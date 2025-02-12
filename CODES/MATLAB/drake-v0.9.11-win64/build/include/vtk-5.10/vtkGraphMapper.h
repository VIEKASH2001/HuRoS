/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkGraphMapper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/
// .NAME vtkGraphMapper - map vtkGraph and derived 
// classes to graphics primitives

// .SECTION Description
// vtkGraphMapper is a mapper to map vtkGraph 
// (and all derived classes) to graphics primitives. 

#ifndef __vtkGraphMapper_h
#define __vtkGraphMapper_h

#include "vtkMapper.h"

#include "vtkSmartPointer.h"    // Required for smart pointer internal ivars.

class vtkActor2D;
class vtkMapArrayValues;
class vtkCamera;
class vtkFollower;
class vtkGraph;
class vtkGlyph3D;
class vtkGraphToPolyData;
class vtkIconGlyphFilter;
class vtkCellCenters;
class vtkPolyData;
class vtkPolyDataMapper;
class vtkPolyDataMapper2D;
class vtkLookupTable;
class vtkTransformCoordinateSystems;
class vtkTexture;
class vtkTexturedActor2D;
class vtkVertexGlyphFilter;
class vtkViewTheme;



class VTK_RENDERING_EXPORT vtkGraphMapper : public vtkMapper 
{
public:
  static vtkGraphMapper *New();
  vtkTypeMacro(vtkGraphMapper,vtkMapper);
  void PrintSelf(ostream& os, vtkIndent indent);
  void Render(vtkRenderer *ren, vtkActor *act);
  
  // Description:
  // The array to use for coloring vertices.  Default is "color".
  void SetVertexColorArrayName(const char* name);
  const char* GetVertexColorArrayName();
  
  // Description:
  // Whether to color vertices.  Default is off.
  void SetColorVertices(bool vis);
  bool GetColorVertices();
  void ColorVerticesOn();
  void ColorVerticesOff();
  
  // Description:
  // Whether scaled glyphs are on or not.  Default is off.
  // By default this mapper uses vertex glyphs that do not
  // scale. If you turn this option on you will get circles
  // at each vertex and they will scale as you zoom in/out.
  void SetScaledGlyphs(bool arg);
  vtkGetMacro(ScaledGlyphs,bool);
  vtkBooleanMacro(ScaledGlyphs, bool);
  
  // Description:
  // Glyph scaling array name. Default is "scale"
  vtkSetStringMacro(ScalingArrayName);
  vtkGetStringMacro(ScalingArrayName);
  
  // Description:
  // Whether to show edges or not.  Default is on.
  void SetEdgeVisibility(bool vis);
  bool GetEdgeVisibility();
  vtkBooleanMacro(EdgeVisibility, bool);
  
  // Description:
  // The array to use for coloring edges.  Default is "color".
  void SetEdgeColorArrayName(const char* name);
  const char* GetEdgeColorArrayName();
  
  // Description:
  // Whether to color edges.  Default is off.
  void SetColorEdges(bool vis);
  bool GetColorEdges();
  void ColorEdgesOn();
  void ColorEdgesOff();
  
  // Description:
  // The array to use for coloring edges.  Default is "color".
  vtkSetStringMacro(EnabledEdgesArrayName);
  vtkGetStringMacro(EnabledEdgesArrayName);
  
  // Description:
  // Whether to enable/disable edges using array values.  Default is off.
  vtkSetMacro(EnableEdgesByArray,int);
  vtkGetMacro(EnableEdgesByArray,int);
  vtkBooleanMacro(EnableEdgesByArray,int);

  // Description:
  // The array to use for coloring edges.  Default is "color".
  vtkSetStringMacro(EnabledVerticesArrayName);
  vtkGetStringMacro(EnabledVerticesArrayName);
  
  // Description:
  // Whether to enable/disable vertices using array valu                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 