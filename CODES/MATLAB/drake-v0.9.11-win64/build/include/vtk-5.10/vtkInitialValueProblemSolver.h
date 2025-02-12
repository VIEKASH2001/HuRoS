                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                tion:
  // Set / get the dataset used for the implicit function evaluation.
  virtual void SetFunctionSet(vtkFunctionSet* functionset);
  vtkGetObjectMacro(FunctionSet,vtkFunctionSet);

  // Description:
  // Returns 1 if the solver uses adaptive stepsize control,
  // 0 otherwise
  virtual int IsAdaptive() { return this->Adaptive; }
  
//BTX
  enum ErrorCodes
  {
    OUT_OF_DOMAIN = 1,
    NOT_INITIALIZED = 2,
    UNEXPECTED_VALUE = 3
  };
//ETX

protected:
  vtkInitialValueProblemSolver();
  ~vtkInitialValueProblemSolver();

  virtual void Initialize();

  vtkFunctionSet* FunctionSet;

  double* Vals;
  double* Derivs;
  int Initialized;
  int Adaptive;

private:
  vtkInitialValueProblemSolver(const vtkInitialValueProblemSolver&);  // Not implemented.
  void operator=(const vtkInitialValueProblemSolver&);  // Not implemented.
};

#endif




