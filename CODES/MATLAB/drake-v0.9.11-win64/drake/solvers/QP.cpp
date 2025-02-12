                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                0))
      *Q = .5* (*Q);
    
  	if (Q->rows() == 1 || Q->cols() == 1) {  // it's a vector
  		d = Q->rows()*Q->cols();
  	  for (i=0; i<d; i++) {
  	  	Qi=i+startrow;
  	  	CGE (GRBaddqpterms(model,1,&Qi,&Qi,&(Q->operator()(i))), env);
  	  }
  	  startrow=startrow+d;
  	} else { // potentially dense matrix
  		d = Q->rows();
  		if (d!=Q->cols()) {
  			cerr << "Q is not square! " << Q->rows() << "x" << Q->cols() << "\n";
  			return NULL;
  		}

  	  for (i=0; i<d; i++)
    	  for (j=0; j<d; j++) {
    	  	Qi=i+startrow; Qj = j+startrow;
    	  	CGE (GRBaddqpterms(model,1,&Qi,&Qj,&(Q->operator()(i,j))), env);
    	  }
  	  startrow=startrow+d;
  	}
  	if (startrow>nparams) {
  		cerr << "Q is too big!" << endl;
  		return NULL;
  	}
  }

  CGE (GRBsetdblattrarray(model,"Obj",0,nparams,f.data()), env);

  if (Aeq.rows()>0) CGE (myGRBaddconstrs(model,Aeq,beq,GRB_EQUAL, 1e-18), env);
  if (Ain.rows()>0) CGE (myGRBaddconstrs(model,Ain,bin,GRB_LESS_EQUAL, 1e-18), env);

  CGE (GRBupdatemodel(model), env);
  CGE (GRBoptimize(model), env);

  CGE (GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, nparams, x.data()), env);

  VectorXd slack(Ain.rows());
  CGE (GRBgetdblattrarray(model, "Slack", Aeq.rows(), Ain.rows(), slack.data()), env);

  int offset=0;
  active.clear();
  for (int i=0; i<Ain.rows(); i++) {
  	if (slack(i)<active_set_slack_tolerance)
  		active.insert(i);
  }
  offset = Ain.rows();
  if (lb.rows()==nparams)
  	for (int i=0; i<nparams; i++)
  		if (x(i)-lb(i) < active_set_slack_tolerance)
  			active.insert(offset+i);
  if (ub.rows()==nparams)
  	for (int i=0; i<nparams; i++)
  		if (ub(i)-x(i) < active_set_slack_tolerance)
  			active.insert(offset+i+nparams);

  return model;
}


