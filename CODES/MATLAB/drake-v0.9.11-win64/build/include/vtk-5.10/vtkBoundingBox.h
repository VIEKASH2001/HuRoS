                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ouble &yMin, double &yMax,
                 double &zMin, double &zMax) const;
    
  // Description:
  // Return the ith bounds of the box (defined by vtk style)
  double GetBound(int i) const;
    
  // Description:
  // Get the minimum point of the bounding box
  const double *GetMinPoint() const;
  void GetMinPoint(double &x, double &y, double &z) const;

  // Description:
  // Get the maximum point of the bounding box
  const double *GetMaxPoint() const;
  void GetMaxPoint(double &x, double &y, double &z) const;

  // Description:
  // Returns 1 if the point is contained in the box else 0;
  int ContainsPoint(double p[3]) const;
  int ContainsPoint(double px, double py, double pz) const;

  // Description:
  // Get the center of the bounding box
  void GetCenter(double center[3]) const;

  // Description:
  // Get the lengths of the box
  void GetLengths(double lengths[3]) const;

  // Description:
  // Return the length in the ith direction
  double GetLength(int i) const;

  // Description:
  // Return the Max Length of the box
  double GetMaxLength() const;

  // Description:
  // Return the length of the diagonal.
  // \pre not_empty: this->IsValid()
  double GetDiagonalLength() const;

  // Description:
  // Expand the Box by delta on each side, the box will grow by
  // 2*delta in x,y and z
  void Inflate(double delta);

  // Description:
  // Returns 1 if the bounds have been set and 0 if the box is in its
  // initialized state which is an inverted state
  int IsValid() const;
  static int IsValid(double bounds[6]);
  
  // Description:
  // Returns the box to its initialized state
  void Reset();

  // Description:
  // Scale each dimension of the box by some given factor.
  // If the box is not valid, it stays unchanged.
  // If the scalar factor is negative, bounds are flipped: for example,
  // if (xMin,xMax)=(-2,4) and sx=-3, (xMin,xMax) becomes (-12,6).
  void Scale(double s[3]);
  void Scale(double sx,
             double sy,
             double sz);

protected:
  double MinPnt[3], MaxPnt[3];
};

inline void vtkBoundingBox::Reset()
{
  this->MinPnt[0] = this->MinPnt[1] = this->MinPnt[2] = VTK_DOUBLE_MAX;    
  this->MaxPnt[0] = this->MaxPnt[1] = this->MaxPnt[2] = VTK_DOUBLE_MIN;
}

inline void vtkBoundingBox::GetBounds(double &xMin, double &xMax,
                                      double &yMin, double &yMax,
                                      double &zMin, double &zMax) const
{
  xMin = this->MinPnt[0];
  xMax = this->MaxPnt[0];
  yMin = this->MinPnt[1];
  yMax = this->MaxPnt[1];
  zMin = this->MinPnt[2];
  zMax = this->MaxPnt[2];
}

inline double vtkBoundingBox::GetBound(int i) const
{
  // If i is odd then when are returning a part of the max bounds
  // else part of the min bounds is requested.  The exact component
  // needed is i /2 (or i right shifted by 1
  return ((i & 0x1) ? this->MaxPnt[i>>1] : this->MinPnt[i>>1]);
}

inline const double *vtkBoundingBox::GetMinPoint() const
{
  return this->MinPnt;
}

inline const double *vtkBoundingBox::GetMaxPoint() const
{
  return this->MaxPnt;
}

inline int vtkBoundingBox::IsValid() const
{
  return ((this->MinPnt[0] <= this->MaxPnt[0]) && 
          (this->MinPnt[1] <= this->MaxPnt[1]) && 
          (this->MinPnt[2] <= this->MaxPnt[2]));
} 

inline int vtkBoundingBox::IsValid(double bounds[6])
{
  return (bounds[0] <= bounds[1] &&
    bounds[2] <= bounds[3] &&
    bounds[4] <= bounds[5]);
}

inline double vtkBoundingBox::GetLength(int i) const
{
  return this->MaxPnt[i] - this->MinPnt[i];
}

inline void vtkBoundingBox::GetLengths(double lengths[3]) const
{
  lengths[0] = this->GetLength(0);
  lengths[1] = this->GetLength(1);
  lengths[2] = this->GetLength(2);
}

