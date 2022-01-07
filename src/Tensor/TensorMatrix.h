#pragma once

#include "TensorBase.h"
#include "TensorCommon.h"

#include <vector>
#include <memory>

#ifndef NumMatIndices_
#define NumMatIndices_ 2
#endif

namespace tens
{

enum DL_MATRIX_BINARY_CALC {
	MATRIX_BINARY_BASE = 0,
	MATRIX_BINARY_MULTIPLE = 1
};

template <typename Derived, typename Scalar_, int NumIndices_>
class TensorBaseReadOnly;

template <typename Derived, typename Scalar_, int NumIndices_>
class TensorBaseWrite;

template <typename Derived, typename Scalar_>
class TensorMatrixBase;

template < typename OtherDerived , typename Scalar_>
class TensorMatrix;

template<typename LhsMatDerived, typename RhsMatDerived, typename Scalar_, int CalcType>
class TensorMatrixBinaryCalc;


// DLTensorMatrix는 Data Tensor에 의해서만 생성될 수 있다. 
// Data Tensor는 member function으로 .data()함수를 가지고 있어야 한다. 
template <typename Derived , typename Scalar_> 
class TensorMatrixBase : public TensorBaseWrite<Derived, Scalar_, NumMatIndices_>
{
public:	
	template <typename OtherMtxDerived>
	TensorMatrixBinaryCalc<Derived, OtherMtxDerived, Scalar_, MATRIX_BINARY_MULTIPLE> operator*(const TensorMatrixBase<OtherMtxDerived, Scalar_> & rhs)
	{
		return TensorMatrixBinaryCalc<Derived, OtherMtxDerived, Scalar_, MATRIX_BINARY_MULTIPLE>(derived(), rhs.derived());
	}
};

template <typename OtherDerived, typename Scalar_>
class TensorMatrix : public TensorMatrixBase<TensorMatrix<OtherDerived, Scalar_>, Scalar_>
{
public:
	TensorMatrix(const OtherDerived& src, const std::vector<IndexType> & srcDims, MATRIX_TYPE mattype)
		:m_srcTen(src), m_srcDims(srcDims), m_matType(mattype) 
	{
		m_matDims = getMatrixRowCol(m_srcDims, mattype);
	}


	inline const IndexType dim(int n) const { return m_matDims[n]; }
	inline const IndexType size() const {return m_matDims[0] * m_matDims[1]; }
	inline std::vector<IndexType> dimensions() const { return  m_matDims; }

protected:
	
	std::vector<IndexType> getMatrixRowCol(const std::vector<IndexType> & vecDims, MATRIX_TYPE mattype) const;
	
	std::shared_ptr<OtherDerived> m_psrcTen;
	std::vector<IndexType> m_srcDims;
	std::vector<IndexType> m_matDims;
	MATRIX_TYPE m_matType;

};

// dummy non sepcified mat
template<typename LhsMatDerived, typename RhsMatDerived, typename Scalar_, int CalcType>
class TensorMatrixBinaryCalc
{
};


template<typename LhsMatDerived, typename RhsMatDerived, typename Scalar_>
class TensorMatrixBinaryCalc<LhsMatDerived, RhsMatDerived, Scalar_, MATRIX_BINARY_BASE>
{

public:
	TensorMatrixBinaryCalc(const LhsMatDerived& lhs, const RhsMatDerived& rhs, int paramType)
		: m_lhs(lhs), m_rhs(rhs), m_nCalcType(paramType) {}

	// The meta four
// 	inline const IndexType dim(int n) const { return  m_lhs.rank() != 0 ? m_lhs.dim(n) : m_rhs.dim(n) }
// 	inline const IndexType size() const { return  m_lhs.rank() != 0 ? m_lhs.size() : m_rhs.size() }
// 	inline std::vector<IndexType> dimensions() const { return  m_lhs.rank() != 0 ? m_lhs.dimensions() : m_rhs.dimensions(); }

protected:
	int m_nCalcType;
	const LhsMatDerived m_lhs;
	const RhsMatDerived m_rhs;

};


template<typename LhsMatDerived, typename RhsMatDerived, typename Scalar_>
class TensorMatrixBinaryCalc<LhsMatDerived, RhsMatDerived, Scalar_, MATRIX_BINARY_MULTIPLE>
	: public TensorMatrixBinaryCalc<LhsMatDerived, RhsMatDerived, Scalar_, MATRIX_BINARY_BASE>
	, public TensorMatrixBase< TensorMatrixBinaryCalc<LhsMatDerived, RhsMatDerived, Scalar_, MATRIX_BINARY_MULTIPLE>, Scalar_>
{
public:
	TensorMatrixBinaryCalc (const LhsMatDerived & lhs, const RhsMatDerived & rhs)
		: TensorMatrixBinaryCalc<LhsMatDerived, RhsMatDerived, Scalar_, MATRIX_BINARY_BASE>(lhs, rhs, MATRIX_BINARY_MULTIPLE) 
	{
		if (m_lhs.dim(1) != m_rhs.dim(0))
			throw size_nomatch_error("Matrix multiplicaion error : the column size of lhs should be the same with the row size of rhs.");
	}

	inline const IndexType dim(int n) const { return n == 0 ? m_lhs.dim(0) : (n == 1 ? m_rhs.dim(1) : 0); }
	inline const IndexType size() const { return  m_lhs.rank() != 0 ? NumMatIndices_; }
	inline std::vector<IndexType> dimensions() const { return{ m_lhs.dim(0), m_rhs.dim(1) } }
};

template<typename OtherDerived, typename Scalar_>
std::vector<IndexType> TensorMatrix<OtherDerived, Scalar_>::getMatrixRowCol(const std::vector<IndexType> & vecDims, MATRIX_TYPE mattype) const
{
	IndexType rowSize = 1;
	IndexType colSize = 1;

	bool gotRow = false;
	if (mattype == MATRIX_TYPE::ROWVECTOR)
		gotRow = true;

	for (int i = 0; i < vecDims.size(); i++)
	{
		if (vecDims[i] > 1)
		{
			if (!gotRow)
			{
				rowSize *= vecDims[i];
				if (mattype != MATRIX_TYPE::COLUMNVECTOR)
					gotRow = true;
			}
			else
				colSize *= vecDims[i];
		}
	}
	return{ rowSize, colSize };
}


}
