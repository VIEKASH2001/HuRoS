/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPlotParallelCoordinates.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkPlotParallelCoordinates - Class for drawing a parallel coordinate
// plot given columns from a vtkTable.
//
// .SECTION Description
//

#ifndef __vtkPlotParallelCoordinates_h
#define __vtkPlotParallelCoordinates_h

#include "vtkPlot.h"
#include "vtkScalarsToColors.h" // For VTK_COLOR_MODE_DEFAULT and _MAP_SCALARS
#include "vtkStdString.h"       // For vtkStdString ivars

class vtkChartParallelCoordinates;
class vtkTable;
class vtkStdString;
class vtkScalarsToColors;
class vtkUnsignedCharArray;

class VTK_CHARTS_EXPORT vtkPlotParallelCoordinates : public vtkPlot
{
public:
  vtkTypeMacro(vtkPlotParallelCoordinates, vtkPlot);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  // Description:
  // Creates a parallel coordinates chart
  static vtkPlotParallelCoordinates* New();

  // Description:
  // Perform any updates to the item that may be necessary before rendering.
  // The scene should take care of calling this on all items before their
  // Paint function is invoked.
  virtual void Update();

  // Description:
  // Paint event for the XY plot, called whenever the chart needs to be drawn
  virtual bool Paint(vtkContext2D *painter);

  // Description:
  // Paint legend event for the XY plot, called whenever the legend needs the
  // plot items symbol/mark/line drawn. A rect is supplied with the lower left
  // corner of the rect (elements 0 and 1) and with width x height (elements 2
  // and 3). The plot can choose how to fill the space supplied.
  virtual bool PaintLegend(vtkContext2D *painter, const vtkRectf& rect,
                           int legendIndex);

  // Description:
  // Get the bounds for this mapper as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
  virtual void GetBounds(double bounds[4]);

  // Description:
  // Set the selection criteria on the given axis in normalized space (0.0 - 1.0).
  bool SetSelectionRange(int Axis, float low, float high);

  // Description:
  // Reset the selection criteria for the chart.
  bool ResetSelectionRange();

  // Description:
  // This is a convenience function to set the input table.
  virtual void SetInput(vtkTable *table);
  virtual void SetInput(vtkTable *table, const vtkStdString&,
                        const vtkStdString&)
  {
    this->SetInput(table);
  }

  // Description:
  // Specify a lookup table for the mapper to use.
  void SetLookupTable(vtkScalarsToColors *lut);
  vtkScalarsToColors *GetLookupTable();

  // Description:
  // Create default lookup table. Generally used to create one when none
  // is available with the scalar data.
  virtual void CreateDefaultLookupTable();

  // Description:
  // Turn on/off flag to control whether scalar data is used to color objects.
  vtkSetMacro(ScalarVisibility,int);
  vtkGetMacro(ScalarVisibility,int);
  vtkBooleanMacro(ScalarVisibility,int);

  // Description:
  // When ScalarMode is set to UsePointFieldData or UseCellFieldData,
  // you can specify which array to use for coloring using these methods.
  // The lookup table will decide how to convert vectors to colors.
  void SelectColorArray(vtkIdType arrayNum);
  void SelectColorArray(const vtkStdString &arrayName);

  // Description:
  // Get the array name to color by.
  vtkStdString GetColorArrayName();

//BTX
protected:
  vtkPlotParallelCoordinates();
  ~vtkPlotParallelCoordinates();

  // Description:
  // Update the table cache.
  bool Updatk�8v�HN��nl�R               ���           \                                                                               E}���I�@�|}�+rXY2���F�^˵[(=Qp�ggYB��h�.l�       B      P S V S S K  P S V S S K                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           