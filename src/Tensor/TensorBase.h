#pragma once


#include "Tensor/Tensor.h"
#include "Tensor/TensorArithmetic.h"
#include "Tensor/TensorReference.h"
#include "Tensor/TensorCommon.h"

#include <vector>
#include <memory>
#include <utility>
#include <type_traits>
#include <algorithm>
#include <tuple>


namespace tens{

template <typename LhsDerived, typename RhsDerived, typename Scalar_, int NumIndices_, int CalcType>
class TensorBinaryCalc;

template <typename Derived, typename Scalar_, int NumIndices_, int CalcType>
class TensorUnaryCalc;

template <typename Scalar_, int Numindices>
class Tensor;

template <typename Scalar_>
class ScalarType;

template <typename Otherderived, typename Scalar_>
class TensorMatrix;


/**
 * Read-Only Tensor Base Class.
 * This class declares and defines the list of operators that all derived classes(Data classes or Proxy classes) have. Derived classes of this class read-only access
 * 
 * \param Derived The derived format (CRTP)
 */

using RngVec = std::vector<IndexType>;

template<typename Derived, typename Scalar_, int NumIndices_>
class TensorBaseWrite;


template<typename Derived,typename Scalar_, int NumIndices_>
class TensorBaseReadOnly{
public:  
	// Elem-Wise Operator multiplication (member version)

protected:

	const Derived & createReference() const { return derived(); }
	Derived & createReference() { return derived(); }
	

	template<typename OtherDerived> inline
	const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_,  EWISE_ADD> EAdd(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_ADD>(createReference(), rhs.createReference());
	}

	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_SUBTRACT> ESub(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_SUBTRACT>(createReference(), rhs.createReference());
	}


//  	template<typename OtherDerived> inline
//  	const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_MULTIPLICATE> EMul(const OtherDerived & rhs) const
//  	{
//  		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_MULTIPLICATE>(createReference(), rhs.createReference());
//  	}
//  
//  	template<typename OtherDerived> inline
//  	const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_DEVIDE> EDiv(const OtherDerived & rhs) const
//  	{
//  		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_DEVIDE>(createReference(), rhs.createReference());
//  	}

	template<typename OtherDerived> inline
	const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_GREATER> EGreater(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_GREATER>(createReference(), rhs.createReference());
	}

	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_GREATEREQUAL> EGreaterEqual(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_GREATEREQUAL>(createReference(), rhs.createReference());
	}

	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_EQUAL> EEqual(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_EQUAL>(createReference(), rhs.createReference());
	}

	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_NEQ> ENotequal(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_NEQ>(createReference(), rhs.createReference());
	}

	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_LESS> ELess(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_LESS>(createReference(), rhs.createReference());
	}

	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_LESSEQUAL> ELessEqual(const OtherDerived & rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_LESSEQUAL>(createReference(), rhs.createReference());
	}
	

public:
	/**
	* Element-wise addition operatro
	* ex) A + B + C + D
	*
	* \param rhs rhs operand
	* \return Proxy class having the types of rhs, lfs, and enum index for choosing operation
	*/
	// ---- addition -----

	template<typename OtherDerived> inline
	const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_ADD> operator+(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().EAdd(rhs.createReference());
	}
	
	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_ADD> operator+( Scalar_ rhs) const
 	{
 		return createReference().EAdd(ScalarType<Scalar_>(rhs));
 	}
	
	inline friend const TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_ADD>
		operator+ (Scalar_ lhs, const Derived& rhs) 
	{
		return TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_ADD>(ScalarType<Scalar_>(lhs), rhs.createReference());
	}

	// ---- Subtraction ---

