                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ic inline void run(Derived1& dst, const CwiseUnaryOp<UnaryOp, Derived2>& src)
  {
    // in case we want to (or have to) skip VML at runtime we can call:
    // assign_impl<Derived1,Eigen::CwiseUnaryOp<UnaryOp, Derived2>,Traversal,Unrolling,BuiltIn>::run(dst,src);
    const Index innerSize = dst.innerSize();
    const Index outerSize = dst.outerSize();
    for(Index outer = 0; outer < outerSize; ++outer) {
      const Scalar *src_ptr = src.IsRowMajor ?  &(src.nestedExpression().coeffRef(outer,0)) :
                                                &(src.nestedExpression().coeffRef(0, outer));
      Scalar *dst_ptr = dst.IsRowMajor ? &(dst.coeffRef(outer,0)) : &(dst.coeffRef(0, outer));
      vml_call<UnaryOp>::run(src.functor(), innerSize, src_ptr, dst_ptr );
    }
  }
};

template<typename Derived1, typename Derived2, typename UnaryOp, int Traversal, int Unrolling>
struct vml_assign_impl<Derived1, Derived2, UnaryOp, Traversal, Unrolling, LinearVectorizedTraversal>
{
  static inline void run(Derived1& dst, const CwiseUnaryOp<UnaryOp, Derived2>& src)
  {
    // in case we want to (or have to) skip VML at runtime we can call:
    // assign_impl<Derived1,Eigen::CwiseUnaryOp<UnaryOp, Derived2>,Traversal,Unrolling,BuiltIn>::run(dst,src);
    vml_call<UnaryOp>::run(src.functor(), dst.size(), src.nestedExpression().data(), dst.data() );
  }
};

// Macroses

#define EIGEN_MKL_VML_SPECIALIZE_ASSIGN(TRAVERSAL,UNROLLING) \
  template<typename Derived1, typename Derived2, typename UnaryOp> \
  struct assign_impl<Derived1, Eigen::CwiseUnaryOp<UnaryOp, Derived2>, TRAVERSAL, UNROLLING, Specialized>  {  \
    static inline void run(Derived1 &dst, const Eigen::CwiseUnaryOp<UnaryOp, Derived2> &src) { \
      vml_assign_impl<Derived1,Derived2,UnaryOp,TRAVERSAL,UNROLLING>::run(dst, src); \
    } \
  };

