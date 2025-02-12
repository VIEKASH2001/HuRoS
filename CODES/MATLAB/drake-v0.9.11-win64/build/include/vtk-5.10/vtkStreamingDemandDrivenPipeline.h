/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkStreamingDemandDrivenPipeline.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkStreamingDemandDrivenPipeline - Executive supporting partial updates.
// .SECTION Description
// vtkStreamingDemandDrivenPipeline is an executive that supports
// updating only a portion of the data set in the pipeline.  This is
// the style of pipeline update that is provided by the old-style VTK
// 4.x pipeline.  Instead of always updating an entire data set, this
// executive supports asking for pieces or sub-extents.

#ifndef __vtkStreamingDemandDrivenPipeline_h
#define __vtkStreamingDemandDrivenPipeline_h

#include "vtkDemandDrivenPipeline.h"

#define VTK_UPDATE_EXTENT_COMBINE 1
#define VTK_UPDATE_EXTENT_REPLACE 2

class vtkExtentTranslator;
class vtkInformationDoubleKey;
class vtkInformationDoubleVectorKey;
class vtkInformationIdTypeKey;
class vtkInformationIntegerKey;
class vtkInformationIntegerVectorKey;
class vtkInformationObjectBaseKey;
class vtkInformationStringKey;
class vtkInformationUnsignedLongKey;

class VTK_FILTERING_EXPORT vtkStreamingDemandDrivenPipeline : public vtkDemandDrivenPipeline
{
public:
  static vtkStreamingDemandDrivenPipeline* New();
  vtkTypeMacro(vtkStreamingDemandDrivenPipeline,vtkDemandDrivenPipeline);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Generalized interface for asking the executive to fullfill update
  // requests.
  virtual int ProcessRequest(vtkInformation* request,
                             vtkInformationVector** inInfo,
                             vtkInformationVector* outInfo);

  // Description:
  // Bring the outputs up-to-date.
  virtual int Update();
  virtual int Update(int port);
  virtual int UpdateWholeExtent();

  // Description:
  // Propagate the update request from the given output port back
  // through the pipeline.  Should be called only when information is
  // up to date.
  int PropagateUpdateExtent(int outputPort);

  // Description:
  // Set/Get the maximum number of pieces that can be requested from
  // the given port.  The maximum number of pieces is meta data for
  // unstructured data sets.  It gets set by the source during the
  // update information call.  A value of -1 indicates that there is
  // no maximum.
  int SetMaximumNumberOfPieces(int port, int n);
  int SetMaximumNumberOfPieces(vtkInformation *, int n);
  int GetMaximumNumberOfPieces(int port);
  int GetMaximumNumberOfPieces(vtkInformation *);

  // Description:
  // Set/Get the whole extent of an output port.  The whole extent is
  // meta data for structured data sets.  It gets set by the algorithm
  // during the update information pass.
  int SetWholeExtent(vtkInformation *, int extent[6]);
  void GetWholeExtent(vtkInformation *, int extent[6]);
  int* GetWholeExtent(vtkInformation *);

  // Description:
  // If the whole input extent is required to generate the requested output
  // extent, this method can be called to set the input update extent to the
  // whole input extent. This method assumes that the whole extent is known
  // (that UpdateInformation has been called)
  int SetUpdateExtentToWholeExtent(int port);
  int SetUpdateExtentToWholeExtent(vtkInformation *);
  