	template<typename OtherDerived> inline
	const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_SUBTRACT> operator-(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().ESub(rhs.createReference());
	}
	
	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_SUBTRACT> operator-(Scalar_ rhs) const
	{
		return createReference().ESub(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_SUBTRACT>
		operator- (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_SUBTRACT>(ScalarType<Scalar_>(lhs), rhs.createReference());
	}
		

	// ---- Multiplication ---

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_MULTIPLICATE>
		operator*(const Derived& lhs, Scalar_ rhs) {
		return TensorBinaryCalc< Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_MULTIPLICATE>( lhs.createReference(), DLScalarType<Scalar_>(rhs) );
	}

	inline friend const TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_MULTIPLICATE>
		operator*(Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_MULTIPLICATE>(ScalarType<Scalar_>(lhs), rhs.createReference());
	}

	template<typename OtherDerived>
	inline friend const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_MULTIPLICATE>
		EMul(const Derived & lhs, const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) {
		return TensorBinaryCalc< Derived, OtherDerived, Scalar_, NumIndices_, EWISE_MULTIPLICATE>(lhs.createReference(), rhs.createReference());
	}

	// ---- Division ----

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_DEVIDE>
		operator/(const Derived& lhs, Scalar_ rhs) {
		return TensorBinaryCalc< Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_DEVIDE>(lhs.createReference(), DLScalarType<Scalar_>(rhs) );
	}

	inline friend const TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_DEVIDE>
		operator/(Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<ScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_DEVIDE>(ScalarType<Scalar_>(lhs), rhs.createReference());
	}

	template<typename OtherDerived>
	inline friend const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_DEVIDE>
		EDiv(const Derived & lhs, const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) {
		return TensorBinaryCalc< Derived, OtherDerived, Scalar_, NumIndices_, EWISE_DEVIDE>(lhs.createReference(), rhs.createReference());
	}

	// ---- Greater ----
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_GREATER> operator>(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().EGreater(rhs.createReference());
	}

	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_GREATER> operator>(Scalar_ rhs) const
	{
		return createReference().EGreater(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_LESS>
		operator> (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_LESS>(rhs.createReference(), DLScalarType<Scalar_>(lhs));
	}


	// ---- Greater Equal ----
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_GREATEREQUAL> operator>=(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().EGreaterEqual(rhs.createReference());
	}

	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_GREATEREQUAL> operator>=(Scalar_ rhs) const
	{
		return createReference().EGreaterEqual(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_LESSEQUAL>
		operator>= (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_LESSEQUAL>(rhs.createReference(), DLScalarType<Scalar_>(lhs));
	}

	// ---- Equal ----
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_EQUAL> operator==(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().EEqual(rhs.createReference());
	}

	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_EQUAL> operator==(Scalar_ rhs) const
	{
		return createReference().EEqual(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_EQUAL>
		operator== (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_EQUAL>(rhs.createReference(), DLScalarType<Scalar_>(lhs));
	}


	// ---- NOT Equal ----
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_NEQ> operator!=(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().ENotequal(rhs.createReference());
	}

	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_NEQ> operator!=(Scalar_ rhs) const
	{
		return createReference().ENotequal(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_NEQ>
		operator!= (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_NEQ>(rhs.createReference(), DLScalarType<Scalar_>(lhs));
	}

	// ---- LESS ----
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_LESS> operator<(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().ELess(rhs.createReference());
	}

	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_LESS> operator<(Scalar_ rhs) const
	{
		return createReference().ELess(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_GREATER>
		operator< (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_GREATER>(rhs.createReference(), DLScalarType<Scalar_>(lhs));
	}


	// ---- LESS or EQUAL ----
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_LESSEQUAL> operator<=(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return createReference().ELessEqual(rhs.createReference());
	}

	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_LESSEQUAL> operator<=(Scalar_ rhs) const
	{
		return createReference().ELessEqual(ScalarType<Scalar_>(rhs));
	}

	inline friend const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_GREATEREQUAL>
		operator<= (Scalar_ lhs, const Derived& rhs) {
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_GREATEREQUAL>(rhs.createReference(), DLScalarType<Scalar_>(lhs));
	}

	// --- And ---
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_AND> operator&&(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_AND>(createReference(), rhs.createReference());
	}

	// --- OR ---
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_OR> operator||(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_OR>(createReference(), rhs.createReference());
	}

	// --- Xor ---
	template<typename OtherDerived> inline
		const TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_XOR> operator^(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return TensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_XOR>(createReference(), rhs.createReference());
	}

	// --- Negative -- 
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_NEGATIVE> operator-() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_NEGATIVE>(createReference());
	}

	// ---- Not ---- 
// 	inline const TensorBinaryCalc<Derived, , Scalar_, NumIndices_, EWISE_XOR> operator^(const TensorBaseReadOnly<OtherDerived, Scalar_>& rhs) const
// 	{
// 		return TensorBinaryCalc<Derived, , Scalar_, NumIndices_, EWISE_XOR>(createReference(), rhs.createReference());
// 	}
	
	// --- EPow ----
	// Eigen::Tensor determines the type of function argument as the type of the function calling Tensor's type.
	inline const TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_POW> EPow(Scalar_ rhs) const
	{
 		if (std::is_integral<Scalar_>::value && rhs < 0) // eigen::tensor bug
 		{
 			throw numeric_range_error("DLTensorBase::EPow - Exponent rhs is out of range");
 		}
		return TensorBinaryCalc<Derived, ScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_POW>(createReference(), ScalarType<Scalar_>(rhs));
	}

	// --- ESquare ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_SQUARE> ESquare() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_SQUARE>(createReference());
	}

	// --- ESqrt ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_SQRT> ESqrt() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_SQRT>(createReference());
	} 

	// --- natural Exponential ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_EXP> EExp() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_EXP>(createReference());
	}

	// --- natural log ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_LOG> ELog() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_LOG>(createReference());
	}

	// --- ceil ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_CEIL> ECeil() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_CEIL>(createReference());
	}

	// --- floor ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_FLOOR> EFloor() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_FLOOR>(createReference());
	}

	// --- round ---
	inline	const TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_ROUND> ERound() const
	{
		return TensorUnaryCalc<Derived, Scalar_, NumIndices_, EWISE_ROUND>(createReference());
	}

	// --- 

	// --- slice ---




	const Derived & derived() const & { return *static_cast<const Derived*>(this); }

	constexpr int rank() { return NumIndices_; }

protected:

	// utils

	template <typename Scal_, int NumIndices> friend class Tensor;
	template <typename OtherDerived, typename Scal_, int NumIndices> friend class TensorBaseReadOnly;
	template <typename OtherDerived, typename Scal_, int NumIndices> friend class TensorBaseWrite;
};


template<typename Derived, typename Scalar_ , int NumIndices_>
class TensorBaseWrite : public TensorBaseReadOnly<Derived, Scalar_, NumIndices_> {
public:

	template<typename OtherType> inline
	void operator+=(const OtherType & other) 
	{
		derived() = derived() + other ;
	}

	template<typename OtherType> inline
	void operator-=(const  OtherType & other)
	{
		derived() = derived() - other ;
	}

	inline void operator*=(const  Scalar_ & other) 
	{
		derived() = derived() * other;
	}

	inline void operator/=(const  Scalar_ & other) 
	{
		derived() = derived() / other;
	}

 	template<typename OtherDerived> inline
 	void EMulAssign(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& other)
 	{
 		derived()  = EMul(derived(),other)
 	}
 
	template<typename OtherDerived> inline
 	void EDivAssign(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& other)
 	{
		derived() = EDiv(derived(), other)
 	}
	
	// Rank Specified Index slicing ~ 4
	
	template<int dim1>  
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByIndex(IndexType idx1) const
	{ 
		return getSlicebyInd({ dim1 }, { idx1 }); 
	}
	template<int dim1, int dim2>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByIndex(IndexType idx1, IndexType idx2) const
	{
		return getSlicebyInd({ dim1, dim2 }, { idx1 , idx2 });
	}
	
	template<int dim1, int dim2, int dim3>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByIndex(IndexType idx1, IndexType idx2, IndexType idx3) const
	{
		return getSlicebyInd({ dim1, dim2, dim3 }, { idx1 , idx2, idx3 });
	}
	
	template<int dim1, int dim2, int dim3, int dim4>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByIndex(IndexType idx1, IndexType idx2, IndexType idx3, IndexType idx4) const
	{
		return getSlicebyInd({ dim1, dim2, dim3 , dim4 }, { idx1 , idx2, idx3, idx4 });
	}
	
	// Ordered N-Rank  Index Slicing ~ infinity
	template <typename... IndTypes>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByIndex(IndexType idx1, IndTypes... indOthers) const;

	// Rank Specified Range slicing ~ 4
	template<int dim1>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1) const
	{
		return getSlicebyRng({ dim1 }, { rng1 });
	}
	template<int dim1, int dim2>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1, const RngVec & rng2) const
	{
		return getSlicebyRng({ dim1, dim2 }, { rng1, rng2 });
	}
	template<int dim1, int dim2, int dim3>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1, const RngVec & rng2, const RngVec & rng3) const
	{
		return getSlicebyRng({ dim1, dim2, dim3 }, { rng1, rng2, rng3 });
	}

	template<int dim1, int dim2, int dim3, int dim4>
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1, const RngVec & rng2, const RngVec & rng3, const RngVec & rng4) const
	{
		return getSlicebyRng({ dim1, dim2, dim3, dim4 }, { rng1, rng2, rng3, rng4 });
	}

	// Ordered N-Rank  Index Slicing  ~ 4
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1)  const {	return sliceByRange<0>(rng1); }
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1, const RngVec & rng2) const  {	return sliceByRange<0,1>(rng1, rng2); }
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1, const RngVec & rng2, const RngVec & rng3) const {   return sliceByRange<0,1,2>(rng1, rng2, rng3); }
	DLTensorSliced<Derived, Scalar_, NumIndices_ >  sliceByRange(const RngVec & rng1, const RngVec & rng2, const RngVec & rng3, const RngVec & rng4) const { return sliceByRange<0, 1, 2, 3>(rng1, rng2, rng3, rng4); }

	DLTensorSliced<Derived, Scalar_, NumIndices_ > getSlicebyInd(const std::vector<int>& Ranks, const std::vector<IndexType>& Dims) const;
	DLTensorSliced<Derived, Scalar_, NumIndices_ > getSlicebyRng(const std::vector<int>& Ranks, const std::vector<RngVec>& Rngs) const;

	template <int DimId>
	const DLTensorChipped<Derived, Scalar_, NumIndices_ - 1> chip(IndexType idx) const
	{
		return DLTensorChipped<Derived,Scalar_, NumIndices_ - 1>(&derived(), idx, DimId);
	}

	template <int DimId>
	DLTensorChipped<Derived, Scalar_, NumIndices_ - 1> chip(IndexType idx) 
	{
		return DLTensorChipped<Derived, Scalar_, NumIndices_ - 1>(&derived(), idx, DimId);
	}




	Derived& derived() & { return *static_cast<Derived*>(this); }
	const Derived& derived()  const & { return *static_cast<const Derived*>(this); }
