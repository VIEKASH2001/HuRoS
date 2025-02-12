                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                Widget, vtkInteractorObserver);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/get the orientation marker to be displayed in this widget.
  virtual void SetOrientationMarker(vtkProp *prop);
  vtkGetObjectMacro(OrientationMarker, vtkProp);

  // Description:
  // Enable/disable the widget. Default is 0 (disabled).
  virtual void SetEnabled(int);

  // Description:
  // Callback to keep the camera for the orientation marker up to date with the
  // camera in the parent renderer.
  void ExecuteCameraUpdateEvent(vtkObject *o, unsigned long event, void *calldata);

  // Description:
  // Set/get whether to allow this widget to be interactively moved/scaled.
  // Default is On.
  void SetInteractive(int state);
  vtkGetMacro(Interactive, int);
  vtkBooleanMacro(Interactive, int);

  // Description:
  // Set/get the color of the outline of this widget.  The outline is visible
  // when (in interactive mode) the cursor is over this widget.
  // Default is white (1,1,1).
  void SetOutlineColor(double r, double g, double b);
  double *GetOutlineColor();

  // Description:
  // Set/get the viewport to position/size this widget.
  // Default is bottom left corner (0,0,0.2,0.2).
  void SetViewport(double minX, double minY, double maxX, double maxY);
  double* GetViewport();

  // Description:
  // The tolerance representing the distance to the widget (in pixels)
  // in which the cursor is considered to be on the widget, or on a
  // widget feature (e.g., a corner point or edge).
  vtkSetClampMacro(Tolerance,int,1,10);
  vtkGetMacro(Tolerance,int);

protected:
  vtkOrientationMarkerWidget();
  ~vtkOrientationMarkerWidget();

  vtkRenderer *Renderer;
  vtkProp     *OrientationMarker;
  vtkPolyData *Outline;
  vtkActor2D  *OutlineActor;

  unsigned long StartEventObserverId;
  
  static void ProcessEvents(vtkObject *object, unsigned long event,
                            void *clientdata, void *calldata);

  // ProcessEvents() dispatches to these methods.
  void OnLeftButtonDown();
  void OnLeftButtonUp();
  void OnMouseMove();

  // observer to update the renderer's camera
  vtkOrientationMarkerWidgetObserver *Observer;

  int Interactive;
  int Tolerance;
  int Moving;

  // used to compute relative movements
  int StartPosition[2];

//BTX - manage the state of the widget
  int State;
  enum WidgetState
  {
    Outside = 0,
    Inside,
    Translating,
    AdjustingP1,
    AdjustingP2,
    AdjustingP3,
    AdjustingP4
  };
//ETX


  // use to determine what state the mouse is over, edge1 p1, etc.
  // returns a state from the WidgetState enum above
  int ComputeStateBasedOnPosition(int X, int Y, int *pos1, int *pos2);

  // set the cursor to the correct shape based on State argument
  void SetCursor(int state);

  // adjust the viewport depending on state
  void MoveWidget(int X, int Y);
  void ResizeTopLeft(int X, int Y);
  void ResizeTopRight(int X, int Y);
  void ResizeBottomLeft(int X, int Y);
  void ResizeBottomRight(int X, int Y);

  void SquareRenderer();
  void UpdateOutline();

private:
  vtkOrientationMarkerWidget(const vtkOrientationMarkerWidget&);  // Not implemented
  void operator=(const vtkOrientationMarkerWidget&);  // Not implemented
};

#endif
