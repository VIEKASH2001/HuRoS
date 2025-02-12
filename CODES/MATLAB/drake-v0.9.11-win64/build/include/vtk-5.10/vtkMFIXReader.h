/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMFIXReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMFIXReader - reads a dataset in MFIX file format
// .SECTION Description
// vtkMFIXReader creates an unstructured grid dataset. It reads a restart
// file and a set of sp files.  The restart file contains the mesh 
// information.  MFIX meshes are either cylindrical or rectilinear, but 
// this reader will convert them to an unstructured grid.  The sp files 
// contain transient data for the cells.  Each sp file has one or more 
// variables stored inside it.  

// .SECTION Thanks
// Thanks to Phil Nicoletti and Brian Dotson at the National Energy 
// Technology Laboratory who developed this class.
// Please address all comments to Brian Dotson (brian.dotson@netl.doe.gov)

// .SECTION See Also
// vtkGAMBITReader

#ifndef __vtkMFIXReader_h
#define __vtkMFIXReader_h

#include "vtkUnstructuredGridAlgorithm.h"

class vtkDataArraySelection;
class vtkDoubleArray;
class vtkStringArray;
class vtkIntArray;
class vtkFloatArray;
class vtkXMLUnstructuredGridWriter;
class vtkWedge;
class vtkQuad;
class vtkHexahedron;
class vtkPoints;
class vtkStdString;

class VTK_IO_EXPORT vtkMFIXReader : public vtkUnstructuredGridAlgorithm
{
public:
  static vtkMFIXReader *New();
  vtkTypeMacro(vtkMFIXReader,vtkUnstructuredGridAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify the file name of the MFIX Restart data file to read.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Get the total number of cells. The number of cells is only valid after a
  // successful read of the data file is performed.
  vtkGetMacro(NumberOfCells,int);

  // Description:
  // Get the total number of nodes. The number of nodes is only valid after a
  // successful read of the data file is performed.
  vtkGetMacro(NumberOfPoints,int);

  // Description:
  // Get the number of data components at the nodes and cells.
  vtkGetMacro(NumberOfCellFields,int);
  
  // Description:
  // Which TimeStep to read.
  vtkSetMacro(TimeStep, int);
  vtkGetMacro(TimeStep, int);
 
  // Description:
  // Returns the number of timesteps.
  vtkGetMacro(NumberOfTimeSteps, int);

  // Description:
  // Which TimeStepRange to read
  vtkGetVector2Macro(TimeStepRange, int);
  vtkSetVector2Macro(TimeStepRange, int);

  // Description
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
  // Get the range of cell data.
  void GetCellDataRange(int cellComp, int index, float *min, float *max);
  
protected:
  vtkMFIXReader();
  ~vtkMFIXReader();
  int RequestInformation(vtkInformation *,
    vtkInformationVector **, vtkInformationVector *);
  int RequestData(vtkInformation *,
    vtkInformationVector **, vtkInformationVector *);

  //
  // ParaView Variables
  //

  char *FileName;
  int RequestInformationFlag;
  int MakeMeshFlag;
  int NumberOfPoints;
  int NumberOfCells;
  int NumberOfCellFields;
  vtkIntArra                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 