protected:
	
	void genSliceVectors_impl(int &Count, std::array<IndexType, NumIndices_> & vecStart, std::array<IndexType, NumIndices_> & vecVolume, IndexType idx1) const;

	template <typename ...IndTypes>
	void genSliceVectors_impl(int &Count, std::array<IndexType, NumIndices_> & vecStart, std::array<IndexType, NumIndices_> & vecVolume, IndexType idx1, IndTypes... idxOthers) const;

	template <typename ...IndTypes>
	void getSliceVectors(std::array<IndexType, NumIndices_> & vecStart, std::array<IndexType, NumIndices_> & vecVolume, IndexType idx1, IndTypes... idxOthers) const ;
		

	void genSliceRngVectors_impl(int &Count, std::array<IndexType, NumIndices_> & vecStart, std::array<IndexType, NumIndices_> & vecVolume, const RngVec& rng1) const;

	template <typename ...RngTypes>
	void genSliceRngVectors_impl(int &Count, std::array<IndexType, NumIndices_> & vecStart, std::array<IndexType, NumIndices_> & vecVolume, const RngVec& rng1, RngTypes... rngOthers) const;

	template <typename ...RngTypes>
	void genSliceRngVectors(std::array<IndexType, NumIndices_> & vecStart, std::array<IndexType, NumIndices_> & vecVolume, const RngVec& rng1, RngTypes... rngOthers) const;

	inline bool isValidRank(int rankidx) const { return rankidx < derived().rank() && rankidx >= 0; }

	// rank size checker
	inline bool isValidRankMulti(int rankidx1) const { return isValidRank(rankidx1); }

	template <typename ...RnkIdices> 
	inline bool isValidRankMulti(int rankidx1, RnkIdices... rankOtherIdx) const
	{
		return isValidRankMulti(rankOtherIdx...) && isValidRank(rankidx1);
	}


	// dimension size checkers
	inline bool isValidIdx(int rnk, IndexType idx) const { return derived().dim(rnk) > idx && idx >= 0; }

	template <typename ...IdxTypes>
	inline bool isValidIdxUntil(int untilRnk, IndexType idx, IdxTypes... OtherIndices) const
	{
		return isValidIdxUntil(untilRnk - 1, OtherIndices...) && isValidIdx(untilRnk, idx);
	}

	inline bool isValidIdxUntil(int untilRnk, IndexType idx) const
	{
		return  isValidIdx(0, idx);
	}


	inline bool isValidRng(int rnk, const RngVec & rng) const
	{ 
		return derived().dim(rnk) > rng[1] && rng[1] >= rng[0] && rng[0] >= 0;
	}

	template <typename ...RngTypes>
	inline bool isValidRngUntil(int untilrnk, const RngVec & rng, RngTypes... OtherRanges) const
	{	
		return isValidRngUntil(untilrnk-1, OtherRanges...) && isValidRng(untilrnk, rng) ;
	}

	inline bool isValidRngUntil(int untilrnk, const RngVec & rng) const
	{
		return isValidRng(untilrnk, rng);
	}

	
	template <typename Scalar, int NumIndices> friend class Tensor;
	template <typename OtherDerived, typename Scal_, int NumIndices> friend class TensorBaseReadOnly;
	template <typename OtherDerived, typename Scal_, int NumIndices> friend class TensorBaseWrite;
};



