#pragma once

#include "myTensorBase.h"

enum TENSOR_BINARY_CALC {
	BINARY_BASE = -1,			// Save lhs, rhs data
	BINARY_CUSTOM = 0,			// CUSTOM function
	EWISE_ADD = 1,				// A + B
	EWISE_SUBTRACT = 2,			// A - B
	EWISE_MULTIPLICATE = 3,		// EMul(A,B)
	EWISE_DEVIDE = 4,			// EDiv(A,B)
	EWISE_GREATER = 5,			// A > B
	EWISE_GREATEREQUAL = 6,		// A >= B
	EWISE_EQUAL = 7,			// A == B
	EWISE_NEQ = 8,				// A != B
	EWISE_LESS = 9,				// A < B
	EWISE_LESSEQUAL = 10,		// A <= B
	EWISE_AND = 11,				// A && B
	EWISE_OR = 12,				// A || B
	EWISE_XOR = 13,				// A ^ B
	EWISE_POW = 14				// EPow(A,B)
};


#define _GENERATE_BINARY_OPERATOR_(TENum, Otor)													\
template < typename LhsDerived, typename RhsDerived, typename Scalar_ , int NumIndices_>		\
class DLTensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, TENum >					\
	: public DLTensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_,  BINARY_BASE>		\
	, public DLTensorBaseReadOnly< DLTensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, TENum>, Scalar_, NumIndices_> \
{																								\
public:																							\
	DLTensorBinaryCalc(const LhsDerived & lhs, const RhsDerived& rhs)							\
	: DLTensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, BINARY_BASE>(lhs, rhs, TENum) {}	\
	auto eval() const  -> decltype(m_lhs.eval() Otor m_rhs.eval())								\
	{																							\
		return m_lhs.eval() Otor m_rhs.eval();													\
	}																							\
};																							


/**
 * Dummy Template Class for all specialization
 */
template <typename LhsDerived, typename RhsDerived, typename Scalar_, int NumIndices_, int CalcType>
class DLTensorBinaryCalc : public DLTensorBinaryCalc<LhsDerived, RhsDerived, Scalar_, NumIndices_, BINARY_BASE>
{

};


// 1
_GENERATE_BINARY_OPERATOR_(EWISE_ADD, +)

// 2
_GENERATE_BINARY_OPERATOR_(EWISE_SUBTRACT, -)