                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                , 0, 1);
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    circle(0,0,0,1);
    line(-1, 0, 1, 0);
    line(0, -1, 0, 1);
    glPopMatrix();
  }

  public synchronized void line3(double x_start, double y_start, double z_start, double x_end, double y_end, double z_end) {
    glBegin(LCMGL_LINES);
    glVertex3d(x_start, y_start, z_start);
    glVertex3d(x_end, y_end, z_end);
    glEnd();
  }

  public synchronized void points(double[] x, double[] y, double[] z) {
    glBegin(LCMGL_POINTS);
    for (int i=0; i<x.length; i++) { 
      glVertex3d(x[i], y[i], z[i]);
    }
    glEnd();
  }
  
  public synchronized void plot3(double[] x, double[] y, double[] z) {
    glBegin(LCMGL_LINES);
    for (int i=0; i<x.length-1; i++) { 
      glVertex3d(x[i], y[i], z[i]);
      glVertex3d(x[i+1], y[i+1], z[i+1]);
    }
    glEnd();    
  }

  public synchronized void rect(double[] xyz, double[] size, int filled) {
     try {
      _outs.writeByte(LCMGL_RECT); 
      _outs.writeDouble(xyz[0]);
      _outs.writeDouble(xyz[1]);
      _outs.writeDouble(xyz[2]);
      _outs.writeDouble(size[0]);
      _outs.writeDouble(size[1]);
      _outs.writeInt(filled);
    } catch(IOException xcp) {}
  }    

  public synchronized void drawArrow3d(double length, double head_width, double head_length, double body_width) {
    int slices = 20;
    int stacks = 20;

    double[] xyz = {0,0,0};

    //apply translations so the drawing is centered at origin along the x axis per bot_gl_draw_arrow_2d
    glPushMatrix();
    glTranslated(-length / 2, 0, 0);
    glRotated(90, 0, 1, 0);

    //draw body
    cylinder(xyz, body_width, body_width, length - head_length, slices, stacks);

    //draw head
    glTranslated(0, 0, length - head_length);
    cylinder(xyz, head_width, 0, head_length, slices, stacks);

    glPopMatrix();
  }

  public synchronized void drawVector3d(double[] origin, double[] vector) {
    double body_width = 0.0025;
    double head_width = 0.01;
    double head_length = 0.01;
    drawVector(origin,vector,body_width,head_width,head_length); 
  }

  public synchronized void scaleToViewerAr() { add0(LCMGL_SCALE_TO_VIEWER_AR); }

  public synchronized void drawVector(double[] origin, double[] vector,double body_width,double head_width,double head_length) {
    int slices = 20;
    int stacks = 20;

    double vector_norm = Math.sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);

    if (vector_norm>0) {
      glPushMatrix();
      
      glTranslated(origin[0],origin[1],origin[2]);

      // cross product with z axis to get rotation axis
      double[] rot_axis = {vector[1],-vector[0],0};
      if (rot_axis[0]==0&&rot_axis[1]==0) {
        // the vector is along the z axis, rot_angle will be 0 or 180 so use either x or y
        rot_axis[0] = 1;
      }
      double rot_angle = -Math.toDegrees(Math.acos(vector[2]/vector_norm));
      glRotated(rot_angle,rot_axis[0],rot_axis[1],rot_axis[2]);

      // make cylinder for body of vector
      double[] xyz = {0,0,0};
      cylinder(xyz,body_width,body_width,vector_norm-head_length,slices,stacks);
      
      // make cylinder for head of vector
      glTranslated(0,0,vector_norm-head_length);
      cylinder(xyz,head_width,0,head_length,slices,stacks);

      glPopMatrix();
    }

  }

  public synchronized void polygon(double[] x, double[] y, double[] z){
    glBegin(LCMGL_POLYGON);
    for(int i = 0;i<x.length;i++){
      glVertex3d(x[i],y[i],z[i]);
    }
    glEnd();
  }

  public synchronized void polyhedron(double[] x, double[] y, double[] z){
    for(int i =0;i<x.length;i++){
      for(int j=i;j<y.length;j++){
        for(int k = j;k<z.length;k++){
          glBegin(LCMGL_POLYGON);
          glVertex3d(x[i],y[i],z[i]);
          glVertex3d(x[j],y[j],z[j]);
          glVertex3d(x[k],y[k],z[k]);
          glEnd();
        }
      }
    }

  }
}