  // Description:
  // Get/Set the update extent for output ports that use 3D extents.
  int SetUpdateExtent(int port, int extent[6]);
  int SetUpdateExtent(vtkInformation *, int extent[6]);
  void GetUpdateExtent(vtkInformation *, int extent[6]);
  int* GetUpdateExtent(vtkInform�PNG

   IHDR   7   7   ���F  �IDATh���JA�� "=H�'�D�k@|�G�T|�_@�	�b2xS�W�<h.40Z%H��̌�Iw3?��?���TW���?��C���o��zA��I�G�7�<��
�5�w%��`�@�*��X���4Na����@	P��p� ����@o!qZw����>Ђ�u�PyW� ��U?:�@9�3�Cu�0�T x-�&c�� &t�n0��AQ [k0�K~:-���� ܖ.p�d�A�,8����\����.H��/ܻN5�{��b� 9���=��@+	�v��mI�v��E��0������u�1han$^s�vM>�l�V�ݲP�[�v�.�7�2w�]81�`���Ȍi�i-��([e�[fLSN�B��,.٭ ��p�1<�����a\p��lF0��J�;Xn�,,��n��QS����z�_g�&I�[YL�d� =�[b��*�܃�͆+P�˘t}��~���ָ�ܪeP/g�����n�YGt��Q���"�{)�O��T	7h�Ǩ�-���Y�
���F~��)i�h�}���_{޶�M&!8&�P��=q<oʬ'JI���T�rѼC��ϡ��ܠ�^�����.���_bŘrG%?A�mBQ,�٪3��~�?i���6RE    IEND�B`�                                                                                                                                                                                                                                                                                                                     imeSteps(vtkInformation *, double *times, int length);
  int SetUpdateTimeStep(int port, double time);
  //void GetUpdateTimeSteps(vtkInformation *, int extent[6]);

  // Description:
  // This request flag indicates whether the requester can handle more
  // data than requested for the given port.  Right now it is used in
  // vtkImageData.  Image filters can return more data than requested.
  // The the consumer cannot handle this (i.e. DataSetToDataSetFitler)
  // the image will crop itself.  This functionality used to be in
  // ImageToStructuredPoints.
  int SetRequestExactExtent(int port, int flag);
  int GetRequestExactExtent(int port);

  // Description:
  // Get/Set the object that will translate pieces into structured
  // extents for an output port.
  int SetExtentTranslator(int port, vtkExtentTranslator* translator);
  int SetExtentTranslator(vtkInformation *, vtkExtentTranslator* translator);
  vtkExtentTranslator* GetExtentTranslator(int port);
  vtkExtentTranslator* GetExtentTranslator(vtkInformation *info);

  // Description:
  // Set/Get the whole bounding box of an output port data object.
  // The whole whole bounding box is meta data for data sets.  It gets
  // set by the algorithm during the update information pass.
  int SetWholeBoundingBox(int port, double bb[6]);
  void GetWholeBoundingBox(int port, double bb[6]);
  double* GetWholeBoundingBox(int port);

  // Description:
  // Set/Get the piece bounding box of an output port data object.
  // The piece bounding box is meta data for data sets.  It gets
  // set by the algorithm during the update extent information pass.
  int SetPieceBoundingBox(int port, double bb[6]);
  void GetPieceBoundingBox(int port, double bb[6]);
  double* GetPieceBoundingBox(int port);

  // Description:
  // Key defining a request to propagate the update extent upstream.
  static vtkInformationRequestKey* REQUEST_UPDATE_EXTENT();

  // Description:
  // Key defining a request to propagate information about the update
  // extent downstream.
  static vtkInformationRequestKey* REQUEST_UPDATE_EXTENT_INFORMATION();
  static vtkInformationRequestKey* REQUEST_MANAGE_INFORMATION();

  // Description:
  // Key defining to propagate resolution changes up the pipeline.
  static vtkInformationRequestKey* REQUEST_RESOLUTION_PROPAGATE();

  // Description:
  // Key for an algorithm to store in a request to tell this executive
  // to keep executing it.
  static vtkInformationIntegerKey* CONTINUE_EXECUTING();

  // Description:
  // Key to store an extent translator in pipeline information.
  static vtkInformationObjectBaseKey* EXTENT_TRANSLATOR();

  // Description:
  // Keys to store an update request in pipeline information.
  static vtkInformationIntegerKey* UPDATE_EXTENT_INITIALIZED();
  static vtkInformationIntegerVectorKey* UPDATE_EXTENT();
  static vtkInformationIntegerKey* UPDATE_PIECE_NUMBER();
  static vtkInformationIntegerKey* UPDATE_NUMBER_OF_PIECES();
  static vtkInformationIntegerKey* UPDATE_NUMBER_�PNG

   IHDR   B   B   �T �  *IDATx���KTQ���fQQ��Ä�FB06V��$HA\$m%"���f���A���~H
AeL4�Z��{�H�{��{w����=�Epq�y���{�q`��7o޼y�f�]��p�
�C��C��	ڀV�Yh
��� *}��JA�w�^BS��%��FBm���� �cJm-C�mA	�	}���O�� ��XQJ�m�1��C?��y�.!4=� ��[.�?.C����� Z�"	�4��鴬�;�IW`��ڈ`T]��;�K0F9IƁ����-�}ɮ�v	D )����9�JvE�5k�����4w�J����^tmW� �� �S�@
@��� �t�%ux��@��'�*��q��VRggm�b�[iRg' �Z bWvw�kX ���M��K����S'�H[�d�/�q^�F�˶��ی �Z��N��X�<����6������8>��xܢk�w���Ϋ��,j�,�p^��F��8˺y-�`	�r�>.�7:��О7 Ă$�I�Q�|[�]�#���Qx[��U�˩d� �$)��+�Z�.Y�f$KB(򚇙���?��vF%�����k���aQ'��k��y����j[�P�~�Ӝ�T�C�2��-^X5��G�B������h�0����`�o�3�3(.M��6Q�b����!2�{�����h�pv���H8p�c��W�����nT5rh�0��Nm?�%n�.;= @Ucں'~��/qc$����W��E�9�4���_�i����嚞�i���o޼y���.��%>�3�    IEND�B`�                                                                                                                                                             ECES();

  // Description:
  // Key to store the bounding box of the entire data set in pipeline
  // information.
  static vtkInformationDoubleVectorKey* WHOLE_BOUNDING_BOX();

  // Description:
  // Key to store the bounding box of a portion of the data set in
  // pipeline information.
  static vtkInformationDoubleVectorKey* PIECE_BOUNDING_BOX();

  // Description:
  // Key used to reject unimportant pieces in streaming.
  static vtkInformationDoubleVectorKey* PIECE_NORMAL();

  // Description:
  // Key to specify the request for exact extent in pipeline information.
  static vtkInformationIntegerKey* EXACT_EXTENT();

  // Description:
  // Key to store available time steps.
  static vtkInformationDoubleVectorKey* TIME_STEPS();

  // Description:
  // Key to store available time range for continuous sources.
  static vtkInformationDoubleVectorKey* TIME_RANGE();

  // Description:
  // Update time steps requested by the pipeline.
  static vtkInformationDoubleVectorKey* UPDATE_TIME_STEPS();

  // Description:
  // Key that specifies from 0.0 to 1.0 the pipeline computed priority
  // of this update extent. 0.0 means does not contribute and can
  // be skipped.
  static vtkInformationDoubleKey* PRIORITY();

  // Description:
  // Key that specifies how many cells were in the piece at the head of the
  // pipeline, so that work estimates can be made.
  static vtkInformationUnsignedLongKey* ORIGINAL_NUMBER_OF_CELLS();

  // Description:
  // Key that specifies a requested resolution level for this update
  // extent. 0.0 is very low and 1.0 is full resolution.
  static vtkInformationDoubleKey* UPDATE_RESOLUTION();

  // Description:
  // Used internally to validate meta information as it flows through pipeline
  static vtkInformationIntegerKey* REMOVE_ATTRIBUTE_INFORMATION();

  // Description:
  // The following keys are meant to be used by an algorithm that 
  // works with temporal data. Rather than re-executing the pipeline
  // for each timestep, if the reader, as part of its API, contains
  // a faster way to read temporal data, algorithms may use these
  // keys to request temporal data from the reader.
  // See also: vtkExtractArraysOverTime. 

  // Key to allow a reader to advertise that it supports a fast-path
  // for reading data over time.
  static vtkInformationIntegerKey* FAST_PATH_FOR_TEMPORAL_DATA();
  // The type of data being requested.
  // Possible values: POINT, CELL, EDGE, FACE
  static vtkInformationStringKey* FAST_PATH_OBJECT_TYPE();
  // Possible values: INDEX, GLOBAL
  static vtkInformationStringKey* FAST_PATH_ID_TYPE();
  // The id (either index or global id) being requested
  static vtkInformationIdTypeKey* FAST_PATH_OBJECT_ID();

  // Description:
  // Issues pipeline request to determine and return the priority of the 
  // piece described by the current update extent. The priority is a 
  // number between 0.0 and 1.0 with 0 meaning skippable (REQUEST_DATA 
  // not needed) and 1.0 meaning important. 
  double Co�PNG

   IHDR   M   M   �	�  �IDATx��MhSA�K�~��͛RAE(��4Z�b!���_4R�"�$To����AAAo�Ŧ"��b�"F��ɓ��gp��}o��d�e7o��vvo�ewv��԰����������ؑ��^�3��-h~�^��n��@qPCK-|h���Z�
m�Oh��t�-L�beB+�+��6��A+�3�T�4�!��j��C�/��j�����{ttt����/й�oQv��@�|»��� ��Ƙ�� /�yw����t�����s(^�8j��r1��?���p&���[��;ɤ���@˅���]	�1��Zh�����H��7j��1%gpϩ@&r��̶��n��6΄��вL�=��F�r�3%gp3�l�dB��n�.2!gh��I&��0�
x�q���	��2h�bh����
n1����67h�*�����*��NE����-!�-�>v�x��6�)X
�U���m�A����c���A�pp�RhĘFU88�u�W�,1��*4�`-h�X�F9��
�[m$���]�z�0gi^U�h�$��n	��8��v�%�=�ڋ@C����)u,)�������$'��P`�OD���n�1,yZw�v_��N�uG�t`�0`�����<�D��7a�n��]Au恤#���0��Q��G��X�3n��KR��<���=<ɂx	7ԧ&	|�
��J-��o��Y�`9.YQG H���y�b�qIޙ�+��5J�"�-�_�6j���(���]�g���A�
 ���čx����)�
o������T�YN���%=bfd����w��R	X9k+Q�Y5��]<��E��$��r���W�R�X��D�j����Z�=#^���6����#�54-~��NN&fccccccccs�?���B�Y�f    IEND�B`�                          vtkInformationDoubleVectorKey* PREVIOUS_UPDATE_TIME_STEPS();

  // Keep track of the fast path keys corresponding to the 
  // previous executing. If all key values are the same as their
  // counterparts in the previous request, we do not need to re-execute.
  static vtkInformationIdTypeKey* PREVIOUS_FAST_PATH_OBJECT_ID();
  static vtkInformationStringKey* PREVIOUS_FAST_PATH_OBJECT_TYPE();
  static vtkInformationStringKey* PREVIOUS_FAST_PATH_ID_TYPE();

  // Does the time request correspond to what is in the data?
  // Returns 0 if yes, 1 otherwise.
  virtual int NeedToExecuteBasedOnTime(vtkInformation* outInfo,
                                       vtkDataObject* dataObject);

  // If the request contains a fast path key for temporal data, always execute
  virtual int NeedToExecuteBasedOnFastPathData(vtkInformation* outInfo);

  // Setup default information on the output after the algorithm
  // executes information.
  virtual int ExecuteInformation(vtkInformation* request,
                                 vtkInformationVector** inInfoVec,
                                 vtkInformationVector* outInfoVec);

  // Copy information for the given request.
  virtual void CopyDefaultInformation(vtkInformation* request, int direction,
                                      vtkInformationVector** inInfoVec,
                                      vtkInformationVector* outInfoVec);

  // Helper to check output information before propagating it to inputs.
  virtual int VerifyOutputInformation(int outputPort,
                                      vtkInformationVector** inInfoVec,
                                      vtkInformationVector* outInfoVec);


  // Override this check to account for update extent.
  virtual int NeedToExecuteData(int outputPort,
                                vtkInformationVector** inInfoVec,
                                vtkInformationVector* outInfoVec);

  // Override these to handle the continue-executing option.
  virtual void ExecuteDataStart(vtkInformation* request,
                                vtkInformationVector** inInfoVec,
                                vtkInformationVector* outInfoVec);
  virtual void ExecuteDataEnd(vtkInformation* request,
                              vtkInformationVector** inInfoVec,
                              vtkInformationVector* outInfoVec);

  // Override this to handle cropping and ghost levels.
  virtual void MarkOutputsGenerated(vtkInformation* request,
                                    vtkInformationVector** inInfoVec,
                                    vtkInformationVector* outInfoVec);


  // Remove update/whole extent when resetting pipeline information.
  virtual void ResetPipelineInformation(int port, vtkInformation*);

  // Flag for when an algorithm returns with CONTINUE_EXECUTING in the
  // request.
  int ContinueExecuting;

  vtkInformation *UpdateExtentRequest;

  // did the most recent PUE do anything ?
  int LastPropogateUpdateExtentShortCircuited;
  
private:
  vtkStream�PNG

   IHDR   c   c   �;��  �IDATx��MHQ�SS!������ad)Be��QE�i��H|��(�E��(PÊk�-�Z�&�xQD����E�^���8S�4:3o�y3���9s~o�܏sϝ2��`0��`0��ڟ,%�I;H{I	��,�'�$m$