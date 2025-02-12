/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkFLUENTReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkFLUENTReader - reads a dataset in Fluent file format
// .SECTION Description
// vtkFLUENTReader creates an unstructured grid dataset. It reads .cas and
// .dat files stored in FLUENT native format.
//
// .SECTION Thanks
// Thanks to Brian W. Dotson & Terry E. Jordan (Department of Energy, National
// Energy Technology Laboratory) & Douglas McCorkle (Iowa State University)
// who developed this class.
// Please address all comments to Brian Dotson (brian.dotson@netl.doe.gov) &
// Terry Jordan (terry.jordan@sa.netl.doe.gov)
// & Doug McCorkle (mccdo@iastate.edu)
//

// .SECTION See Also
// vtkGAMBITReader

#ifndef __vtkFLUENTReader_h
#define __vtkFLUENTReader_h

#include "vtkMultiBlockDataSetAlgorithm.h"

class vtkDataArraySelection;
class vtkPoints;
class vtkTriangle;
class vtkTetra;
class vtkQuad;
class vtkHexahedron;
class vtkPyramid;
class vtkWedge;
class vtkConvexPointSet;

class VTK_IO_EXPORT vtkFLUENTReader : public vtkMultiBlockDataSetAlgorithm
{
public:
  static vtkFLUENTReader *New();
  vtkTypeMacro(vtkFLUENTReader,vtkMultiBlockDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify the file name of the Fluent case file to read.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Get the total number of cells. The number of cells is only valid after a
  // successful read of the data file is performed. Initial value is 0.
  vtkGetMacro(NumberOfCells,int);

  // Description:
  // Get the number of cell arrays available in the input.
  int GetNumberOfCellArrays(void);

  // Description:
  // Get the name of the  cell array with the given index in
  // the input.
  const char* GetCellArrayName(int index);

  // Description:
  // Get/Set whether the cell array with the given name is to
  // be read.
  int GetCellArrayStatus(const char* name);
  void SetCellArrayStatus(const char* name, int status);

  // Description:
  // Turn on/off all cell arrays.
  void DisableAllCellArrays();
  void EnableAllCellArrays();

  // Description:
  // These methods should be used instead of the SwapBytes methods.
  // They indicate the byte ordering of the file you are trying
  // to read in. These methods will then either swap or not swap
  // the bytes depending on the byte ordering of the machine it is
  // being run on. For example, reading in a BigEndian file on a
  // BigEndian machine will result in no swapping. Trying to read
  // the same file on a LittleEndian machine will result in swapping.
  // As a quick note most UNIX machines are BigEndian while PC's
  // and VAX tend to be LittleEndian. So if the file you are reading
  // in was generated on a VAX or PC, SetDataByteOrderToLittleEndian 
  // otherwise SetDataByteOrderToBigEndian. Not used when reading
  // text files. 
  void SetDataByteOrderToBigEndian();
  void SetDataByteOrderToLittleEndian();
  int  GetDataByteOrder();
  void SetDataByteOrder(int);
  const char *GetDataByteOrderAsString();
  //
  //  Structures
  //
  struct Cell;
  struct Face;
  struct ScalarDataChunk;
  struct VectorDataChunk;
  struct stdString;
  struct intVector;
  struct doubleVector;
  struct stringVector;
  struct cellVector;
  struct faceVector;
  struct stdMap;
  struct scalarDataVector;
  struct vectorDataVector;
  struct intVectorVector;

protected:
  vtkFLUENTReader();
  ~vtkFLUENTReader();
  int Reque                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     