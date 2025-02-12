                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                eady been
  // updated.
  virtual void Write();

  // Description:
  // Set a matrix that describes the orientation of the data.  The
  // three columns of this matrix should give the unit-vector
  // directions for the VTK x, y and z dimensions respectively.  
  // The writer will use this information to determine how to map
  // the VTK dimensions to the canonical MINC dimensions, and if
  // necessary, the writer will re-order one or more dimensions
  // back-to-front to ensure that no MINC dimension ends up with
  // a direction cosines vector whose dot product with the canonical
  // unit vector for that dimension is negative.
  virtual void SetDirectionCosines(vtkMatrix4x4 *matrix);
  vtkGetObjectMacro(DirectionCosines, vtkMatrix4x4);

  // Description:
  // Set the slope and intercept for rescaling the intensities.  The
  // default values are zero, which indicates to the reader that no
  // rescaling is to be performed.
  vtkSetMacro(RescaleSlope, double);
  vtkGetMacro(RescaleSlope, double);
  vtkSetMacro(RescaleIntercept, double);
  vtkGetMacro(RescaleIntercept, double);

  // Description:
  // Set the image attributes, which contain patient information and
  // other useful metadata.
  virtual void SetImageAttributes(vtkMINCImageAttributes *attributes);
  virtual vtkMINCImageAttributes *GetImageAttributes() {
    return this->ImageAttributes; }; 

  // Description:
  // Set whether to validate that all variable attributes that
  // have been set are ones that are listed in the MINC standard.
  vtkSetMacro(StrictValidation, int);
  vtkBooleanMacro(StrictValidation, int);
  vtkGetMacro(StrictValidation, int);

  // Description:
  // Set a string value to append to the history of the file.  This
  // string should describe, briefly, how the file was processed.
  vtkSetStringMacro(HistoryAddition);
  vtkGetStringMacro(HistoryAddition);

protected:
  vtkMINCImageWriter();
  ~vtkMINCImageWriter();  

  int MINCImageType;
  int MINCImageTypeSigned;
  int MINCImageMinMaxDims;
  
  vtkMatrix4x4 *DirectionCosines;
  double RescaleSlope;
  double RescaleIntercept;
  int StrictValidation;
  int DataUpdateExtent[6];

  int FileDataType;
  double FileValidRange[2];
  double InternalRescaleSlope;
  double InternalRescaleIntercept;

  int ComputeValidRangeFromScalarRange;

  vtkStringArray *FileDimensionNames;

  vtkMINCImageAttributes *ImageAttributes;

  int Permutation[3];
  int Flip[3];

  int MismatchedInputs;
  int MINCFileId;

  char *HistoryAddition;

  virtual int OpenNetCDFFile(const char *filename, int& ncid);
  virtual int CloseNetCDFFile(int ncid);

  virtual int IndexFromDimensionName(const char *dimName);
  virtual void ComputePermutationFromOrientation(int permutation[3],
                                                 int flip[3]);
  virtual int CreateMINCDimensions(vtkImageData *input, int timeStep, 
                                   int *dimids);
  virtual int CreateMINCVariables(vtkImageData *input, int timeStep,
                                  int *dimids);
  virtual int WriteMINCFileAttributes(vtkImageData *input, int timeStep);
  virtual int WriteMINCData(vtkImageData *input, int frameNumber);
  virtual void FindRescale(double &rescaleSlope, double &rescaleIntercept);
  virtual void FindMINCValidRange(double range[2]);

  virtual int FillInputPortInformation(int port, vtkInformation *info);

  virtual int RequestInformation(vtkInformation *request,
                                 vtkInformationVector **inputVector,
                                 vtkInformationVector *outputVector);

  virtual int RequestUpdateExtent(vtkInformation *request,
                                  vtkInformationVector **inputVector,
                                  vtkInformationVector *outputVector);

  virtual int RequestData(vtkInformation* request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector* outputVector);

private:
  vtkMINCImageWriter(const vtkMINCImageWriter&); // Not implemented
  void operator=(const vtkMINCImageWriter&);  // Not implemented

};

#endif
