/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkFrameBufferObject.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkFrameBufferObject - internal class which encapsulates OpenGL
// frame buffer object. Not to be used directly.
// .SECTION Description
// Encapsulates an OpenGL Frame Buffer Object.
// For use by vtkOpenGLFBORenderWindow, not to be used directly.
// .SECTION Caveats
// DON'T PLAY WITH IT YET.
#ifndef __vtkFrameBufferObject_h
#define __vtkFrameBufferObject_h

#include "vtkObject.h"
#include "vtkSmartPointer.h" // needed for vtkSmartPointer.
#include "vtkWeakPointer.h" // needed for vtkWeakPointer.
//BTX
#include <vector> // for the lists of logical buffers.
//ETX

class vtkRenderWindow;
class vtkTextureObject;
class vtkOpenGLExtensionManager;

class VTK_RENDERING_EXPORT vtkFrameBufferObject : public vtkObject
{
public:
  static vtkFrameBufferObject* New();
  vtkTypeMacro(vtkFrameBufferObject, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get/Set the context. Context must be a vtkOpenGLRenderWindow. 
  // This does not increase the reference count of the 
  // context to avoid reference loops.
  // SetContext() may raise an error is the OpenGL context does not support the
  // required OpenGL extensions.
  void SetContext(vtkRenderWindow *context);
  vtkRenderWindow *GetContext();

  // Description:
  // User must take care that width/height match the dimensions of 
  // the user defined texture attachments.
  // This method makes the "active buffers" the buffers that will get drawn
  // into by subsequent drawing calls.
  // Note that this does not clear the render buffers i.e. no glClear() calls
  // are made by either of these methods. It's up to the caller to clear the
  // buffers if needed.
  bool Start(int width,
             int height,
             bool shaderSupportsTextureInt);
  bool StartNonOrtho(int width,
                     int height,
                     bool shaderSupportsTextureInt);

  // Description:
  // Renders a quad at the given location with pixel coordinates. This method
  // is provided as a convenience, since we often render quads in a FBO.
  // \pre positive_minX: minX>=0
  // \pre increasing_x: minX<=maxX
  // \pre valid_maxX: maxX<LastSize[0]
  // \pre positive_minY: minY>=0
  // \pre increasing_y: minY<=maxY
  // \pre valid_maxY: maxY<LastSize[1]
  void RenderQuad(int minX,
                  int maxX,
                  int minY,
                  int maxY);

  // Description:
  // Save the current framebuffer and make the frame buffer active.
  // Multiple calls to Bind has no effect.
  void Bind();

  // Description:
  // Restore the framebuffer saved with the call to Bind().
  // Multiple calls to UnBind has no effect.
  void UnBind();

  // Description:
  // Choose the buffer to render into.
  void SetActiveBuffer(unsigned int index)
    {
      this->SetActiveBuffers(1, &index);
    }
  
  // Description:
  // Choose the buffer to render into.
  // This is available only if the GL_ARB_draw_buffers extension is supported
  // by the card.
  void SetActiveBuffers(int numbuffers,
                        unsigned int indices[]);

  // All user specified texture objects must match the FBO dimensions
  // and must have been created by the time Start() gets called.
  // If texture is a 3D texture, zslice identifies the zslice that will be
  // attached to the color buffer.
  // .SECTION Caveat
  // Currently, 1D textures are not supported.
  void SetColor                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                