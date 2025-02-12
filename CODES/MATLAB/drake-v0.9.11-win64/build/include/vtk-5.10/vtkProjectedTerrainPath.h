/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkProjectedTerrainPath.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkProjectedTerrainPath - project a polyline onto a terrain
// .SECTION Description
// vtkProjectedTerrainPath projects an input polyline onto a terrain. (The
// terrain is defined by a 2D height image and is the second input to the
// filter.) The polyline projection is controlled via several modes as
// follows. 1) Simple mode projects the polyline points onto the terrain,
// taking into account the height offset instance variable. 2) Non-occluded
// mode insures that no parts of the polyline are occluded by the terrain
// (e.g. a line passes through a mountain). This may require recursive
// subdivision of the polyline. 3) Hug mode insures that the polyine points
// remain within a constant distance from the surface. This may also require
// recursive subdivision of the polyline. Note that both non-occluded mode
// and hug mode also take into account the height offset, so it is possible 
// to create paths that hug terrain a certain distance above it. To use this
// filter, define two inputs: 1) a polyline, and 2) an image whose scalar
// values represent a height field. Then specify the mode, and the height
// offset to use.
//
// An description of the algorithm is as follows. The filter begins by
// projecting the polyline points to the image (offset by the specified
// height offset).  If the mode is non-occluded or hug, then the maximum
// error along each line segment is computed and placed into a priority
// queue. Each line segment is then split at the point of maximum error, and
// the two new line segments are evaluated for maximum error. This process
// continues until the line is not occluded by the terrain (non-occluded
// mode) or satisfies the error on variation from the surface (hug
// mode). (Note this process is repeated for each polyline in the
// input. Also, the maximum error is computed in two parts: a maximum
// positive error and maximum negative error. If the polyline is above the
// terrain--i.e., the height offset is positive--in non-occluded or hug mode
// all negative errors are eliminated. If the polyline is below the
// terrain--i.e., the height offset is negative--in non-occluded or hug mode
// all positive errors are eliminated.)
// 
// .SECTION Caveats
// This algorithm requires the entire input image to be in memory, hence it 
// may not work for extremely large images. 
//
// The input height image is assumed to be positioned in the x-y plane so the
// scalar value is the z-coordinate, height value.
//
// A priority queue is used so that the 1) the total number of line segments
// can be controlled, and 2) the algorithm can terminate when the errors in
// the queue are less than the specified error tolerance.
//
// .SECTION See Also
// vtkGreedyTerrainDecimation

#ifndef __vtkProjectedTerrainPath_h
#define __vtkProjectedTerrainPath_h

#include "vtkPolyDataAlgorithm.h"

class vtkPriorityQueue;
class vtkImageData;
class vtkEdgeList;
class vtkPoints;

class VTK_HYBRID_EXPORT vtkProjectedTerrainPath : public vtkPolyDataAlgorithm
{
public:
  // Description:
  // Standard methids for printing and determining type information.
  vtkTypeMacro(vtkProjectedTerrainPath,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Instantiate the class.
  static vtkProjectedTerrainPath* New();

  // Description:
  // Specify the second input (the terrain) onto which the polyline(s) shoul                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   