GRBmodel* gurobiActiveSetQP(GRBenv *env, vector< MatrixXd* > QblkDiag, VectorXd& f, const MatrixXd& Aeq, const VectorXd& beq, 
  const MatrixXd& Ain, const VectorXd& bin, VectorXd& lb, VectorXd& ub, int* &vbasis, int vbasis_len, int* &cbasis, int cbasis_len, VectorXd& x)
{
  // NOTE:  this allocates memory for a new GRBmodel and returns it. (you should delete this object when you're done with it)
  // NOTE:  by convention here, the active set indices correspond to Ain,bin first, then lb, then ub.
  GRBmodel *model = NULL;

  int method;  GRBgetintparam(env,"method",&method);
  if (!(method==0 || method==1)) {
    cerr<< "gurobiActiveSetQP: method should be 0 or 1" << endl;
    return NULL;
  }

  int i,j,nparams = f.rows(),Qi,Qj;
  double *lbdata = NULL, *ubdata=NULL;
  if (lb.rows()==nparams) lbdata = lb.data();
  if (ub.rows()==nparams) ubdata = ub.data();
  CGE (GRBnewmodel(env,&model,"QP",nparams,NULL,lbdata,ubdata,NULL,NULL), env);

  int startrow=0,d;
  for (vector< MatrixXd* >::iterator iterQ=QblkDiag.begin(); iterQ!=QblkDiag.end(); iterQ++) {
    MatrixXd* Q=*iterQ;
    
	*Q = .5* (*Q);
    
    if (Q->rows() == 1 || Q->cols() == 1) {  // it's a vector
      d = Q->rows()*Q->cols();
      for (i=0; i<d; i++) {
        Qi=i+startrow;
        CGE (GRBaddqpterms(model,1,&Qi,&Qi,&(Q->operator()(i))), env);
      }
      startrow=startrow+d;
    } else { // potentially dense matrix
      d = Q->rows();
      if (d!=Q->cols()) {
        cerr << "Q is not square! " << Q->rows() << "x" << Q->cols() << "\n";
        return NULL;
      }

      for (i=0; i<d; i++)
        for (j=0; j<d; j++) {
          Qi=i+startrow; Qj = j+startrow;
          CGE (GRBaddqpterms(model,1,&Qi,&Qj,&(Q->operator()(i,j))), env);
        }
      startrow=startrow+d;
    }
    if (startrow>nparams) {
      cerr << "Q is too big!" << endl;
      return NULL;
    }
  }

  CGE (GRBsetdblattrarray(model,"Obj",0,nparams,f.data()), env);

  if (Aeq.rows()>0) CGE (myGRBaddconstrs(model,Aeq,beq,GRB_EQUAL, 1e-18), env);
  if (Ain.rows()>0) CGE (myGRBaddconstrs(model,Ain,bin,GRB_LESS_EQUAL, 1e-18), env);

  CGE (GRBupdatemodel(model), env);

  int numvars; CGE(GRBgetintattr(model,"NumVars",&numvars), env);
  if (numvars == vbasis_len) {
    CGE (GRBsetintattrarray(model, "VBasis", 0, numvars, vbasis), env);
  }
  else {
    delete[] vbasis;
    vbasis = new int[numvars];
  }

  int numconstr; CGE(GRBgetintattr(model,"NumConstrs",&numconstr),env);
  if (numconstr == cbasis_len) {
    CGE (GRBsetintattrarray(model, "CBasis", 0, numconstr, cbasis), env);
  }
  else {
    delete[] cbasis;
    cbasis = new int[numconstr];
  }
  CGE (GRBoptimize(model), env);

  CGE (GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, nparams, x.data()), env);

  CGE (GRBgetintattrarray(model, "VBasis", 0, numvars, vbasis), env);
  CGE (GRBgetintattrarray(model, "CBasis", 0, numconstr, cbasis), env);

  return model;
}



/*
template int fastQP(vector< MatrixBase<MatrixXd>* > QblkDiag, const MatrixBase< Map<VectorXd> >&, const MatrixBase< Map<MatrixXd> >&, const MatrixBase< Map<VectorXd> >&, const MatrixBase< Map<MatrixXd> >&, const MatrixBase< Map<VectorXd> >&, set<int>&, MatrixBase< Map<VectorXd> >&);
template GRBmodel* gurobiQP(GRBenv *env, vector< MatrixBase<MatrixXd>* > QblkDiag, VectorXd& f, const MatrixBase< Map<MatrixXd> >& Aeq, const MatrixBase< Map<VectorXd> >& beq, const MatrixBase< Map<MatrixXd> >& Ain, const MatrixBase< Map<VectorXd> >&bin, VectorXd& lb, VectorXd& ub, set<int>&, VectorXd&);
template GRBmodel* gurobiQP(GRBenv *env, vector< MatrixBase<MatrixXd>* > QblkDiag, VectorXd& f, const MatrixBase< MatrixXd >& Aeq, const MatrixBase< VectorXd >& beq, const MatrixBase< MatrixXd >& Ain, const MatrixBase< VectorXd >&bin, VectorXd&lb, VectorXd&ub, set<int>&, VectorXd&);
*/

/*
template int fastQP(vector< MatrixBase< VectorXd > >, const MatrixBase< VectorXd >&, const MatrixBase< Matrix<double,-1,-1,RowMajor,1000,-1> >&, const MatrixBase< Matrix<double,-1,1,0,1000,1> >&, const MatrixBase< Matrix<double,-1,-1,RowMajor,1000,-1> >&, const MatrixBase< Matrix<double,-1,1,0,1000,1> >&, set<int>&, MatrixBase< VectorXd >&);
*/



