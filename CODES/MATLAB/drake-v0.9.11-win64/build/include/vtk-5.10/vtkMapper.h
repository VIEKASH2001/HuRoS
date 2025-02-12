/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMapper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMapper - abstract class specifies interface to map data to graphics primitives
// .SECTION Description
// vtkMapper is an abstract class to specify interface between data and 
// graphics primitives. Subclasses of vtkMapper map data through a 
// lookuptable and control the creation of rendering primitives that
// interface to the graphics library. The mapping can be controlled by 
// supplying a lookup table and specifying a scalar range to map data
// through.
//
// There are several important control mechanisms affecting the behavior of
// this object. The ScalarVisibility flag controls whether scalar data (if
// any) controls the color of the associated actor(s) that refer to the
// mapper. The ScalarMode ivar is used to determine whether scalar point data
// or cell data is used to color the object. By default, point data scalars
// are used unless there are none, in which cell scalars are used. Or you can
// explicitly control whether to use point or cell scalar data. Finally, the
// mapping of scalars through the lookup table varies depending on the
// setting of the ColorMode flag. See the documentation for the appropriate
// methods for an explanation.
//
// Another important feature of this class is whether to use immediate mode
// rendering (ImmediateModeRenderingOn) or display list rendering
// (ImmediateModeRenderingOff). If display lists are used, a data structure
// is constructed (generally in the rendering library) which can then be
// rapidly traversed and rendered by the rendering library. The disadvantage
// of display lists is that they require additionally memory which may affect
// the performance of the system.
//
// Another important feature of the mapper is the ability to shift the
// z-buffer to resolve coincident topology. For example, if you'd like to
// draw a mesh with some edges a different color, and the edges lie on the
// mesh, this feature can be useful to get nice looking lines. (See the
// ResolveCoincidentTopology-related methods.)

// .SECTION See Also
// vtkDataSetMapper vtkPolyDataMapper

#ifndef __vtkMapper_h
#define __vtkMapper_h

#include "vtkAbstractMapper3D.h"
#include "vtkScalarsToColors.h" // For VTK_COLOR_MODE_DEFAULT and _MAP_SCALARS

#define VTK_RESOLVE_OFF 0
#define VTK_RESOLVE_POLYGON_OFFSET 1
#define VTK_RESOLVE_SHIFT_ZBUFFER 2

#define VTK_GET_ARRAY_BY_ID 0
#define VTK_GET_ARRAY_BY_NAME 1

#define VTK_MATERIALMODE_DEFAULT  0
#define VTK_MATERIALMODE_AMBIENT  1
#define VTK_MATERIALMODE_DIFFUSE  2
#define VTK_MATERIALMODE_AMBIENT_AND_DIFFUSE  3

class vtkWindow;
class vtkRenderer;
class vtkActor;
class vtkDataSet;
class vtkFloatArray;
class vtkImageData;

class VTK_RENDERING_EXPORT vtkMapper : public vtkAbstractMapper3D
{
public:
  vtkTypeMacro(vtkMapper,vtkAbstractMapper3D);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Make a shallow copy of this mapper.
  void ShallowCopy(vtkAbstractMapper *m);

  // Description:
  // Overload standard modified time function. If lookup table is modified,
  // then this object is modified as well.
  unsigned long GetMTime();

  // Description:
  // Method initiates the mapping process. Generally sent by the actor 
  // as each frame is rendered.
  virtual void Render(vtkRenderer *ren, vtkActor *a) = 0;

  // Description:
  // Release any graphics resources that are being consumed by this mapper.
  // The parameter window could be used to determine which graphic
  // resources to release.
  virtual void ReleaseGraphicsResources(vtkWindow *) {};

  // Description:
  // Specify a lookup table for the mapper to use.
  void SetLookupTable(vtkScalarsToColors *lut);
  vtkScalarsToColors *GetLookupTable();

  // Description:
  // Create default lookup table. Generally used to create one when none
  // is available with the scalar data.
  virtual void CreateDefaultLookupTable();

  // Description:
  // Turn on/off flag to control whether scalar data is used to color objects.
  vtkSetMacro(ScalarVisibility,int);
  vtkGetMacro(ScalarVisibility,int);
  vtkBooleanMacro(ScalarVisibility,int);

  // Description:
  // Turn on/off flag to control whether the mapper's data is static. Static data
  // means that the mapper does not propagate updates down the pipeline, greatly
  // decreasing the time it takes to update many mappers. This should only be
  // used if the data never changes.
  vtkSetMacro(Static,int);
  vtkGetMacro(Static,int);
  vtkBooleanMacro(Static,int);

  // Description:
  // Control how the scalar data is mapped to colors.  By default
  // (ColorModeToDefault), unsigned char scalars are treated as colors, and
  // NOT mapped through the lookup table, while everything else is. Setting
  // ColorModeToMapScalars means that all scalar data will be mapped through
  // the lookup table.  (Note that for multi-component scalars, the
  // particular component to use for mapping can be specified using the
  // SelectColorArray() method.)
  vtkSetMacro(ColorMode,int);
  vtkGetMacro(ColorMode,int);
  void SetColorModeToDefault() 
    {this->SetColorMode(VTK_COLOR_MODE_DEFAULT);};
  void SetColorModeToMapScalars() 
    {this->SetColorMode(VTK_COLOR_MODE_MAP_SCALARS);};

  // Description:
  // Return the method of coloring scalar data.
  const char *GetColorModeAsString();

  // Description:
  // By default, vertex color is used to map colors to a surface.
  // Colors are interpolated after being mapped.
  // This option avoids color interpolation by using a one dimensional
  // texture map for the colors.
  vtkSetMacro(InterpolateScalarsBeforeMapping,int);
  vtkGetMacro(InterpolateScalarsBeforeMapping,int);
  vtkBooleanMacro(InterpolateScalarsBeforeMapping,int);