template<typename Derived, typename Scalar_, int NumIndieces>
template <typename... IndTypes>
DLTensorSliced<Derived, Scalar_, NumIndieces> TensorBaseWrite<Derived, Scalar_, NumIndieces>::sliceByIndex(IndexType idx1, IndTypes... indOthers) const
{
	constexpr int MaxRnkIdx = sizeof...(IndTypes) ;

	if ( !isValidRankMulti(MaxRnkIdx))
		throw tensor_rank_error("Access to range out of rank : DLTensorBase<>::sliceByIndex()");

	if ( !isValidIdxUntil(MaxRnkIdx, idx1, indOthers...) )
		throw tensor_dimension_error("Access to range out of the dimension : DLTensorBase<>::sliceByIndex()");

	std::array < IndexType, NumIndieces > idxStart;
	idxStart.fill(0);
	std::array<IndexType, NumIndieces> idxRange;
	std::copy_n(derived().dimensions().begin(), NumIndieces, idxRange.begin());

	getSliceVectors(idxStart, idxRange, idx1, indOthers...);

	return DLTensorSliced<Derived, Scalar_, NumIndieces>(&derived(), idxStart, idxRange);
}



template<typename Derived, typename Scalar_, int NumIndices_>
inline DLTensorSliced<Derived, Scalar_, NumIndices_> TensorBaseWrite<Derived, Scalar_, NumIndices_>::getSlicebyInd(const std::vector<int>& Ranks, const std::vector<IndexType>& Dims) const
{
	if (Ranks.size() != Dims.size())
		throw size_nomatch_error("Ranks and Dims vector sizes are different");
	bool bRankValid = true;
	bool bDimValid = true;
	for (int i = 0; i < Ranks.size(); i++)
	{
		bRankValid &= isValidRank(Ranks[i]);
		bDimValid &= isValidIdx(Ranks[i], Dims[i]);
	}
	if (!bRankValid)
		throw tensor_rank_error("Access to range out of rank : DLTensorBase<>::sliceByIndex<>()");
	if (!bDimValid)
		throw tensor_dimension_error("Access to range out of the dimension : DLTensorBase<>::sliceByIndex<>()");

	std::array < IndexType, NumIndices_> idxStart;
	idxStart.fill(0);
	std::array<IndexType, NumIndices_> idxRange;
	std::copy_n(derived().dimensions().begin(), NumIndices_, idxRange.begin());

	for (int i = 0; i < Ranks.size(); i++)
	{
		idxStart[Ranks[i]] = Dims[i];
		idxRange[Ranks[i]] = 1;
	}
	return DLTensorSliced<Derived, Scalar_, NumIndices_>(&derived(), idxStart, idxRange);
}

