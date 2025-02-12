                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                1 : 0;
              UpLo==Lower ? i1<actualBlockSize : i1<=j1; ++i1)
            r[i1] += buffer(i1,j1);
        }
      }

      if(UpLo==Lower)
      {
        Index i = j+actualBlockSize;
        gebp_kernel(res+j*resStride+i, resStride, blockA+depth*i, actual_b, size-i, depth, actualBlockSize, alpha,
                    -1, -1, 0, 0, workspace);
      }
    }
  }
};

} // end namespace internal

// high level API

template<typename MatrixType, typename ProductType, int UpLo, bool IsOuterProduct>
struct general_product_to_triangular_selector;


template<typename MatrixType, typename ProductType, int UpLo>
struct general_product_to_triangular_selector<MatrixType,ProductType,UpLo,true>
{
  static void run(MatrixType& mat, const ProductType& prod, const typename MatrixType::Scalar& alpha)
  {
    typedef typename MatrixType::Scalar Scalar;
    typedef typename MatrixType::Index Index;
    
    typedef typename internal::remove_all<typename ProductType::LhsNested>::type Lhs;
    typedef internal::blas_traits<Lhs> LhsBlasTraits;
    typedef typename LhsBlasTraits::DirectLinearAccessType ActualLhs;
    typedef typename internal::remove_all<ActualLhs>::type _ActualLhs;
    typename internal::add_const_on_value_type<ActualLhs>::type actualLhs = LhsBlasTraits::extract(prod.lhs());
    
    typedef typename internal::remove_all<typename ProductType::RhsNested>::type Rhs;
    typedef internal::blas_traits<Rhs> RhsBlasTraits;
    typedef typename RhsBlasTraits::DirectLinearAccessType ActualRhs;
    typedef typename internal::remove_all<ActualRhs>::type _ActualRhs;
    typename internal::add_const_on_value_type<ActualRhs>::type actualRhs = RhsBlasTraits::extract(prod.rhs());

    Scalar actualAlpha = alpha * LhsBlasTraits::extractScalarFactor(prod.lhs().derived()) * RhsBlasTraits::extractScalarFactor(prod.rhs().derived());

    enum {
      StorageOrder = (internal::traits<MatrixType>::Flags&RowMajorBit) ? RowMajor : ColMajor,
      UseLhsDirectly = _ActualLhs::InnerStrideAtCompileTime==1,
      UseRhsDirectly = _ActualRhs::InnerStrideAtCompileTime==1
    };
    
    internal::gemv_static_vector_if<Scalar,Lhs::SizeAtCompileTime,Lhs::MaxSizeAtCompileTime,!UseLhsDirectly> static_lhs;
    ei_declare_aligned_stack_constructed_variable(Scalar, actualLhsPtr, actualLhs.size(),
      (UseLhsDirectly ? const_cast<Scalar*>(actualLhs.data()) : static_lhs.data()));
    if(!UseLhsDirectly) Map<typename _ActualLhs::PlainObject>(actualLhsPtr, actualLhs.size()) = actualLhs;
    
    internal::gemv_static_vector_if<Scalar,Rhs::SizeAtCompileTime,Rhs::MaxSizeAtCompileTime,!UseRhsDirectly> static_rhs;
    ei_declare_aligned_stack_constructed_variable(Scalar, actualRhsPtr, actualRhs.size(),
      (UseRhsDirectly ? const_cast<Scalar*>(actualRhs.data()) : static_rhs.data()));
    if(!UseRhsDirectly) Map<typename _ActualRhs::PlainObject>(actualRhsPtr, actualRhs.size()) = actualRhs;
    
    
    selfadjoint_rank1_update<Scalar,Index,StorageOrder,UpLo,
                              LhsBlasTraits::NeedToConjugate && NumTraits<Scalar>::IsComplex,
                              RhsBlasTraits::NeedToConjugate && NumTraits<Scalar>::IsComplex>
          ::run(actualLhs.size(), mat.data(), mat.outerStride(), actualLhsPtr, actualRhsPtr, actualAlpha);
  }
};

template<typename MatrixType, typename ProductType, int UpLo>
struct general_product_to_triangular_selector<MatrixType,ProductType,UpLo,false>
{
  static void run(MatrixType& mat, const ProductType& prod, const typename MatrixType::Scalar& alpha)
  {
    typedef typename MatrixType::Index Index;
    
    typedef typename internal::remove_all<typename ProductType::LhsNested>::type Lhs;
    typedef internal::blas_traits<Lhs> LhsBlasTraits;
    typedef typename LhsBlasTraits::DirectLinearAccessType ActualLhs;
    typedef typename internal::remove_all<ActualLhs>::type _ActualLhs;
    typename internal::add_const_on_value_type<ActualLhs>::type actualLhs = LhsBlasTraits::extract(prod.lhs());
    
    typedef typename internal::remove_all<typename ProductType::RhsNested>::type Rhs;
    typedef internal::blas_traits<Rhs> RhsBlasTraits;
    typedef typename RhsBlasTraits::DirectLinearAccessType ActualRhs;
    typedef typename internal::remove_all<ActualRhs>::type _ActualRhs;
    typename internal::add_const_on_value_type<ActualRhs>::type actualRhs = RhsBlasTraits::extract(prod.rhs());

    typename ProductType::Scalar actualAlpha = alpha * LhsBlasTraits::extractScalarFactor(prod.lhs().derived()) * RhsBlasTraits::extractScalarFactor(prod.rhs().derived());

    internal::general_matrix_matrix_triangular_product<Index,
      typename Lhs::Scalar, _ActualLhs::Flags&RowMajorBit ? RowMajor : ColMajor, LhsBlasTraits::NeedToConjugate,
      typename Rhs::Scalar, _ActualRhs::Flags&RowMajorBit ? RowMajor : ColMajor, RhsBlasTraits::NeedToConjugate,
      MatrixType::Flags&RowMajorBit ? RowMajor : ColMajor, UpLo>
      ::run(mat.cols(), actualLhs.cols(),
            &actualLhs.coeffRef(0,0), actualLhs.outerStride(), &actualRhs.coeffRef(0,0), actualRhs.outerStride(),
            mat.data(), mat.outerStride(), actualAlpha);
  }
};

template<typename MatrixType, unsigned int UpLo>
template<typename ProductDerived, typename _Lhs, typename _Rhs>
TriangularView<MatrixType,UpLo>& TriangularView<MatrixType,UpLo>::assignProduct(const ProductBase<ProductDerived, _Lhs,_Rhs>& prod, const Scalar& alpha)
{
  general_product_to_triangular_selector<MatrixType, ProductDerived, UpLo, (_Lhs::ColsAtCompileTime==1) || (_Rhs::RowsAtCompileTime==1)>::run(m_matrix.const_cast_derived(), prod.derived(), alpha);
  
  return *this;
}

} // end namespace Eigen

#endif // EIGEN_GENERAL_MATRIX_MATRIX_TRIANGULAR_H
