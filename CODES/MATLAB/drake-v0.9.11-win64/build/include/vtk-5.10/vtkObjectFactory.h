/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkObjectFactory.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkObjectFactory - abstract base class for vtkObjectFactories
// .SECTION Description
// vtkObjectFactory is used to create vtk objects.   The base class
// vtkObjectFactory contains a static method CreateInstance which is used
// to create vtk objects from the list of registered vtkObjectFactory 
// sub-classes.   The first time CreateInstance is called, all dll's or shared
// libraries in the environment variable VTK_AUTOLOAD_PATH are loaded into
// the current process.   The C functions vtkLoad, vtkGetFactoryCompilerUsed, 
// and vtkGetFactoryVersion are called on each dll.  To implement these
// functions in a shared library or dll, use the macro:
// VTK_FACTORY_INTERFACE_IMPLEMENT.
// VTK_AUTOLOAD_PATH is an environment variable 
// containing a colon separated (semi-colon on win32) list of paths.
//
// The vtkObjectFactory can be use to override the creation of any object
// in VTK with a sub-class of that object.  The factories can be registered
// either at run time with the VTK_AUTOLOAD_PATH, or at compile time
// with the vtkObjectFactory::RegisterFactory method.
//



#ifndef __vtkObjectFactory_h
#define __vtkObjectFactory_h




#include "vtkObject.h"

class vtkObjectFactoryCollection;
class vtkOverrideInformationCollection;
class vtkCollection;

class VTK_COMMON_EXPORT vtkObjectFactory : public vtkObject
{
public:  
  // Class Methods used to interface with the registered factories
  
  // Description:
  // Create and return an instance of the named vtk object.
  // Each loaded vtkObjectFactory will be asked in the order
  // the factory was in the VTK_AUTOLOAD_PATH.  After the
  // first factory returns the object no other factories are asked.
  static vtkObject* CreateInstance(const char* vtkclassname);

  // Description:
  // Create all possible instances of the named vtk object.
  // Each registered vtkObjectFactory will be asked, and the
  // result will be stored in the user allocated vtkCollection
  // passed in to the function.
  static void CreateAllInstance(const char* vtkclassname,
                                vtkCollection* retList);
  // Description:
  // Re-check the VTK_AUTOLOAD_PATH for new factory libraries.
  // This calls UnRegisterAll before re-loading
  static void ReHash(); 
  // Description:
  // Register a factory so it can be used to create vtk objects
  static void RegisterFactory(vtkObjectFactory* );
  // Description:
  // Remove a factory from the list of registered factories
  static void UnRegisterFactory(vtkObjectFactory*);
  // Description:
  // Unregister all factories
  static void UnRegisterAllFactories();
  
  // Description:
  // Return the list of all registered factories.  This is NOT a copy,
  // do not remove items from this list!
  static vtkObjectFactoryCollection* GetRegisteredFactories();

  // Description: 
  // return 1 if one of the registered factories 
  // overrides the given class name
  static int HasOverrideAny(const char* className);
  
  // Description:
  // Fill the given collection with all the overrides for
  // the class with the given name.
  static void GetOverrideInformation(const char* name,
                                     vtkOverrideInformationCollection*);
  
  // Description:
  // Set the enable flag for a given named class for all registered
  // factories.
  static void SetAllEnableFlags(int flag, 
                                const char* className);
  // Description:
  // Set the enable flag for a given named class subclass pair
  // for all registered factories.
  static void SetAllEnableFlags(int flag, 
                                const char* className,
                                const char* subclassName);

  // Instance methods to be used on individual instances of vtkObjectFactory
  
  // Methods from vtkObject
  vtkTypeMacro(vtkObjectFactory,vtkObject);
  // Description:
  // Print ObjectFactory to stream.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // All sub-classes of vtkObjectFactory should must return the version of 
  // VTK they were built with.  This should be implemented with the macro
  // VTK_SOURCE_VERSION and NOT a call to vtkVersion::GetVTKSourceVersion.
  // As the version needs to be compiled into the file as a string constant.
  // This is critical to determine possible incompatible dynamic factory loads.
  virtual const char* GetVTKSourceVersion() = 0;

  // Description:
  // Return a descriptive string describing the factory.
  virtual const char* GetDescription() = 0;

  // Description:
  // Return number of overrides this factory can create.
  virtual int GetNumberOfOverrides();

  // Description:
  // Return the name of a class override at the given index.
  virtual const char* GetClassOverrideName(int index);

  // Description:
  // Return the name of the class that will override the class
  // at the given index
  virtual const char* GetClassOverrideWithName(int index);
  
  // Description:
  // Return the enable flag for the class at the given index.
  virtual int GetEnableFlag(int index);

  // Description:
  // Return the description for a the class override at the given 
  // index.
  virtual const char* GetOverrideDescription(int index);

  // Description:
  // Set and Get the Enable flag for the specific override of className.
  // if subclassName is null, then it is ignored.
  virtual void SetEnableFlag(int flag,
                             const char* className,
                             const char* subclassName);
  virtual int GetEnableFlag(const char* className,
                            const char* subclassName);

  // Description:
  // Return 1 if this factory overrides the given class name, 0 otherwise.
  virtual int HasOverride(const char* className);
  // Description:
  // Return 1 if this factory overrides the given class name, 0 otherwise.
  virtual int HasOverride(const char* className, const char* subclassName);
  
  // Description:
  // Set all enable flags for the given class to 0.  This will
  // mean that the factory will stop producing class with the given
  // name.
  virtual void Disable(const char* className);
  
  // Description:
  // This returns the path to a dynamically loaded factory.
  vtkGetStringMacro(LibraryPath);

  //BTX
  typedef vtkObject* (*CreateFunction)();
  //ETX
protected:
  //BTX

  // Description:
  // Register object creation information with the factory.
  void RegisterOverride(const char* classOverride,
                        const char* overrideClassName,
                        const char* description,
                        int enableFlag,
                        CreateFunction createFunction);
                
  //ETX

        
  // Description:
  // This method is provided by sub-classes of vtkObjectFactory.
  // It should create the named vtk object or return 0 if that object
  // is not supported by the factory implementation.
  virtual vtkObject* CreateObject(const char* vtkclassname );
  
  vtkObjectFactory();
  ~vtkObjectFactory();
  //BTX
  struct OverrideInformation
  {
    char* Description;
    char* OverrideWithName;
    int EnabledFlag;
    CreateFunction CreateCallback;
  };
  //ETX
  OverrideInformation* OverrideArray;
  char** OverrideClassNames;
  int SizeOverrideArray;
  int OverrideArrayLength;

private:
  void GrowOverrideArray();

  // Description:
  // Initialize the static members of vtkObje                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     