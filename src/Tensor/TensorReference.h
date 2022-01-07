#pragma once

#include "Tensor/TensorBase.h"
#include "Tensor/TensorCommon.h"
#include <array>
#include <vector>


namespace tens {

template <typename Derived, typename Scalar_, int NumIndices_>
class TensorBaseReadOnly;

template <typename Derived, typename Scalar_, int NumIndices_>
class TensorBaseWrite;

template <typename SrcDerived, typename Scalar_, int NumIndices_>
class DLTensorSliced;


template <typename SrcDerived, typename Scalar_, int NumIndices_>
class DLTensorSliced : public TensorBaseWrite<DLTensorSliced<SrcDerived, Scalar_, NumIndices_>, Scalar_, NumIndices_>
{

protected:
	SrcDerived * m_srcTen;
	std::array<IndexType, NumIndices_> m_vecStart;
	std::array<IndexType, NumIndices_> m_vecVolume;

public:
	DLTensorSliced(const SrcDerived * srcTen, const std::array<IndexType, NumIndices_> & vecStart, const std::array<IndexType, NumIndices_> &  vecVolume)
		 :m_srcTen(const_cast<SrcDerived *> (srcTen)), m_vecStart(vecStart), m_vecVolume(vecVolume) {}

	inline auto eval() -> decltype( m_srcTen->eval().slice(m_vecStart, m_vecVolume) )
	{
		return  m_srcTen->eval().slice(m_vecStart, m_vecVolume);
	}

	inline auto eval() const -> decltype(m_srcTen->eval().slice(m_vecStart, m_vecVolume))
	{
		return  m_srcTen->eval().slice(m_vecStart, m_vecVolume);
	}

	template<typename OtherDerived>
	inline void operator=(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs)
	{
		derived().eval() = rhs.derived().eval();
	}

	inline void operator=(Scalar_ rhs)
	{
		derived().eval().setConstant(rhs);
	}

	// The meta four
	inline constexpr int rank() const { return NumIndices_; }
	inline const IndexType dim(int n) const { return  m_vecVolume[n]; }
	inline const IndexType size() const 
	{ 
		IndexType retSize = 1;
		for (auto & dimx : m_vecVolume)
			retSize *= dimx;
		return retSize;
	}
	inline std::vector<IndexType> dimensions() const { return std::vector<IndexType>(m_vecVolume.begin(), m_vecVolume.end()); }


};

template <typename SrcDerived, typename Scalar_, int NumIndices_>
class DLTensorChipped : public TensorBaseWrite< DLTensorChipped<SrcDerived, Scalar_, NumIndices_>, Scalar_, NumIndices_>
{

protected:
	SrcDerived * m_srcTen;
	int m_Rnk;
	IndexType m_Dim;

public:
	DLTensorChipped(const SrcDerived * srcTen, IndexType dimi, int rnk)
		:m_srcTen(const_cast<SrcDerived *> (srcTen)), m_Rnk(rnk), m_Dim(dimi) {}

	inline auto eval() -> decltype(m_srcTen->eval().chip(m_Dim, m_Rnk))
	{
		return  m_srcTen->eval().chip(m_Dim, m_Rnk);
	}

	inline auto eval() const -> decltype(m_srcTen->eval().chip(m_Dim, m_Rnk))
	{
		return  m_srcTen->eval().chip(m_Dim, m_Rnk);
	}

	template<typename OtherDerived>
	inline void operator=(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs)
	{
		derived().eval() = rhs.derived().eval();
	}

	inline void operator=(Scalar_ rhs)
	{
		derived().eval().setConstant( rhs);
	}

	// The meta four
	inline constexpr int rank() const { return NumIndices_; }
	inline const IndexType dim(int n) const { return n < m_Rnk ?  m_srcTen->dim(n) : m_srcTen->dim(n + 1) ; }
	inline const IndexType size() const
	{
		IndexType retVal = 1;
		for (int i = 0; i < m_srcTen->rank(); i++)
			if (i != m_Rnk)
				retVal *= m_srcTen->dim(i);
		return retVal;
	}
	inline std::vector<IndexType> dimensions() const { 
		auto retVec = m_srcTen->dimensions();
		return retVec.erase(retVec.begin() + m_Rnk);
	}
};


}

