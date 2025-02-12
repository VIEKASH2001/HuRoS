                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                sing the stencil.
  vtkSetVector3Macro(Spacing, double);
  vtkGetVector3Macro(Spacing, double);

  // Description:
  // Set the desired origin for the stencil.
  // This must be called before the stencil is Updated, ideally 
  // in the ExecuteInformation method of the imaging filter that
  // is using the stencil.
  vtkSetVector3Macro(Origin, double);
  vtkGetVector3Macro(Origin, double);

  // Description:
  // Set the extent of the data.  This is should be called only 
  // by vtkImageStencilSource, as it is part of the basic pipeline
  // functionality.
  void SetExtent(int extent[6]);
  void SetExtent(int x1, int x2, int y1, int y2, int z1, int z2);
  vtkGetVector6Macro(Extent, int);

  // Description:
  // Allocate space for the sub-extents.  This is called by
  // vtkImageStencilSource.
  void AllocateExtents();

  // Description:
  // Fill the sub-extents.
  void Fill();

  // Description:
  // Override these to handle origin, spacing, scalar type, and scalar
  // number of components.  See vtkDataObject for details.
  virtual void CopyInformationToPipeline(vtkInformation* request,
                                         vtkInformation* input,
                                         vtkInformation* output,
                                         int forceCopy);
  virtual void CopyInformationFromPipeline(vtkInformation* request);

  //BTX
  // Description:
  // Retrieve an instance of this class from an information object.
  static vtkImageStencilData* GetData(vtkInformation* info);
  static vtkImageStencilData* GetData(vtkInformationVector* v, int i=0);
  //ETX
  
  // Description:
  // Add merges the stencil supplied as argument into Self.
  virtual void Add     ( vtkImageStencilData * ); 

  // Description:
  // Subtract removes the portion of the stencil, supplied as argument, 
  // that lies within Self from Self.   
  virtual void Subtract( vtkImageStencilData * ); 

  // Description:
  // Replaces the portion of the stencil, supplied as argument, 
  // that lies within Self from Self.   
  virtual void Replace( vtkImageStencilData * ); 

  // Description:
  // Clip the stencil with the supplied extents. In other words, discard data
  // outside the specified extents. Return 1 if something changed.
  virtual int Clip( int extent[6] );

protected:
  vtkImageStencilData();
  ~vtkImageStencilData();

  // Description:
  // Get important info from pipeline.
  void CopyOriginAndSpacingFromPipeline();

  // Description:
  // Merges portions of the stencil that are within Self's extents into 
  // itself. 
  virtual void InternalAdd( vtkImageStencilData * );
  
  void CollapseAdditionalIntersections(int r2, int idx, int *clist, 
    int &clistlen);

  // Description:
  // The Spacing and Origin of the data.
  double Spacing[3];
  double Origin[3];
  
  int Extent[6];

  // Description:
  // The actual 'data' is stored here.
  int NumberOfExtentEntries;
  int *ExtentListLengths;
  int **ExtentLists;

private:
  vtkImageStencilData(const vtkImageStencilData&);  // Not implemented.
  void operator=(const vtkImageStencilData&);  // Not implemented.

  friend class vtkImageStencilIteratorFriendship;
};

//BTX
// Description:
// This is a helper class for stencil creation.  It is a raster with
// infinite resolution in the X direction (approximately, since it uses
// double precision).  Lines that represent polygon edges can be drawn
// into this raster, and then filled given a tolerance.
class VTK_IMAGING_EXPORT vtkImageStencilRaster
{
public:
  // Description:
  // Create a raster with the specified whole y extent.
  vtkImageStencilRaster(const int wholeExtent[2]);

  // Description:
  // Destructor.
  ~vtkImageStencilRaster();

  // Description:
  // Reset the raster to its original state, but keep the same whole
  // extent. Pre-allocate the specified 1D allocateExtent, which must be
  // within the whole extent.
  void PrepareForNewData(const int allocateExtent[2] = 0);

  // Description:
  // Insert a line into the raster, given the two end points.
  // The "inflect1" and "inflect2" should be set if you want
  // to add a small vertical tolerance to either endpoints.
  void InsertLine(const double p1[2], const double p2[2],
                  bool inflect1, bool inflect2);

  // Description:
  // Fill the specified extent of a vtkImageStencilData with the raster,
  // after permuting the raster according to xj and yj.
  void FillStencilData(vtkImageStencilData *data, const int extent[6],
                       int xj = 0, int yj = 1);

  // Description:
  // The tolerance for float-to-int conversions.
  void SetTolerance(double tol) { this->Tolerance = tol; }
  double GetTolerance() { return this->Tolerance; }

protected:
  // Description:
  // Ensure that the raster is initialized for the specified range
  // of y values, which must be within the Extent.
  void PrepareExtent(int ymin, int ymax);

  // Description:
  // Insert an x point into the raster.  If the y value is larger
  // than the y extent, the extent will grow automatically.
  void InsertPoint(int y, double x);

  int Extent[2];
  int UsedExtent[2];
  double **Raster;
  double Tolerance;

private:
  vtkImageStencilRaster(const vtkImageStencilRaster&);  // Not implemented.
  void operator=(const vtkImageStencilRaster&);  // Not implemented.
};
//ETX

#endif



