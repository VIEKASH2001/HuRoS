/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMatrix3x3.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMatrix3x3 - represent and manipulate 3x3 transformation matrices
// .SECTION Description
// vtkMatrix3x3 is a class to represent and manipulate 3x3 matrices.
// Specifically, it is designed to work on 3x3 transformation matrices
// found in 2D rendering using homogeneous coordinates [x y w].

// .SECTION See Also
// vtkTransform2D

#ifndef __vtkMatrix3x3_h
#define __vtkMatrix3x3_h

#include "vtkObject.h"

class VTK_COMMON_EXPORT vtkMatrix3x3 : public vtkObject
{
  // Some of the methods in here have a corresponding static (class)
  // method taking a pointer to 9 doubles that constitutes a user
  // supplied matrix. This allows C++ clients to allocate double arrays
  // on the stack and manipulate them using vtkMatrix3x3 methods.
  // This is an alternative to allowing vtkMatrix3x3 instances to be
  // created on the stack (which is frowned upon) or doing lots of
  // temporary heap allocation within vtkTransform2D methods,
  // which is inefficient.

public:
  // Description:
  // Construct a 3x3 identity matrix.
  static vtkMatrix3x3 *New();

  vtkTypeMacro(vtkMatrix3x3,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the elements of the matrix to the same values as the elements
  // of the source Matrix.
  void DeepCopy(vtkMatrix3x3 *source)
    {vtkMatrix3x3::DeepCopy(*this->Element,source); this->Modified(); }
//BTX
  static void DeepCopy(double Elements[9], vtkMatrix3x3 *source)
    {vtkMatrix3x3::DeepCopy(Elements,*source->Element); }
  static void DeepCopy(double Elements[9], const double newElements[9]);
//ETX

  // Description:
  // Non-static member function. Assigns *from* elements array
  void DeepCopy(const double Elements[9])
    { this->DeepCopy(*this->Element,Elements); this->Modified(); }

  // Description:
  // Set all of the elements to zero.
  void Zero()
    { vtkMatrix3x3::Zero(*this->Element); this->Modified(); }
//BTX
  static void Zero(double Elements[9]);
//ETX

  // Description:
  // Set equal to Identity matrix
  void Identity()
    { vtkMatrix3x3::Identity(*this->Element); this->Modified();}
//BTX
  static void Identity(double Elements[9]);
//ETX

  // Description:
  // Matrix Inversion (adapted from Richard Carling in "Graphics Gems,"
  // Academic Press, 1990).
  static void Invert(vtkMatrix3x3 *in, vtkMatrix3x3 *out)
    {vtkMatrix3x3::Invert(*in->Element,*out->Element); out->Modified(); }
  void Invert()
    { vtkMatrix3x3::Invert(this,this); }
//BTX
  static void Invert(const double inElements[9], double outElements[9]);
//ETX


  // Description:
  // Transpose the matrix and put it into out.
  static void Transpose(vtkMatrix3x3 *in, vtkMatrix3x3 *out)
    {vtkMatrix3x3::Transpose(*in->Element,*out->Element); out->Modified(); }
  void Transpose()
    { vtkMatrix3x3::Transpose(this,this); }
//BTX
  static void Transpose(const double inElements[9], double outElements[9]);
//ETX

  // Description:
  // Multiply a homogeneous coordinate by this matrix, i.e. out = A*in.
  // The in[3] and out[3] can be the same array.
  void MultiplyPoint(const float in[3], float out[3])
    {vtkMatrix3x3::MultiplyPoint(*this->Element,in,out); }
  void MultiplyPoint(const double in[3], double out[3])
    {vtkMatrix3x3::MultiplyPoint(*this->Element,in,out); }

//BTX
  static void MultiplyPoint(const double Elements[9],
                            const float in[3], float out[3]                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          