EIGEN_MKL_VML_SPECIALIZE_ASSIGN(DefaultTraversal,NoUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(DefaultTraversal,CompleteUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(DefaultTraversal,InnerUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(LinearTraversal,NoUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(LinearTraversal,CompleteUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(InnerVectorizedTraversal,NoUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(InnerVectorizedTraversal,CompleteUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(InnerVectorizedTraversal,InnerUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(LinearVectorizedTraversal,CompleteUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(LinearVectorizedTraversal,NoUnrolling)
EIGEN_MKL_VML_SPECIALIZE_ASSIGN(SliceVectorizedTraversal,NoUnrolling)


#if !defined (EIGEN_FAST_MATH) || (EIGEN_FAST_MATH != 1)
#define  EIGEN_MKL_VML_MODE VML_HA
#else
#define  EIGEN_MKL_VML_MODE VML_LA
#endif

#define EIGEN_MKL_VML_DECLARE_UNARY_CALL(EIGENOP, VMLOP, EIGENTYPE, VMLTYPE)     \
  template<> struct vml_call< scalar_##EIGENOP##_op<EIGENTYPE> > {               \
    enum { IsSupported = 1 };                                                    \
    static inline void run( const scalar_##EIGENOP##_op<EIGENTYPE>& /*func*/,        \
                            int size, const EIGENTYPE* src, EIGENTYPE* dst) {    \
      VMLOP(size, (const VMLTYPE*)src, (VMLTYPE*)dst);                           \
    }                                                                            \
  };

#define EIGEN_MKL_VML_DECLARE_UNARY_CALL_LA(EIGENOP, VMLOP, EIGENTYPE, VMLTYPE)  \
  template<> struct vml_call< scalar_##EIGENOP##_op<EIGENTYPE> > {               \
    enum { IsSupported = 1 };                                                    \
    static inline void run( const scalar_##EIGENOP##_op<EIGENTYPE>& /*func*/,        \
                            int size, const EIGENTYPE* src, EIGENTYPE* dst) {    \
      MKL_INT64 vmlMode = EIGEN_MKL_VML_MODE;                                    \
      VMLOP(size, (const VMLTYPE*)src, (VMLTYPE*)dst, vmlMode);                  \
    }                                                                            \
  };

#define EIGEN_MKL_VML_DECLARE_POW_CALL(EIGENOP, VMLOP, EIGENTYPE, VMLTYPE)       \
  template<> struct vml_call< scalar_##EIGENOP##_op<EIGENTYPE> > {               \
    enum { IsSupported = 1 };                                                    \
    static inline void run( const scalar_##EIGENOP##_op<EIGENTYPE>& func,        \
                          int size, const EIGENTYPE* src, EIGENTYPE* dst) {      \
      EIGENTYPE exponent = func.m_exponent;                                      \
      MKL_INT64 vmlMode = EIGEN_MKL_VML_MODE;                                    \
      VMLOP(&size, (const VMLTYPE*)src, (const VMLTYPE*)&exponent,               \
                        (VMLTYPE*)dst, &vmlMode);                                \
    }                                                                            \
  };

#define EIGEN_MKL_VML_DECLARE_UNARY_CALLS_REAL(EIGENOP, VMLOP)                   \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL(EIGENOP, vs##VMLOP, float, float)             \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL(EIGENOP, vd##VMLOP, double, double)

#define EIGEN_MKL_VML_DECLARE_UNARY_CALLS_COMPLEX(EIGENOP, VMLOP)                \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL(EIGENOP, vc##VMLOP, scomplex, MKL_Complex8)   \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL(EIGENOP, vz##VMLOP, dcomplex, MKL_Complex16)

#define EIGEN_MKL_VML_DECLARE_UNARY_CALLS(EIGENOP, VMLOP)                        \
  EIGEN_MKL_VML_DECLARE_UNARY_CALLS_REAL(EIGENOP, VMLOP)                         \
  EIGEN_MKL_VML_DECLARE_UNARY_CALLS_COMPLEX(EIGENOP, VMLOP)


#define EIGEN_MKL_VML_DECLARE_UNARY_CALLS_REAL_LA(EIGENOP, VMLOP)                \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL_LA(EIGENOP, vms##VMLOP, float, float)         \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL_LA(EIGENOP, vmd##VMLOP, double, double)

#define EIGEN_MKL_VML_DECLARE_UNARY_CALLS_COMPLEX_LA(EIGENOP, VMLOP)             \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL_LA(EIGENOP, vmc##VMLOP, scomplex, MKL_Complex8)  \
  EIGEN_MKL_VML_DECLARE_UNARY_CALL_LA(EIGENOP, vmz##VMLOP, dcomplex, MKL_Complex16)

#define EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(EIGENOP, VMLOP)                     \
  EIGEN_MKL_VML_DECLARE_UNARY_CALLS_REAL_LA(EIGENOP, VMLOP)                      \
  EIGEN_MKL_VML_DECLARE_UNARY_CALLS_COMPLEX_LA(EIGENOP, VMLOP)


EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(sin,  Sin)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(asin, Asin)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(cos,  Cos)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(acos, Acos)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(tan,  Tan)
//EIGEN_MKL_VML_DECLARE_UNARY_CALLS(abs,  Abs)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(exp,  Exp)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(log,  Ln)
EIGEN_MKL_VML_DECLARE_UNARY_CALLS_LA(sqrt, Sqrt)

EIGEN_MKL_VML_DECLARE_UNARY_CALLS_REAL(square, Sqr)

// The vm*powx functions are not avaibale in the windows version of MKL.
#ifndef _WIN32
EIGEN_MKL_VML_DECLARE_POW_CALL(pow, vmspowx_, float, float)
EIGEN_MKL_VML_DECLARE_POW_CALL(pow, vmdpowx_, double, double)
EIGEN_MKL_VML_DECLARE_POW_CALL(pow, vmcpowx_, scomplex, MKL_Complex8)
EIGEN_MKL_VML_DECLARE_POW_CALL(pow, vmzpowx_, dcomplex, MKL_Complex16)
#endif

} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_ASSIGN_VML_H
