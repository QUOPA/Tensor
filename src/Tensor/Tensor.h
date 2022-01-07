#pragma once

#include <memory>
#include <algorithm>

#include "Tensor/TensorCommon.h"
#include "Tensor/TensorArithmetic.h"
#include "Tensor/TensorMatrix.h"
#include "Tensor/TensorException.h"


namespace tens{

template <typename Scalar_, int NumIndices_>
class Tensor : public TensorBaseWrite<Tensor<Scalar_, NumIndices_> , Scalar_ , NumIndices_>
{	
public:  
	// Ctors
	typedef Tensor <Scalar_, NumIndices_> SELF;
	typedef TensorBaseWrite < Tensor<Scalar_, NumIndices_>, Scalar_, NumIndices_> SELFBASE;

	//Tensor() {};
	template<typename... IndexTypes>
	explicit Tensor(IndexType firstDimension, IndexTypes... otherDimensions) 
	{ 
		resizeclear(firstDimension, otherDimensions...); 
	}

	explicit Tensor( const std::vector<IndexType> & dimVec ) 
	{
		ErrIfNot<tensor_rank_error>(dimVec.size() == NumIndices_, "Input vector size is not the same with tensor rank size - DLTEnsor::DLTEnsor(vector)");
		std::array<IndexType, NumIndices_> arrDims;
		std::copy_n(dimVec.begin(), NumIndices_, arrDims.begin());
	}

	// for pre definition before assignment
	Tensor() {}

	// Ctors Copy/Move 
	Tensor(const Tensor & rhs) 
	{
		this->operator=(rhs);
	}
	
	Tensor(Tensor && rhs) 
	{
		this->operator=(std::move(rhs));
	}
	
	void operator=(const Tensor & rhs) 
	{
		m_pvecData.reset( new std::vector<Scalar>(*rhs.m_pvecData))
		copyArrDimFrom( rhs.dimensions() );
	}
	
	void operator=(Tensor && rhs) 
	{
		m_pvecData = std::move ( rhs.m_pvecData );
		copyArrDimFrom( rhs.dimensions() );
	}

	Tensor createReference() 
	{
		Tensor retTen;
		retTen.m_pvecData = this->m_pvecData;
		retTen.copyArrDimFrom(this->dimensions());
		return retTen;
	}


	template<typename OtherDerived>
	Tensor(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& other) { *this = other }
	
	template<typename OtherDerived>
	void operator=(const TensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_> & other) { *this = other.eval(); }

	void operator=(const Scalar_ & val) { setConstant(val); }

	// create datastore and set dimensions
	template<typename... IndexTypes>
	void resizeClear(IndexType firstDimension, IndexTypes... otherDimensions) 
	{ 
		vecData.resize(getMultiples(firstDimension, otherDimensions...));
		resize(firstDimension, otherDimensions...);
	}

	template <typename... IndexTypes>
	void resizeSafe(IndexType firstDimension, IndexTypes... otherDimensions)
	{
		if (getMultiples(firstDimension, otherDimensions...) != this->size())
			throw size_nomatch_error("resize fail : size calculated from input dimensions are not the same with src data vector size");
		resize(firstDimension, otherDimensions...);
	}

	void copyDataFrom(Scalar_ * dataPtr, IndexType sizechecker);
	// copy data from datasource as ptrData. Check size of vector of all data in tensor and 'sizechecker'
	
	void setConstant(Scalar_ Val);
	void setLinSpaced(Scalar_ lowval, Scalar_ highval)
	{
		double Interval = highval - lowval;
		double Increm = Interval / size();
		std::vector<Scalar_> vecTmp(size());
		for (int i = 0; i < size(); i++)
			vecTmp[i] = lowval + Increm*i;
		copyDataFrom(vecTmp.data(), vecTmp.size());
	}

	void setLinSpaced(Scalar_ lowval)
	{
		setLinSpaced(lowval, lowval +size());
	}

	// return data
	Scalar_ *data()	{ return vecData.data(); }
	const Scalar_ *data() const { return vecData.data(); }

	Scalar_* begin() { return vecData.data(); }
	const Scalar_ * begin() const { return vecData.data(); }
	
	Scalar_* end() { return vecData.data() + size(); }
	const Scalar_ * end() const { return vecData.data() + size(); }

	template <typename... IdxTypes>
	inline const Scalar_& operator()(IndexType firstIdx, IdxTypes... otherIndices) const
	{
		return m_pvecData->operator[](getDataIdx(firstIdx, otherIndices...));
	}

	template <typename... IdxTypes>
	inline Scalar_& operator()(IndexType firstIdx, IdxTypes... otherIndices)
	{
		return m_pvecData->operator[](getDataIdx(firstIdx, otherIndices...));
	}

	template <typename... IdxTypes>
	inline const Scalar_& element(IndexType firstIdx, IdxTypes... otherIndices) const
	{
		ErrIfNot<tensor_dimension_error>(checkDimensionInRange(firstIdx, otherIndices...), "Input vector size is not the same with tensor rank size");
		return m_pvecData->operator[](getDataIdx(firstIdx, otherIndices...));
	}

