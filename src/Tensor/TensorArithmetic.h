#pragma once

#include "Tensor/TensorCommon.h"
#include "Tensor/TensorBase.h"
#include <utility>


// Generating Operator Proxy Class
#define _GENERATE_BINARY_OPERATOR_(TENum, Otor)													\
template < typename LhsDerived, typename RhsDerived, typename Scalar_ , int NumIndices_>		\
class TensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, TENum >					\
	: public TensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_,  BINARY_BASE>		\
	, public TensorBaseReadOnly< TensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, TENum>, Scalar_, NumIndices_> \
{																								\
public:																							\
	TensorBinaryCalc(const LhsDerived & lhs, const RhsDerived& rhs)							\
	: TensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, BINARY_BASE>(lhs, rhs, TENum) {}	\
	auto eval() const  -> decltype(m_lhs.eval() Otor m_rhs.eval())								\
	{																							\
		return m_lhs.eval() Otor m_rhs.eval();													\
	}																							\
};																							

#define _GENERATE_UNARY_OPERATOR_(TENum, CALC)															\
template <typename Derived, typename Scalar_, int NumIndices_>											\
class TensorUnaryCalc<Derived, Scalar_, NumIndices_, TENum>											\
	: public TensorUnaryCalc<Derived, Scalar_, NumIndices_, UNARY_BASE>										 \
	, public TensorBaseReadOnly<TensorUnaryCalc<Derived, Scalar_, NumIndices_, TENum>, Scalar_, NumIndices_> \
{																						    \
public:																					    \
	TensorUnaryCalc(const Derived& src)												    \
		: TensorUnaryCalc<Derived, Scalar_, NumIndices_, UNARY_BASE>(src, TENum) {}		\
	auto eval() const  -> decltype(CALC)													\
	{																					    \
		return CALC;																		\
	}																					    \
};


namespace tens {

template <typename Derived, typename Scalar_, int NumIndices_>
class TensorBaseReadOnly;

template <typename LhsDerived, typename RhsDerived, typename Scalar_, int NumIndices_, int CalcType>
class TensorBinaryCalc;

template <typename Derived, typename Scalar_, int NumIndices_, int CalcType>
class TensorUnaryCalc;



template <typename Scalar_>
class ScalarType : public TensorBaseWrite< ScalarType<Scalar_> , Scalar_ , 0 >
{
public:
	ScalarType(const Scalar_& sclval) : m_val(sclval) {}
	inline const Scalar_ & eval() const { return m_val; }

	ScalarType(const ScalarType & rhs)
		: m_val(rhs.m_val) {}

	inline constexpr int rank() const { return 0; }
	inline const IndexType dim(int n) const { 
		throw tensor_rank_error("Access to range out of rank");
		return -1;
	}
	inline const IndexType size() const { return 1; }
	inline std::vector<IndexType> dimensions() const { return std::vector<IndexType>(); }
	
	void operator=(const Scalar_& rhs) { m_val = rhs; }
	void operator=(const ScalarType & rhs){m_val = rhs.m_val;}

protected:
	Scalar_ m_val;

	template <typename OtherDerived, typename Scal_, int NumIndices_> friend class TensorBaseReadOnly;
	template <typename OtherDerived, typename Scal_, int NumIndices_> friend class TensorBaseWrite;
};

template <typename LhsDerived, typename RhsDerived, typename Scalar_, int NumIndices_>
class TensorBinaryCalc<LhsDerived, RhsDerived, Scalar_,NumIndices_, BINARY_BASE>
{
public:
	typedef Scalar_ ScalarType;
 	TensorBinaryCalc(const LhsDerived & lhs, const RhsDerived& rhs, int paramType)
 		: m_lhs(lhs), m_rhs(rhs), m_nCalcType(paramType) {}
 	
