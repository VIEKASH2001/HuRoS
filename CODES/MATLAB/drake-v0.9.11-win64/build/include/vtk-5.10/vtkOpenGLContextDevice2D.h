                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ring);

  // Description:
  // Compute the bounds of the supplied string. The bounds will be copied to the
  // supplied bounds variable, the first two elements are the bottom corner of
  // the string, and the second two elements are the width and height of the
  // bounding box.
  // NOTE: This function does not take account of the text rotation.
  virtual void ComputeStringBounds(const vtkStdString &string,
                                   float bounds[4]);

  // Description:
  // Draw some text to the screen.
  virtual void DrawString(float *point, const vtkUnicodeString &string);

  // Description:
  // Compute the bounds of the supplied string. The bounds will be copied to the
  // supplied bounds variable, the first two elements are the bottom corner of
  // the string, and the second two elements are the width and height of the
  // bounding box.
  // NOTE: This function does not take account of the text rotation.
  virtual void ComputeStringBounds(const vtkUnicodeString &string,
                                   float bounds[4]);

  // Description:
  // Draw the supplied image at the given x, y (p[0], p[1]) (bottom corner),
  // scaled by scale (1.0 would match the image).
  virtual void DrawImage(float p[2], float scale, vtkImageData *image);

  // Description:
  // Draw the supplied image at the given position. The origin, width, and
  // height are specified by the supplied vtkRectf variable pos. The image
  // will be drawn scaled to that size.
  void DrawImage(const vtkRectf& pos, vtkImageData *image);

  // Description:
  // Set the color for the device using unsigned char of length 4, RGBA.
  virtual void SetColor4(unsigned char color[4]);

  // Description:
  // Set the color for the device using unsigned char of length 3, RGB.
  virtual void SetColor(unsigned char color[3]);

  // Description:
  // Set the texture for the device, it is used to fill the polygons
  virtual void SetTexture(vtkImageData* image, int properties = 0);

  // Description:
  // Set the point size for glyphs/sprites.
  virtual void SetPointSize(float size);

  // Description:
  // Set the line width for glyphs/sprites.
  virtual void SetLineWidth(float width);

  // Description:
  // Set the line type type (using anonymous enum in vtkPen).
  virtual void SetLineType(int type);

  // Description:
  // Multiply the current model view matrix by the supplied one.
  virtual void MultiplyMatrix(vtkMatrix3x3 *m);

  // Description:
  // Set the model view matrix for the display
  virtual void SetMatrix(vtkMatrix3x3 *m);

  // Description:
  // Set the model view matrix for the display
  virtual void GetMatrix(vtkMatrix3x3 *m);

  // Description:
  // Push the current matrix onto the stack.
  virtual void PushMatrix();

  // Description:
  // Pop the current matrix off of the stack.
  virtual void PopMatrix();

  // Description:
  // Supply an int array of length 4 with x1, y1, x2, y2 specifying clipping
  // for the display.
  virtual void SetClipping(int *x);

  // Description:
  // Disable clipping of the display.
  virtual void EnableClipping(bool enable);

  // Description:
  // Begin drawing, pass in the viewport to set up the view.
  virtual void Begin(vtkViewport* viewport);

  // Description:
  // End drawing, clean up the view.
  virtual void End();

  // Description:
  // Start BufferId creation Mode.
  // The default implementation is empty.
  // \pre not_yet: !GetBufferIdMode()
  // \pre bufferId_exists: bufferId!=0
  // \post started: GetBufferIdMode()
  virtual void BufferIdModeBegin(vtkAbstractContextBufferId *bufferId);

  // Description:
  // Finalize BufferId creation Mode. It makes sure that the content of the
  // bufferId passed in argument of BufferIdModeBegin() is correctly set.
  // The default implementation is empty.
  // \pre started: GetBufferIdMode()
  // \post done: !GetBufferIdMode()
  virtual void BufferIdModeEnd();

  // Description:
  // Force the use of the freetype based render strategy. If Qt is available
  // then freetype will be used preferentially, otherwise this has no effect.
  // Returns true on success.
  bool SetStringRendererToFreeType();

  // Description:
  // Force the use of the Qt based string render strategy. If Qt is not available
  // then freetype will be used and this will return false.
  bool SetStringRendererToQt();

  // Description:
  // Check whether the current context device has support for GLSL.
  bool HasGLSL();

  // Description:
  // Get the active RenderWindow of the device. Will return null if not active.
  vtkGetObjectMacro(RenderWindow, vtkOpenGLRenderWindow);

  // Description:
  // Release any graphics resources that are being consumed by this device.
  // The parameter window could be used to determine which graphic
  // resources to release.
  virtual void ReleaseGraphicsResources(vtkWindow *window);

//BTX
protected:
  vtkOpenGLContextDevice2D();
  virtual ~vtkOpenGLContextDevice2D();

  // Description:
  // Factorized code called by DrawEllipseWedge() and DrawEllipticArc()
  // to figure out the number of iterations required to make an arc smooth.
  // \pre positive_rX: rX>=0.0f
  // \pre positive_rY: rY>=0.0f
  // \pre not_both_null: rX>0.0 || rY>0.0
  int GetNumberOfArcIterations(float rX,
                               float rY,
                               float startAngle,
                               float stopAngle);

  // Description:
  // Store the width and height of the display devicen (in pixels).
  int Geometry[2];

  // Description:
  // We need to store a pointer to the renderer for the text rendering
  vtkRenderer *Renderer;

  // Description:
  // We also need a label render strategy
  vtkStringToImage *TextRenderer;

  // Description:
  // Is the device currently rendering? Prevent multiple End() calls.
  bool InRender;

  // Description:
  // Private data pointer of the class
  class Private;
  Private *Storage;

  // Description:
  // Load the OpenGL extensions we need.
  virtual bool LoadExtensions(vtkOpenGLExtensionManager *m);

  // Description:
  // The OpenGL render window being used by the device
  vtkOpenGLRenderWindow* RenderWindow;

private:
  vtkOpenGLContextDevice2D(const vtkOpenGLContextDevice2D &); // Not implemented.
  void operator=(const vtkOpenGLContextDevice2D &);   // Not implemented.

  void AlignText(double orientation, float width, float height, float *p);

//ETX
};

#endif //__vtkOpenGLContextDevice2D_h
