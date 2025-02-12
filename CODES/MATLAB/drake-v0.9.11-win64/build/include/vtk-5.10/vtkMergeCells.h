                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                that locator here.  The default tolerance
  //   is 10e-4.

  vtkSetClampMacro(PointMergeTolerance, float, 0.0, VTK_LARGE_FLOAT);
  vtkGetMacro(PointMergeTolerance, float);

  // Description:
  //   vtkMergeCells will detect and filter out duplicate cells if you
  //   provide it the name of a global cell ID array.

  vtkSetMacro(UseGlobalCellIds, int);
  vtkGetMacro(UseGlobalCellIds, int);

  // Description:
  //   vtkMergeCells attempts eliminate duplicate points when merging
  //   data sets.  If for some reason you don't want it to do this,
  //   than MergeDuplicatePointsOff().

  vtkSetMacro(MergeDuplicatePoints, int);
  vtkGetMacro(MergeDuplicatePoints, int);
  vtkBooleanMacro(MergeDuplicatePoints, int);

  // Description:
  //    We need to know the number of different data sets that will
  //    be merged into one so we can pre-allocate some arrays.
  //    This can be an upper bound, not necessarily exact.

  vtkSetMacro(TotalNumberOfDataSets, int);
  vtkGetMacro(TotalNumberOfDataSets, int);

  // Description:
  //    Provide a DataSet to be merged in to the final UnstructuredGrid.
  //    This call returns after the merge has completed.  Be sure to call
  //    SetTotalNumberOfCells, SetTotalNumberOfPoints, and SetTotalNumberOfDataSets
  //    before making this call.  Return 0 if OK, -1 if error.

  int MergeDataSet(vtkDataSet *set);

  // Description:
  //    Call Finish() after merging last DataSet to free unneeded memory and to
  //    make sure the ugrid's GetNumberOfPoints() reflects the actual
  //    number of points set, not the number allocated.

  void Finish();

protected:

  vtkMergeCells();
  ~vtkMergeCells();

private:

  void FreeLists();
  void StartUGrid(vtkDataSet *set);
  vtkIdType *MapPointsToIdsUsingGlobalIds(vtkDataSet *set);
  vtkIdType *MapPointsToIdsUsingLocator(vtkDataSet *set);
  vtkIdType AddNewCellsUnstructuredGrid(vtkDataSet *set, vtkIdType *idMap);
  vtkIdType AddNewCellsDataSet(vtkDataSet *set, vtkIdType *idMap);

  vtkIdType GlobalCellIdAccessGetId(vtkIdType idx);
  int GlobalCellIdAccessStart(vtkDataSet *set);
  vtkIdType GlobalNodeIdAccessGetId(vtkIdType idx);
  int GlobalNodeIdAccessStart(vtkDataSet *set);

  int TotalNumberOfDataSets;

  vtkIdType TotalNumberOfCells;
  vtkIdType TotalNumberOfPoints;

  vtkIdType NumberOfCells;     // so far
  vtkIdType NumberOfPoints;

  int UseGlobalIds;       // point, or node, IDs
  int GlobalIdArrayType;
  void* GlobalIdArray;

  int UseGlobalCellIds;   // cell IDs
  int GlobalCellIdArrayType;
  void* GlobalCellIdArray;

  float PointMergeTolerance;
  int MergeDuplicatePoints;

  char InputIsUGrid;
  char InputIsPointSet;

  vtkMergeCellsSTLCloak *GlobalIdMap;
  vtkMergeCellsSTLCloak *GlobalCellIdMap;

//BTX
  vtkDataSetAttributes::FieldList *ptList;
  vtkDataSetAttributes::FieldList *cellList;
//ETX

  vtkUnstructuredGrid *UnstructuredGrid;

  int nextGrid;

  vtkMergeCells(const vtkMergeCells&); // Not implemented
  void operator=(const vtkMergeCells&); // Not implemented
};
#endif
