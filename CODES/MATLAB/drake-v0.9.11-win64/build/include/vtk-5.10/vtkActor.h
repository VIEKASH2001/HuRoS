/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkActor.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkActor - represents an object (geometry & properties) in a rendered scene 
// .SECTION Description
// 
// vtkActor is used to represent an entity in a rendering scene.  It inherits
// functions related to the actors position, and orientation from
// vtkProp. The actor also has scaling and maintains a reference to the
// defining geometry (i.e., the mapper), rendering properties, and possibly a
// texture map. vtkActor combines these instance variables into one 4x4
// transformation matrix as follows: [x y z 1] = [x y z 1] Translate(-origin)
// Scale(scale) Rot(y) Rot(x) Rot (z) Trans(origin) Trans(position)

// .SECTION See Also
// vtkProperty vtkTexture vtkMapper vtkAssembly vtkFollower vtkLODActor

#ifndef __vtkActor_h
#define __vtkActor_h

#include "vtkProp3D.h"

class vtkRenderer;
class vtkPropCollection;
class vtkActorCollection;
class vtkTexture;
class vtkMapper;
class vtkProperty;

class VTK_RENDERING_EXPORT vtkActor : public vtkProp3D
{
public:
  vtkTypeMacro(vtkActor,vtkProp3D);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Creates an actor with the following defaults: origin(0,0,0)
  // position=(0,0,0) scale=(1,1,1) visibility=1 pickable=1 dragable=1
  // orientation=(0,0,0). No user defined matrix and no texture map.
  static vtkActor *New();

  // Description: 
  // For some exporters and other other operations we must be
  // able to collect all the actors or volumes. These methods
  // are used in that process.
  virtual void GetActors(vtkPropCollection *);

  // Description:
  // Support the standard render methods.
  virtual int RenderOpaqueGeometry(vtkViewport *viewport);
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport *viewport);
  
  // Description:
  // Does this prop have some translucent polygonal geometry?
  virtual int HasTranslucentPolygonalGeometry();
  
  // Description:
  // This causes the actor to be rendered. It in turn will render the actor's
  // property, texture map and then mapper. If a property hasn't been
  // assigned, then the actor will create one automatically. Note that a side
  // effect of this method is that the pipeline will be updated.
  virtual void Render(vtkRenderer *, vtkMapper *) {}

  // Description:
  // Shallow copy of an actor. Overloads the virtual vtkProp method.
  void ShallowCopy(vtkProp *prop);

  // Description:
  // Release any graphics resources that are being consumed by this actor.
  // The parameter window could be used to determine which graphic
  // resources to release.
  void ReleaseGraphicsResources(vtkWindow *);

  // Description: 
  // Set/Get the property object that controls this actors surface
  // properties.  This should be an instance of a vtkProperty object.  Every
  // actor must have a property associated with it.  If one isn't specified,
  // then one will be generated automatically. Multiple actors can share one
  // property object.
  void SetProperty(vtkProperty *lut);
  vtkProperty *GetProperty();
  
  // Description:
  // Create a new property suitable for use with this type of Actor.
  // For example, a vtkMesaActor should create a vtkMesaProperty 
  // in this function.   The default is to just call vtkProperty::New.
  virtual vtkProperty* MakeProperty();

  // Description: 
  // Set/Get the property object that controls this actors backface surface
  // properties.  This should be an instance of a vtkProperty ob                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     