	template <typename... IdxTypes>
	inline Scalar_& element(IndexType firstIdx, IdxTypes... otherIndices)
	{
		ErrIfNot<tensor_dimension_error>(checkDimensionInRange(firstIdx, otherIndices...), "Input vector size is not the same with tensor rank size");
		return m_pvecData->operator[](getDataIdx(firstIdx, otherIndices...));
	}

	TensorMatrix< SELF ,Scalar_> asMat()
	{
		return TensorMatrix< SELF, Scalar_>(derived(), dimensions(), MATRIX_TYPE::MATRIX);
	}

	TensorMatrix< SELF, Scalar_> asRVec()
	{
		return TensorMatrix< SELF, Scalar_>(derived(), dimensions(), MATRIX_TYPE::ROWVECTOR);
	}

	TensorMatrix< SELF, Scalar_> asCVec()
	{
		return TensorMatrix< SELF, Scalar_>(derived(), dimensions(), MATRIX_TYPE::COLUMNVECTOR);
	}
	
	// the meta four
	constexpr int rank() const { return NumIndices_; }
	IndexType dim(int n) const { return arrDim[n]; }
	const std::vector<IndexType> dimensions() const { return std::vector<IndexType>( arrDim, arrDim + NumIndices_ ); }

	IndexType size() const 
	{ 
		IndexType retval = 1;
		for (int rnk = 0; rnk < NumIndices_; rnk++)
			retval *= arrDim[rnk];
		return retval;
	}

private:
	template <typename... IndexTypes>
	inline IndexType getMultiples(IndexType firstDimension, IndexTypes... otherDimensions) const 
	{ return firstDimension * getMultiples(otherDimensions...);}

	inline IndexType getMultiples(IndexType firstDimension) const  { return firstDimension; }

	template <typename... IndexTypes>
	inline bool checkDimensionInRange(IndexType firstDimension, IndexTypes... otherDimensions) const {
		return checkDimensionInRangeImpl(0, firstDimension, otherDimensions...);
	}
	template <typename... IndexTypes>
	inline bool checkDimensionInRangeImpl(int Rnk, IndexType firstDimension, IndexTypes... otherDimensions) const {
		return ((lastDimension < arrDim[Rnk] && arrDim[Rnk] >= 0) ? true : false ) && checkDimensionInRangeImpl(Rnk+1, firstDimension, otherDimensions...);}

	inline bool checkDimensionInRangeImpl(int Rnk, IndexType lastDimension) const {
		return (lastDimension < arrDim[Rnk] && arrDim[Rnk] >= 0 ) ? true : false ;}


	template<typename... IndexTypes>
	void resize(IndexType firstDimension, IndexTypes... otherDimensions) 
	{ 
		resizeImpl(0, firstDimension, otherDimensions...);
	}
	
	// read only
	const std::vector<Scalar_> & getVector() const { return &m_pvecData; }

private:
	template<typename... IndexTypes>
	void resizeImpl(int Rnk, IndexType firstDimension, IndexTypes... otherDimensions){
		arrDim[Rnk] = firstDimension;
		resizeImpl(Rnk + 1, otherDimensions...); }
	
	void resizeImpl(int Rnk, IndexType lastDimension) {
		arrDim[Rnk] = lastDimension; }
	
	void copyDataFrom(Scalar_ * dataPtr);
	
	template<typename... IndexTypes>
	inline IndexType getDataIdx(IndexType firstDimension, IndexTypes... otherDimensions) const {
		return getDataIdxImpl(0, firstDimension, otherDimensions...); }
	
	template<typename... IndexTypes>
	inline IndexType getDataIdxImpl(int Rnk, IndexType firstDimension, IndexTypes... otherDimensions) const {
		return firstDimension * ( arrDim[Rnk + 1] ) + getDataIdx(Rnk + 1, otherDimensions...); }
	
	template<typename... IndexTypes>
	inline IndexType getDataIdxImpl(int Rnk, IndexType firstDimension) const { return firstDimension;  }

	void copyArrDimFrom(const std::vector<IndexType>& rhs) 
	{ 
		for (int rnk = 0; rnk < NumIndices_; rnk++)
			arrDim[rnk] = rhs[rnk];
	}

protected:
	template <typename Derived, typename Scalar> friend class TensorMatrix;
	std::shared_ptr<std::vector<Scalar>> m_pvecData;
	IndexType arrDim[NumIndices_];
};

template<typename Scalar_, int NumIndices_>
void Tensor<Scalar_, NumIndices_>::setConstant(Scalar_ Val)
{
	std::fill(m_pvecData->begin(), m_pvecData->end(), Val);
}

template<typename Scalar_, int NumIndices_>
void Tensor<Scalar_, NumIndices_>::copyDataFrom(Scalar_ * dataPtr)
{
	std::copy(dataPtr, dataPtr + size(), m_pvecData->begin());
}


template<typename Scalar_, int NumIndices_>
void Tensor<Scalar_, NumIndices_>::copyDataFrom(Scalar_*  dataPtr, IndexType sizeChecker)
{
	IndexType totalSize = size();
	if (totalSize != sizeChecker)
		throw size_nomatch_error("different vector size between data source and tensor");
	
	copyDataFrom(dataPtr);
	
}

}