/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMapArrayValues.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMapArrayValues - Map values in an input array to different values in
//   an output array of (possibly) different type.

// .SECTION Description
// vtkMapArrayValues allows you to associate certain values of an attribute array
// (on either a vertex, edge, point, or cell) with different values in a
// newly created attribute array. 
//
// vtkMapArrayValues manages an internal STL map of vtkVariants that can be added to
// or cleared. When this filter executes, each "key" is searched for in the
// input array and the indices of the output array at which there were matches
// the set to the mapped "value".
//
// You can control whether the input array values are passed to the output
// before the mapping occurs (using PassArray) or, if not, what value to set 
// the unmapped indices to (using FillValue). 
//
// One application of this filter is to help address the dirty data problem.
// For example, using vtkMapArrayValues you could associate the vertex values 
// "Foo, John", "Foo, John.", and "John Foo" with a single entity.

#ifndef __vtkMapArrayValues_h
#define __vtkMapArrayValues_h

#include "vtkPassInputTypeAlgorithm.h"

class vtkMapType;
class vtkVariant;

class VTK_RENDERING_EXPORT vtkMapArrayValues : public vtkPassInputTypeAlgorithm
{
public:
  vtkTypeMacro(vtkMapArrayValues,vtkPassInputTypeAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkMapArrayValues *New();

  // Description: 
  // Set/Get where the data is located that is being mapped.
  // See FieldType enumeration for possible values.
  // Default is POINT_DATA.
  vtkSetMacro(FieldType, int);
  vtkGetMacro(FieldType, int);

  // Description: 
  // Set/Get whether to copy the data from the input array to the output array
  // before the mapping occurs. If turned off, FillValue is used to initialize
  // any unmapped array indices. Default is off.
  vtkSetMacro(PassArray, int);
  vtkGetMacro(PassArray, int);
  vtkBooleanMacro(PassArray, int);

  // Description: 
  // Set/Get whether to copy the data from the input array to the output array
  // before the mapping occurs. If turned off, FillValue is used to initialize
  // any unmapped array indices. Default is -1.
  vtkSetMacro(FillValue, double);
  vtkGetMacro(FillValue, double);

  // Description: 
  // Set/Get the name of the input array. This must be set prior to execution.
  vtkSetStringMacro(InputArrayName);
  vtkGetStringMacro(InputArrayName);

  // Description: 
  // Set/Get the name of the output array. Default is "ArrayMap".
  vtkSetStringMacro(OutputArrayName);
  vtkGetStringMacro(OutputArrayName);

  // Description: 
  // Set/Get the type of the output array. See vtkSetGet.h for possible values. 
  // Default is VTK_INT.
  vtkGetMacro(OutputArrayType, int);
  vtkSetMacro(OutputArrayType, int);

// Description:
// Add to the internal STL map. "from" should be a value in the input array and
// "to" should be the new value it gets assigned in the output array. 
  void AddToMap(vtkVariant from, vtkVariant to);
  void AddToMap(int from, int to);
  void AddToMap(int from, char *to);
  void AddToMap(char *from, int to);
  void AddToMap(char *from, char *to);

  // Description: 
  // Clear the internal map.
  void ClearMap();

  // Description: 
  // Get the size of the internal map.
  int GetMapSize();

//BTX
  // Always keep NUM_ATTRIBUTE_LOCS as the last entry
  enum FieldType
  {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      