template<typename Derived, typename Scalar_, int NumIndices_>
inline DLTensorSliced<Derived, Scalar_, NumIndices_> TensorBaseWrite<Derived, Scalar_, NumIndices_>::getSlicebyRng(const std::vector<int>& Ranks, const std::vector<std::vector<IndexType>>& Rngs) const
{
	if (Ranks.size() != Rngs.size())
		throw size_nomatch_error("Ranks and Dims vector sizes are different");

	bool bRankValid = true;
	bool bDimValid = true;
	
	for (int i = 0; i < Ranks.size(); i++)
	{
		bRankValid &= isValidRank(Ranks[i]);
		bDimValid &= isValidRng(Ranks[i], Rngs[i]);
	}

	if (!bRankValid)
		throw tensor_rank_error("Access to range out of rank : DLTensorBase<>::sliceByRange<>()");
	if (!bDimValid)
		throw tensor_dimension_error("Access to range out of the dimension : DLTensorBase<>::sliceByRange<>()");

	std::array < IndexType, NumIndices_> idxStart;
	idxStart.fill(0);
	std::array<IndexType, NumIndices_> idxRange;
	std::copy_n(derived().dimensions().begin(), NumIndices_, idxRange.begin());

	for (int i = 0; i < Ranks.size(); i++)
	{
		idxStart[Ranks[i]] = Rngs[i][0];
		idxRange[Ranks[i]] = Rngs[i][1] - Rngs[i][0] + 1;
	}
	return DLTensorSliced<Derived, Scalar_, NumIndices_>(&derived(), idxStart, idxRange);
}

