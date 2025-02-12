                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ationCallback(DICOMParser *parser,
                                           doublebyte group,
                                           doublebyte element,
                                           DICOMParser::VRTypes type,
                                           unsigned char* val,
                                           quadbyte len);

  virtual void PhotometricInterpretationCallback(DICOMParser *parser,
                                                 doublebyte,
                                                 doublebyte,
                                                 DICOMParser::VRTypes,
                                                 unsigned char* val,
                                                 quadbyte len);

  virtual void PixelDataCallback(DICOMParser *parser,
                                 doublebyte,
                                 doublebyte,
                                 DICOMParser::VRTypes,
                                 unsigned char* val,
                                 quadbyte len);

  virtual void RescaleOffsetCallback( DICOMParser *parser,
                                      doublebyte,
                                      doublebyte,
                                      DICOMParser::VRTypes,
                                      unsigned char* val,
                                      quadbyte);

  /** Register all the standard callbacks with the DICOM Parser.  This
   * associates a callback with each (group, element) tag pair in the
   * header of the file whose data needs to be cached. */
  virtual void RegisterCallbacks(DICOMParser* parser);

  /** Register a callback for retrieving the pixel data from a DICOM
   *  file */
  virtual void RegisterPixelDataCallback(DICOMParser* parser);


  /** Output information associated with a DICOM series */
  void OutputSeries();


  /** The next set of methods are for accessing information which is
   * cached when a DICOM file is processed.  This allows access to
   * information from the header as well as the pixel data. */
  
  
  /** Get the pixel spacing of the last image processed by the
   *  DICOMParser */
  float* GetPixelSpacing()
    {
    return this->PixelSpacing;
    }

  /** Get the image width of the last image processed by the
   *  DICOMParser */
  int GetWidth()
    {
    return this->Width;
    }

  /** Get the image height of the last image processed by the
   *  DICOMParser */
  int GetHeight()
    {
    return this->Height;
    }

  /** Get the dimensions (width, height) of the last image processed
   *  by the DICOMParser */
  int* GetDimensions()
    {
    return this->Dimensions;
    }

  /** Get the (DICOM) x,y,z coordinates of the first pixel in the
   * image (upper left hand corner) of the last image processed by the
   * DICOMParser */
  float *GetImagePositionPatient()
    {
      return this->ImagePositionPatient;
    }

  /** Get the (DICOM) directions cosines. It consist of the components
   * of the first two vectors. The third vector needs to be computed
   * to form an orthonormal basis. */
 float *GetImageOrientationPatient()
    {
      return this->ImageOrientationPatient;
    }
  
  /** Get the number of bits allocated per pixel of the last image
   *  processed by the DICOMParser */
  int GetBitsAllocated()
    {
    return this->BitsAllocated;
    }

  /** Get the pixel representation of the last image processed by the
   * DICOMParser. A zero is a unsigned quantity.  A one indicates a
   * signed quantity. */
  int GetPixelRepresentation()
    {
    return this->PixelRepresentation;
    }

  /** Get the number of components of the last image processed by the
   *  DICOMParser. */
  int GetNumberOfComponents()
    {
    if (!this->PhotometricInterpretation)
      {
      return 1;
      }

    //
    // DICOM standard says that spaces (0x20) are to
    // be ignored for CS types.  We don't handle this
    // well yet.
    //
    dicom_stl::string str1(*this->PhotometricInterpretation);
    dicom_stl::string rgb("RGB ");

    if (str1 == rgb)
      {
      return 3;
      }
    else
      {
      return 1;
      }
    }

  /** Get the transfer syntax UID for the last image processed by the
   *  DICOMParser. */
  dicom_stl::string GetTransferSyntaxUID()
    {
    return *(this->TransferSyntaxUID);
    }

  /** Get a textual description of the transfer syntax of the last
   *  image processed by the DICOMParser. */
  const char* TransferSyntaxUIDDescription(const char* uid);

  /** Get the image data from the last image processed by the
   * DICOMParser.  The data is only valid if the PixelDataCallback was
   * registered.
   * \sa RegisterPixelDataCallback()
  */
  void GetImageData(void* & data, DICOMParser::VRTypes& dataType, unsigned long& len);

  /** Determine whether the image data was rescaled (by the
   *  RescaleSlope tag) to be floating point. */
  bool RescaledImageDataIsFloat();

  /** Determine whether the image data was rescaled (by the
   * RescaleSlope tag) to be a signed data type. */
  bool RescaledImageDataIsSigned();

  /** Get the slice number of the last image processed by the
      DICOMParser. */
  int GetSliceNumber()
    {
    return this->SliceNumber;
    }

  /** Clear the internal databases. This will reset the internal
   * databases that are grouping filenames based on SeriesUID's and
   * ordering filenames based on image locations. */
  void Clear();

  /** Get the series UIDs for the files processed since the last
   * clearing of the cache. */
  void GetSeriesUIDs(dicom_stl::vector<dicom_stl::string> &v); 
  
  /** Get the filenames for a series ordered by slice number. */
  void GetSliceNumberFilenamePairs(const dicom_stl::string &seriesUID,
                              dicom_stl::vector<dicom_stl::pair<int, dicom_stl::string> > &v, bool ascending = true);

  /** Get the filenames for a series order by slice number.  Use the
      first series by default. */
  void GetSliceNumberFilenamePairs(dicom_stl::vector<dicom_stl::pair<int, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by slice location. */
  void GetSliceLocationFilenamePairs(const dicom_stl::string &seriesUID,
                              dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by slice location. Use the
   * first series by default. */
  void GetSliceLocationFilenamePairs(dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by image position
     patient. This is the most reliable way to order the images in a
     series. */
  void GetImagePositionPatientFilenamePairs(const dicom_stl::string &seriesUID,
                            dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by image position
     patient. This is the most reliable way to order the images in a
     series. Use the first series by default. */
  void GetImagePositionPatientFilenamePairs(dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  float GetRescaleSlope()
    {
    return this->RescaleSlope;
    }

  float GetRescaleOffset()
    {
    return this->RescaleOffset;
    }

  dicom_stl::string GetPatientName()
    {
    return *(this->PatientName);
    }

  dicom_stl::string GetStudyUID()
    {
    return *(this->StudyUID);
    }

  dicom_stl::string GetStudyID()
    {
    return *(this->StudyID);
    }
  
  void PatientNameCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  void StudyUIDCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  void StudyIDCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  void GantryAngleCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  float GetGantryAngle()
    {
    return this->GantryAngle;
    }

  

 protected:
  int BitsAllocated;
  bool ByteSwapData;
  float PixelSpacing[3];
  int Width;
  int Height;
  int SliceNumber; 
  int Dimensions[2];
  float ImagePositionPatient[3];
  float ImageOrientationPatient[6];

  // map from series UID to vector of files in the series 
  // dicom_stl::map<dicom_stl::string, dicom_stl::vector<dicom_stl::string>, ltstdstr> SeriesUIDMap;

  // map from filename to intraseries sortable tags
  // dicom_stl::map<dicom_stl::string, DICOMOrderingElements, ltstdstr> SliceOrderingMap;

  typedef dicom_stl::map<dicom_stl::pair<doublebyte, doublebyte>, DICOMTagInfo> TagMapType;
  // TagMapType TagMap;

  dicom_stream::ofstream HeaderFile;
  
  // 0 unsigned
  // 1 2s complement (signed)
  int PixelRepresentation;
  dicom_stl::string* PhotometricInterpretation;
  dicom_stl::string* TransferSyntaxUID;
  float RescaleOffset;
  float RescaleSlope;
  void* ImageData;
  DICOMParser::VRTypes ImageDataType;
  unsigned long ImageDataLengthInBytes;

  dicom_stl::string* PatientName;
  dicom_stl::string* StudyUID;
  dicom_stl::string* StudyID;
  float GantryAngle;

  DICOMMemberCallback<DICOMAppHelper>* SeriesUIDCB;
  DICOMMemberCallback<DICOMAppHelper>* SliceNumberCB;
  DICOMMemberCallback<DICOMAppHelper>* SliceLocationCB;
  DICOMMemberCallback<DICOMAppHelper>* ImagePositionPatientCB;
  DICOMMemberCallback<DICOMAppHelper>* ImageOrientationPatientCB;
  DICOMMemberCallback<DICOMAppHelper>* TransferSyntaxCB;
  DICOMMemberCallback<DICOMAppHelper>* ToggleSwapBytesCB;
  DICOMMemberCallback<DICOMAppHelper>* BitsAllocatedCB;
  DICOMMemberCallback<DICOMAppHelper>* PixelSpacingCB;
  DICOMMemberCallback<DICOMAppHelper>* HeightCB;
  DICOMMemberCallback<DICOMAppHelper>* WidthCB;
  DICOMMemberCallback<DICOMAppHelper>* PixelRepresentationCB;
  DICOMMemberCallback<DICOMAppHelper>* PhotometricInterpretationCB;
  DICOMMemberCallback<DICOMAppHelper>* RescaleOffsetCB;
  DICOMMemberCallback<DICOMAppHelper>* RescaleSlopeCB;
  DICOMMemberCallback<DICOMAppHelper>* PixelDataCB;
  DICOMMemberCallback<DICOMAppHelper>* PatientNameCB;
  DICOMMemberCallback<DICOMAppHelper>* StudyUIDCB;
  DICOMMemberCallback<DICOMAppHelper>* StudyIDCB;

  DICOMMemberCallback<DICOMAppHelper>* GantryAngleCB;

  //
  // Implementation contains stl templated classes that 
  // can't be exported from a DLL in Windows. We hide
  // them in the implementation to get rid of annoying
  // compile warnings.
  //
  DICOMAppHelperImplementation* Implementation;

 private:
  DICOMAppHelper(const DICOMAppHelper&);  
  void operator=(const DICOMAppHelper&); 
    
};

#ifdef _MSC_VER
#pragma warning ( pop )
#endif

#endif
