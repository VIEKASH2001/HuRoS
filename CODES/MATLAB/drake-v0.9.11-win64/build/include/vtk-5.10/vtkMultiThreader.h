                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                t                 NumberOfThreads;
    int                 *ActiveFlag;
    vtkMutexLock        *ActiveFlagLock;
    void                *UserData;
  };
  //ETX

  // Description:
  // Get/Set the number of threads to create. It will be clamped to the range
  // 1 - VTK_MAX_THREADS, so the caller of this method should check that the
  // requested number of threads was accepted.
  vtkSetClampMacro( NumberOfThreads, int, 1, VTK_MAX_THREADS );
  virtual int GetNumberOfThreads();

  // Description:
  // Set/Get the maximum number of threads to use when multithreading.
  // This limits and overrides any other settings for multithreading.
  // A value of zero indicates no limit.
  static void SetGlobalMaximumNumberOfThreads(int val);
  static int  GetGlobalMaximumNumberOfThreads();

  // Description:
  // Set/Get the value which is used to initialize the NumberOfThreads
  // in the constructor.  Initially this default is set to the number of 
  // processors or VTK_MAX_THREADS (which ever is less).
  static void SetGlobalDefaultNumberOfThreads(int val);
  static int  GetGlobalDefaultNumberOfThreads();

  // These methods are excluded from Tcl wrapping 1) because the
  // wrapper gives up on them and 2) because they really shouldn't be
  // called from a script anyway.
  //BTX 
  
  // Description:
  // Execute the SingleMethod (as define by SetSingleMethod) using
  // this->NumberOfThreads threads.
  void SingleMethodExecute();

  // Description:
  // Execute the MultipleMethods (as define by calling SetMultipleMethod
  // for each of the required this->NumberOfThreads methods) using
  // this->NumberOfThreads threads.
  void MultipleMethodExecute();
  
  // Description:
  // Set the SingleMethod to f() and the UserData field of the
  // ThreadInfo that is passed to it will be data.
  // This method (and all the methods passed to SetMultipleMethod)
  // must be of type vtkThreadFunctionType and must take a single argument of
  // type void *.
  void SetSingleMethod(vtkThreadFunctionType, void *data );
 
  // Description:
  // Set the MultipleMethod at the given index to f() and the UserData 
  // field of the ThreadInfo that is passed to it will be data.
  void SetMultipleMethod( int index, vtkThreadFunctionType, void *data ); 

  // Description:
  // Create a new thread for the given function. Return a thread id
  // which is a number between 0 and VTK_MAX_THREADS - 1. This id should
  // be used to kill the thread at a later time.
  int SpawnThread( vtkThreadFunctionType, void *data );

  // Description:
  // Terminate the thread that was created with a SpawnThreadExecute()
  void TerminateThread( int thread_id );

  // Description:
  // Determine if a thread is still active
  int IsThreadActive( int threadID );
  
  // Description:
  // Get the thread identifier of the calling thread.
  static vtkMultiThreaderIDType GetCurrentThreadID();

  // Description:
  // Check whether two thread identifiers refer to the same thread.
  static int ThreadsEqual(vtkMultiThreaderIDType t1,
                          vtkMultiThreaderIDType t2);

protected:
  vtkMultiThreader();
  ~vtkMultiThreader();

  // The number of threads to use
  int                        NumberOfThreads;

  // An array of thread info containing a thread id
  // (0, 1, 2, .. VTK_MAX_THREADS-1), the thread count, and a pointer
  // to void so that user data can be passed to each thread
  ThreadInfo                 ThreadInfoArray[VTK_MAX_THREADS];

  // The methods
  vtkThreadFunctionType      SingleMethod;
  vtkThreadFunctionType      MultipleMethod[VTK_MAX_THREADS];

  // Storage of MutexFunctions and ints used to control spawned 
  // threads and the spawned thread ids
  int                        SpawnedThreadActiveFlag[VTK_MAX_THREADS];
  vtkMutexLock               *SpawnedThreadActiveFlagLock[VTK_MAX_THREADS];
  vtkThreadProcessIDType     SpawnedThreadProcessID[VTK_MAX_THREADS];
  ThreadInfo                 SpawnedThreadInfoArray[VTK_MAX_THREADS];

//ETX

  // Internal storage of the data
  void                       *SingleData;
  void                       *MultipleData[VTK_MAX_THREADS];

private:
  vtkMultiThreader(const vtkMultiThreader&);  // Not implemented.
  void operator=(const vtkMultiThreader&);  // Not implemented.
};

#endif