  // Description:
  // Control whether the mapper sets the lookuptable range based on its
  // own ScalarRange, or whether it will use the LookupTable ScalarRange
  // regardless of it's own setting. By default the Mapper is allowed to set
  // the LookupTable range, but users who are sharing LookupTables between
  // mappers/actors will probably wish to force the mapper to use the
  // LookupTable unchanged.
  vtkSetMacro(UseLookupTableScalarRange,int);
  vtkGetMacro(UseLookupTableScalarRange,int);
  vtkBooleanMacro(UseLookupTableScalarRange,int);

  // Description:
  // Specify range in terms of scalar minimum and maximum (smin,smax). These
  // values are used to map scalars into lookup table. Has no effect when
  // UseLookupTableScalarRange is true.
  vtkSetVector2Macro(ScalarRange,double);
  vtkGetVectorMacro(ScalarRange,double,2);

  // Description:
  // Turn on/off flag to control whether data is rendered using
  // immediate mode or note. Immediate mode rendering
  // tends to be slower but it can handle larger datasets.
  // The default value is immediate mode off. If you are
  // having problems rendering a large dataset you might
  // want to consider using immediate more rendering.
  vtkSetMacro(ImmediateModeRendering,int);
  vtkGetMacro(ImmediateModeRendering,int);
  vtkBooleanMacro(ImmediateModeRendering,int);

  // Description:
  // Turn on/off flag to control whether data is rendered using
  // immediate mode or note. Immediate mode rendering
  // tends to be slower but it can handle larger datasets.
  // The default value is immediate mode off. If you are 
  // having problems rendering a large dataset you might
  // want to consider using immediate more rendering.
  static void SetGlobalImmediateModeRendering(int val);
  static void GlobalImmediateModeRenderingOn() 
    {vtkMapper::SetGlobalImmediateModeRendering(1);};
  static void GlobalImmediateModeRenderingOff() 
    {vtkMapper::SetGlobalImmediateModeRendering(0);};
  static int  GetGlobalImmediateModeRendering();

  //BTX
  // Description:
  // Force compile only mode in case display lists are used
  // (ImmediateModeRendering is false). If ImmediateModeRendering is true,
  // no rendering happens. Changing the value of this flag does not change
  // modified time of the mapper. Initial value is false.
  // This can be used by another rendering class which also uses display lists
  // (call of display lists can be nested but not their creation.)
  // There is no good reason to expose it to wrappers.
  vtkGetMacro(ForceCompileOnly,int);
  void SetForceCompileOnly(int value);
  //ETX

  // Description:
  // Control how the filter works with scalar point data and cell attribute
  // data.  By default (ScalarModeToDefault), the filter will use point data,
  // and if no point data is available, then cell data is used. Alternatively
  // you can explicitly set the filter to use point data
  // (ScalarModeToUsePointData) or cell data (ScalarModeToUseCellData).
  // You can also choose to get the scalars from an array in point field
  // data (ScalarModeToUsePointFieldData) or cell field data
  // (ScalarModeToUseCellFieldData).  If scalars are coming from a field
  // data array, you must call SelectColorArray before you call
  // GetColors.
  // When ScalarMode is set to use Field Data (ScalarModeToFieldData), you 
  // must call SelectColorArray to choose the field data array to be used to
  // color cells. In this mode, if the poly data has triangle strips, 
  // the field data is treated as the celldata for each mini-cell formed by
  // a triangle in the strip rather than the entire strip.
  vtkSetMacro(ScalarMode,int);
  vtkGetMacro(ScalarMode,int);
  void SetScalarModeToDefault() {
    this->SetScalarMode(VTK_SCALAR_MODE_DEFAULT);};
  void SetScalarModeToUsePointData() {
    this->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_DATA);};
  void SetScalarModeToUseCellData() {
    this->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_DATA);};
  void SetScalarModeToUsePointFieldData() {
    this->SetScalarMode(VTK_SCALAR_MODE_USE_POINT_FIELD_DATA);};
  void SetScalarModeToUseCellFieldData() {
    this->SetScalarMode(VTK_SCALAR_MODE_USE_CELL_FIELD_DATA);};
  void SetScalarModeToUseFieldData() {
    this->SetScalarMode(VTK_SCALAR_MODE_USE_FIELD_DATA); }
  
  // Description:
  // When ScalarMode is set to UsePointFieldData or UseCellFieldData,
  // you can specify which array to use for coloring using these methods.
  // The lookup table will decide how to convert vectors to colors.
  void SelectColorArray(int arrayNum); 
  void SelectColorArray(const char* arrayName); 

  // Description:
  // Legacy:
  // These methods used to be used to specify the array component.
  // It is better to do this in the lookup table.
  void ColorByArrayComponent(int arrayNum, int component);
  void ColorByArrayComponent(const char* arrayName, int component);
  
  // Description:
  // Get the array name or number and component to color by.
  char* GetArrayName() { return this->ArrayName; }
  int GetArrayId() { return this->ArrayId; }
  int GetArrayAccessMode() { return this->ArrayAccessMode; }
  int GetArrayComponent() { return this->ArrayComponent; }

  // Description:
  // Return the method for obtaining scalar data.
  const char *GetScalarModeAsString();

  // Description:
  // Set/Get a global flag that controls whether coincident topology (e.g., a
  // line on top of a polygon) is shifted to avoid z-buffer resolution (and
  // hence rendering problems). If not off, there are two methods to choose
  // from. PolygonOffset uses graphics systems calls to shift polygons, but
  // does not distinguish vertices and lines from one another. ShiftZBuffer
  // remaps the z-buffer to distinguish vertices, lines, an                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              