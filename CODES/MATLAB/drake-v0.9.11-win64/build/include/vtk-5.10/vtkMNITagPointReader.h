                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 point set for each
  // volume, so really, this parameter just tells you the number of
  // outputs to expect from this reader.
  virtual int GetNumberOfVolumes();

  // Description:
  // Get the points.  These are also provided in the first and
  // second output ports of the reader.  This method will return
  // NULL if there is no data.
  virtual vtkPoints *GetPoints(int port);
  virtual vtkPoints *GetPoints() { return this->GetPoints(0); }

  // Description:
  // Get the labels.  These same labels are provided in the output
  // point sets, as the PointData data array named "LabelText".
  // This will return NULL if there were no labels in the file.
  virtual vtkStringArray *GetLabelText();

  // Description:
  // Get the weights.  These are also provided in the output
  // point sets, as the PointData data array named "Weights".
  // This will return NULL if there were no weights in the file.
  virtual vtkDoubleArray *GetWeights();

  // Description:
  // Get the structure ids.  These are also provided in the output
  // point sets, as the PointData data array named "StructureIds".
  // This will return NULL if there were no ids in the file.
  virtual vtkIntArray *GetStructureIds();

  // Description:
  // Get the patient ids.  These are also provided in the output
  // point sets, as the PointData data array named "PatientIds".
  // This will return NULL if there were no ids in the file.
  virtual vtkIntArray *GetPatientIds();

  // Description:
  // Get any comments that are included in the file.
  virtual const char *GetComments();

protected:
  vtkMNITagPointReader();
  ~vtkMNITagPointReader();

  char *FileName;
  int NumberOfVolumes;

  int LineNumber;
  char *Comments;

  int ReadLine(istream &infile, std::string &linetext,
               std::string::iterator &pos);
  int ReadLineAfterComments(istream &infile, std::string &linetext,
                            std::string::iterator &pos);
  int SkipWhitespace(istream &infile,  std::string &linetext,
                     std::string::iterator &pos, int nl);
  int ParseLeftHandSide(istream &infile, std::string &linetext,
                        std::string::iterator &pos,
                        std::string &identifier);
  int ParseStringValue(istream &infile, std::string &linetext,
                       std::string::iterator &pos,
                       std::string &data);
  int ParseIntValues(istream &infile, std::string &linetext,
                     std::string::iterator &pos,
                     int *values, int count);
  int ParseFloatValues(istream &infile, std::string &linetext,
                       std::string::iterator &pos,
                       double *values, int count);

  virtual int ReadFile(vtkPolyData *output1, vtkPolyData *output2);

  virtual int RequestData(vtkInformation* request,
                          vtkInformationVector** inInfo,
                          vtkInformationVector* outInfo);

private:
  vtkMNITagPointReader(const vtkMNITagPointReader&); // Not implemented
  void operator=(const vtkMNITagPointReader&);  // Not implemented

};

#endif
