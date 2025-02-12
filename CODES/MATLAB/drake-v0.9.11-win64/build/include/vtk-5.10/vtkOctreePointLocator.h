                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                to the point.
  virtual vtkIdType FindClosestPointWithinRadius(
    double radius, const double x[3], double& dist2);

  // Description:
  // Find the Id of the point in the given leaf region which is
  // closest to the given point.  Return the ID of the point,
  // and set the square of the distance of between the points.
  vtkIdType FindClosestPointInRegion(int regionId, double *x, double &dist2);
  vtkIdType FindClosestPointInRegion(int regionId, double x, double y, 
                                     double z, double &dist2);

  // Description:
  // Find all points within a specified radius of position x.
  // The result is not sorted in any specific manner.
  virtual void FindPointsWithinRadius(
    double radius, const double x[3], vtkIdList *result);

  // Description:
  // Find the closest N points to a position. This returns the closest
  // N points to a position. A faster method could be created that returned
  // N close points to a position, but not necessarily the exact N closest.
  // The returned points are sorted from closest to farthest.
  // These methods are thread safe if BuildLocator() is directly or
  // indirectly called from a single thread first.
  void FindClosestNPoints(int N, const double x[3], vtkIdList *result);

  // Description:
  // Get a list of the original IDs of all points in a leaf node.
  vtkIdTypeArray *GetPointsInRegion(int leafNodeId);

  // Description:
  // Delete the octree data structure. 
  virtual void FreeSearchStructure();
  
  // Description:
  // Create a polydata representation of the boundaries of
  // the octree regions.  
  void GenerateRepresentation(int level, vtkPolyData *pd);
  
  // Description:
  // Fill ids with points found in area.  The area is a 6-tuple containing
  // (xmin, xmax, ymin, ymax, zmin, zmax).
  // This method will clear the array by default.  To append ids to an array,
  // set clearArray to false.
  void FindPointsInArea(double* area, vtkIdTypeArray* ids, bool clearArray = true);

protected:

  vtkOctreePointLocator();
  ~vtkOctreePointLocator();

  vtkOctreePointLocatorNode *Top;
  vtkOctreePointLocatorNode **LeafNodeList;      // indexed by region/node ID

  void BuildLeafNodeList(vtkOctreePointLocatorNode* node, int & index);

  // Description:
  // Given a point and a node return the leaf node id that contains the
  // point.  The function returns -1 if no nodes contain the point.
  int FindRegion(vtkOctreePointLocatorNode* node, float x, float y, float z);
  int FindRegion(vtkOctreePointLocatorNode* node, double x, double y, double z);

  static void SetDataBoundsToSpatialBounds(vtkOctreePointLocatorNode *node);

  static void DeleteAllDescendants(vtkOctreePointLocatorNode* octant);

//BTX
  // Description:
  // Recursive helper for public FindPointsWithinRadius.  radiusSquared
  // is the square of the radius and is used in order to avoid the
  // expensive square root calculation.
  void FindPointsWithinRadius(vtkOctreePointLocatorNode* node, double radiusSquared,
                              const double x[3], vtkIdList* ids);  

  // Recursive helper for public FindPointsWithinRadius
  void AddAllPointsInRegion(vtkOctreePointLocatorNode* node, vtkIdList* ids);

  // Recursive helper for public FindPointsInArea
  void FindPointsInArea(vtkOctreePointLocatorNode* node, double* area, vtkIdTypeArray* ids);

  // Recursive helper for public FindPointsInArea
  void AddAllPointsInRegion(vtkOctreePointLocatorNode* node, vtkIdTypeArray* ids);

  void DivideRegion(vtkOctreePointLocatorNode *node, int* ordering, int level);

  int DivideTest(int size, int level);

//ETX

  void AddPolys(vtkOctreePointLocatorNode *node, vtkPoints *pts, vtkCellArray *polys);

  // Description:
  // Given a leaf node id and point, return the local id and the squared distance
  // between the closest point and the given point.
  int _FindClosestPointInRegion(int leafNodeId, double x, double y, 
                                double z, double &dist2);

  // Description:
  // Given a location and a radiues, find the closest point within
  // this radius.  The function does not examine the region with Id
  // equal to skipRegion (do not set skipRegion to -1 as all non-leaf
  // octants have -1 as their Id).  The Id is returned along with 
  // the distance squared for success and -1 is returned for failure.  
  int FindClosestPointInSphere(double x, double y, double z, double radius,
                               int skipRegion, double &dist2);

  // Description:
  // The maximum number of points in a region/octant before it is subdivided.
  int MaximumPointsPerRegion;
  int NumberOfLeafNodes;

  double FudgeFactor;   // a very small distance, relative to the dataset's size
  int NumberOfLocatorPoints;
  float *LocatorPoints;
  int *LocatorIds;

  float MaxWidth;

  // Description:
  // If CreateCubicOctants is non-zero, the bounding box of the points will 
  // be expanded such that all octants that are created will be cube-shaped
  // (e.g. have equal lengths on each side).  This may make the tree deeper
  // but also results in better shaped octants for doing searches. The
  // default is to have this set on.
  int CreateCubicOctants;

  vtkOctreePointLocator(const vtkOctreePointLocator&); // Not implemented
  void operator=(const vtkOctreePointLocator&); // Not implemented
};
#endif