	// The meta four
	inline const IndexType dim(int n) const { return  m_lhs.rank() != 0 ? m_lhs.dim(n) : m_rhs.dim(n); }
	inline const IndexType size() const { return  m_lhs.rank() != 0 ? m_lhs.size() : m_rhs.size(); }
	inline std::vector<IndexType> dimensions() const { return  m_lhs.rank() != 0 ? m_lhs.dimensions() : m_rhs.dimensions();  }

protected:
	int m_nCalcType;
	const LhsDerived m_lhs;
	const RhsDerived m_rhs;
};

/**
 * Dummy Template Class for all specialization
 */
template <typename LhsDerived, typename RhsDerived, typename Scalar_, int NumIndices_, int CalcType>
class TensorBinaryCalc : public TensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, BINARY_BASE>
{

};

// 1
_GENERATE_BINARY_OPERATOR_(EWISE_ADD, +)

// 2
_GENERATE_BINARY_OPERATOR_(EWISE_SUBTRACT,-)

// 3
_GENERATE_BINARY_OPERATOR_(EWISE_MULTIPLICATE,*)

// 4
_GENERATE_BINARY_OPERATOR_(EWISE_DEVIDE,/)

// 5
_GENERATE_BINARY_OPERATOR_(EWISE_GREATER, > )

// 6
_GENERATE_BINARY_OPERATOR_(EWISE_GREATEREQUAL, >= )

// 7 
_GENERATE_BINARY_OPERATOR_(EWISE_EQUAL, == )

// 8
_GENERATE_BINARY_OPERATOR_(EWISE_NEQ, != )

// 9
_GENERATE_BINARY_OPERATOR_(EWISE_LESS, < )

// 10
_GENERATE_BINARY_OPERATOR_(EWISE_LESSEQUAL, <= )

// 11
_GENERATE_BINARY_OPERATOR_(EWISE_AND, && )

// 12
_GENERATE_BINARY_OPERATOR_(EWISE_OR, || )

// 13
_GENERATE_BINARY_OPERATOR_(EWISE_XOR, ^ )

// 14 Rhs must be Rhs Scalar
template < typename LhsDerived, typename RhsScalar, typename Scalar_, int NumIndices_>
class TensorBinaryCalc<LhsDerived, RhsScalar, Scalar_, NumIndices_, EWISE_POW >
	: public TensorBinaryCalc<LhsDerived, RhsScalar, Scalar_, NumIndices_, BINARY_BASE>
	, public TensorBaseReadOnly< TensorBinaryCalc<LhsDerived, RhsScalar, Scalar_, NumIndices_, EWISE_POW>, Scalar_, NumIndices_ >
{																								
public:																							
	TensorBinaryCalc(const LhsDerived & lhs, const RhsScalar& rhs)
	: TensorBinaryCalc<LhsDerived, RhsScalar, Scalar_, NumIndices_, BINARY_BASE>(lhs, rhs, EWISE_POW) {}
	auto eval() const  -> decltype(m_lhs.eval().pow(m_rhs.eval()))								
{																							
		return m_lhs.eval().pow(m_rhs.eval());													
}																							
};



template <typename Derived, typename Scalar_, int NumIndices_>
class TensorUnaryCalc<Derived, Scalar_, NumIndices_, UNARY_BASE>
{
public:
	//typedef Scalar_ ScalarType;
	TensorUnaryCalc(const Derived& src, int paramType)
		: m_src(src), m_nCalcType(paramType) {}

	inline constexpr int rank() const { return NumIndices_; }
	inline const IndexType dim(int n) const { return m_src.dim(n); }
	inline const IndexType size() const { return m_src.size(); }
	inline std::vector<IndexType> dimensions() const { return m_src.dimensions(); }

protected:
	int m_nCalcType;
	const Derived m_src;
};

// dummy unary not specialized template class


// 1
_GENERATE_UNARY_OPERATOR_(EWISE_NEGATIVE, -m_src.eval())

// 3
_GENERATE_UNARY_OPERATOR_(EWISE_SQRT, m_src.eval().sqrt())

// 4
_GENERATE_UNARY_OPERATOR_(EWISE_SQUARE, m_src.eval().square())

// 5
_GENERATE_UNARY_OPERATOR_(EWISE_EXP, m_src.eval().exp())

// 6
_GENERATE_UNARY_OPERATOR_(EWISE_LOG, m_src.eval().log())

// 7
_GENERATE_UNARY_OPERATOR_(EWISE_CEIL, m_src.eval().ceil())

// 8
_GENERATE_UNARY_OPERATOR_(EWISE_FLOOR, m_src.eval().floor())

// 9
_GENERATE_UNARY_OPERATOR_(EWISE_ROUND, m_src.eval().round())




/**
* Dummy Template Class for all specialization
*/



template <typename Derived, typename Scalar_, int NumIndices_,  int CalcType>
class TensorUnaryCalc
	: public TensorUnaryCalc<Derived, Scalar_, NumIndices_,  UNARY_BASE>
{

};


}
