/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkLabelPlacementMapper.h

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
// .NAME vtkLabelPlacementMapper - Places and renders non-overlapping labels.
//
// .SECTION Description
// To use this mapper, first send your data through vtkPointSetToLabelHierarchy,
// which takes a set of points, associates special arrays to the points (label,
// priority, etc.), and produces a prioritized spatial tree of labels.
//
// This mapper then takes that hierarchy (or hierarchies) as input, and every
// frame will decide which labels and/or icons to place in order of priority,
// and will render only those labels/icons. A label render strategy is used to
// render the labels, and can use e.g. FreeType or Qt for rendering.

#ifndef __vtkLabelPlacementMapper_h
#define __vtkLabelPlacementMapper_h

#include "vtkMapper2D.h"

class vtkCoordinate;
class vtkLabelRenderStrategy;
class vtkSelectVisiblePoints;

class VTK_RENDERING_EXPORT vtkLabelPlacementMapper : public vtkMapper2D
{
public:
  static vtkLabelPlacementMapper *New();
  vtkTypeMacro(vtkLabelPlacementMapper, vtkMapper2D);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Draw non-overlapping labels to the screen.
  void RenderOverlay(vtkViewport *viewport, vtkActor2D *actor);

  // Description:
  // Set the label rendering strategy.
  virtual void SetRenderStrategy(vtkLabelRenderStrategy* s);
  vtkGetObjectMacro(RenderStrategy, vtkLabelRenderStrategy);

  // Description:
  // The maximum fraction of the screen that the labels may cover.
  // Label placement stops when this fraction is reached.
  vtkSetClampMacro(MaximumLabelFraction,double,0.,1.);
  vtkGetMacro(MaximumLabelFraction,double);

  // Description:
  // The type of iterator used when traversing the labels.
  // May be vtkLabelHierarchy::FRUSTUM or vtkLabelHierarchy::FULL_SORT
  vtkSetMacro(IteratorType,int);
  vtkGetMacro(IteratorType,int);

  // Description:
  // Set whether, or not, to use unicode strings.
  vtkSetMacro(UseUnicodeStrings,bool);
  vtkGetMacro(UseUnicodeStrings,bool);
  vtkBooleanMacro(UseUnicodeStrings,bool);

  // Description:
  // Use label anchor point coordinates as normal vectors and eliminate those
  // pointing away from the camera. Valid only when points are on a sphere
  // centered at the origin (such as a 3D geographic view). Off by default.
  vtkGetMacro(PositionsAsNormals,bool);
  vtkSetMacro(PositionsAsNormals,bool);
  vtkBooleanMacro(PositionsAsNormals,bool);

  // Description:
  // Enable drawing spokes (lines) to anchor point coordinates that were perturbed
  // for being coincident with other anchor point coordinates.
  vtkGetMacro(GeneratePerturbedLabelSpokes,bool);
  vtkSetMacro(GeneratePerturbedLabelSpokes,bool);
  vtkBooleanMacro(GeneratePerturbedLabelSpokes,bool);

  // Description:
  // Use the depth buffer to test each label to see if it should not be displayed if
  // it would be occluded by other objects in the scene. Off by default.
  vtkGetMacro(UseDepthBuffer,bool);
  vtkSetMacro(UseDepthBuffer,bool);
  vtkBooleanMacro(UseDepthBuffer,bool);

  // Description:
  // Tells the placer to place every label regardless of overlap.
  /                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            