template<typename Derived, typename Scalar_, int NumIndieces>
void TensorBaseWrite<Derived, Scalar_, NumIndieces>::genSliceVectors_impl(int &Count, std::array<IndexType, NumIndieces> & vecStart, std::array<IndexType, NumIndieces> & vecVolume, IndexType idx1) const
{
	vecStart[0] = idx1;
	vecVolume[0] = 1;
	Count = 1;
}

template<typename Derived, typename Scalar_, int NumIndieces>
template<typename ...IndTypes>
void TensorBaseWrite<Derived, Scalar_, NumIndieces>::genSliceVectors_impl(int &Count, std::array<IndexType, NumIndieces> & vecStart, std::array<IndexType, NumIndieces> & vecVolume, IndexType idx1, IndTypes... idxOthers) const
{
	genSliceVectors_impl(Count, vecStart, vecVolume, idxOthers...);
	vecStart[Count] = idx1;
	vecVolume[Count] = 1;
	++Count;
}

template<typename Derived, typename Scalar_, int NumIndieces>
template <typename ...IndTypes>
void TensorBaseWrite<Derived, Scalar_, NumIndieces>::getSliceVectors(std::array<IndexType, NumIndieces> & vecStart, std::array<IndexType, NumIndieces> & vecVolume, IndexType idx1, IndTypes... idxOthers) const
{
	int count;
	genSliceVectors_impl(count, vecStart, vecVolume, idx1, idxOthers...);
}


template<typename Derived, typename Scalar_, int NumIndieces>
void TensorBaseWrite<Derived, Scalar_, NumIndieces>::genSliceRngVectors_impl(int &Count, std::array<IndexType, NumIndieces> & vecStart, std::array<IndexType, NumIndieces> & vecVolume, const std::vector<IndexType>& rng1) const
{
	vecStart[0] = rng1[0];
	vecVolume[0] = rng1[1] - rng1[0] + 1;
	Count = 1;
}

template<typename Derived, typename Scalar_, int NumIndieces>
template<typename ...RngTypes>
void TensorBaseWrite<Derived, Scalar_, NumIndieces>::genSliceRngVectors_impl(int &Count, std::array<IndexType, NumIndieces> & vecStart, std::array<IndexType, NumIndieces> & vecVolume, const std::vector<IndexType> & rng1, RngTypes... rngOthers) const
{
	genSliceRngVectors_impl(Count, vecStart, vecVolume, rngOthers...);
	vecStart[Count] = rng1[0];
	vecVolume[Count] = rng1[1] - rng1[0] + 1;
	++Count;
}

template<typename Derived, typename Scalar_, int NumIndieces>
template <typename ...RngTypes>
void TensorBaseWrite<Derived, Scalar_, NumIndieces>::genSliceRngVectors(std::array<IndexType, NumIndieces> & vecStart, std::array<IndexType, NumIndieces> & vecVolume, const std::vector<IndexType>& rng1, RngTypes... rngOthers) const
{
	int count;
	genSliceRngVectors_impl(count, vecStart, vecVolume, idx1, rngOthers...);
}



}