inline void vtkBoundingBox::GetCenter(double center[3]) const
{
  center[0] = 0.5 * (this->MaxPnt[0] + this->MinPnt[0]);
  center[1] = 0.5 * (this->MaxPnt[1] + this->MinPnt[1]);
  center[2] = 0.5 * (this->MaxPnt[2] + this->MinPnt[2]);
}

inline void vtkBoundingBox::SetBounds(double bounds[6])
{
  this->SetBounds(bounds[0], bounds[1], bounds[2],
                  bounds[3], bounds[4], bounds[5]);
}

inline void vtkBoundingBox::GetBounds(double bounds[6]) const
{
  this->GetBounds(bounds[0], bounds[1], bounds[2],
                  bounds[3], bounds[4], bounds[5]);
}

inline vtkBoundingBox::vtkBoundingBox()
{
  this->Reset();
}

inline vtkBoundingBox::vtkBoundingBox(double bounds[6])
{
  this->Reset();
  this->SetBounds(bounds);
}

inline vtkBoundingBox::vtkBoundingBox(double xMin, double xMax,
                                      double yMin, double yMax,
                                      double zMin, double zMax)
{
  this->Reset();
  this->SetBounds(xMin, xMax, yMin, yMax, zMin, zMax);
}

inline vtkBoundingBox::vtkBoundingBox(const vtkBoundingBox &bbox)
{
  this->MinPnt[0] = bbox.MinPnt[0];
  this->MinPnt[1] = bbox.MinPnt[1];
  this->MinPnt[2] = bbox.MinPnt[2];

  this->MaxPnt[0] = bbox.MaxPnt[0];
  this->MaxPnt[1] = bbox.MaxPnt[1];
  this->MaxPnt[2] = bbox.MaxPnt[2];
}

inline vtkBoundingBox &vtkBoundingBox::operator=(const vtkBoundingBox &bbox)
{
  this->MinPnt[0] = bbox.MinPnt[0];
  this->MinPnt[1] = bbox.MinPnt[1];
  this->MinPnt[2] = bbox.MinPnt[2];

  this->MaxPnt[0] = bbox.MaxPnt[0];
  this->MaxPnt[1] = bbox.MaxPnt[1];
  this->MaxPnt[2] = bbox.MaxPnt[2];
  return *this;
}

inline int vtkBoundingBox::operator==(const vtkBoundingBox &bbox)const
{
  return ((this->MinPnt[0] == bbox.MinPnt[0]) &&
          (this->MinPnt[1] == bbox.MinPnt[1]) &&
          (this->MinPnt[2] == bbox.MinPnt[2]) &&
          (this->MaxPnt[0] == bbox.MaxPnt[0]) &&
          (this->MaxPnt[1] == bbox.MaxPnt[1]) &&
          (this->MaxPnt[2] == bbox.MaxPnt[2]));
}

inline int vtkBoundingBox::operator!=(const vtkBoundingBox &bbox)const
{
  return !((*this) == bbox);
}

inline void vtkBoundingBox::SetMinPoint(double p[3])
{
  this->SetMinPoint(p[0], p[1], p[2]);
}

inline void vtkBoundingBox::SetMaxPoint(double p[3])
{
  this->SetMaxPoint(p[0], p[1], p[2]);
}

inline void vtkBoundingBox::GetMinPoint(double &x, double &y, double &z) const
{
  x = this->MinPnt[0];
  y = this->MinPnt[1];
  z = this->MinPnt[2];
}

inline void vtkBoundingBox::GetMaxPoint(double &x, double &y, double &z) const
{
  x = this->MaxPnt[0];
  y = this->MaxPnt[1];
  z = this->MaxPnt[2];
}

inline int vtkBoundingBox::ContainsPoint(double px, double py, 
                                         double pz) const
{
  if ((px < this->MinPnt[0]) || (px > this->MaxPnt[0]))
    {
    return 0;
    }
  if ((py < this->MinPnt[1]) || (py > this->MaxPnt[1]))
    {
    return 0;
    }
  if ((pz < this->MinPnt[2]) || (pz > this->MaxPnt[2]))
    {
    return 0;
    }
  return 1;
}

inline int vtkBoundingBox::ContainsPoint(double p[3]) const
{
  return this->ContainsPoint(p[0], p[1], p[2]);
}

#endif
