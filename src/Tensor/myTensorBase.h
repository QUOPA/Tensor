#pragma once

template < typename T, unsigned int Rank, typename Derived>
class myTensorBase {
public:
	myTensorBase(const std::vector<T>& vecData, const std::vector<unsigned int>& vecDim);
	myTensorBase(std::vector<T>&& vecData, const std::vector<unsigned int>& vecDim);

	template<typename OtherDerived> inline
		const DLTensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_ADD> operator+(const DLTensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return derived().EAdd(rhs.derived());
	}

	inline const DLTensorBinaryCalc<Derived, DLScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_ADD> operator+(Scalar_ rhs) const
	{
		return derived().EAdd(DLScalarType<Scalar_>(rhs));
	}

	inline friend const DLTensorBinaryCalc<DLScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_ADD>
		operator+ (Scalar_ lhs, const Derived& rhs)
	{
		return DLTensorBinaryCalc<DLScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_ADD>(DLScalarType<Scalar_>(lhs), rhs.derived());
	}

	// ---- Subtraction ---

	template<typename OtherDerived> inline
		const DLTensorBinaryCalc<Derived, OtherDerived, Scalar_, NumIndices_, EWISE_SUBTRACT> operator-(const DLTensorBaseReadOnly<OtherDerived, Scalar_, NumIndices_>& rhs) const
	{
		return derived().ESub(rhs.derived());
	}

	inline const DLTensorBinaryCalc<Derived, DLScalarType<Scalar_>, Scalar_, NumIndices_, EWISE_SUBTRACT> operator-(Scalar_ rhs) const
	{
		return derived().ESub(DLScalarType<Scalar_>(rhs));
	}

	inline friend const DLTensorBinaryCalc<DLScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_SUBTRACT>
		operator- (Scalar_ lhs, const Derived& rhs) {
		return DLTensorBinaryCalc<DLScalarType<Scalar_>, Derived, Scalar_, NumIndices_, EWISE_SUBTRACT>(DLScalarType<Scalar_>(lhs), rhs.derived());
	}


private:

	const Derived* derived() const { return static_cast< const Derived * >(this);}
	Derived* derived() { return static_cast<Derived*>(this); }

	unsigned int calcVecsize(const std::vector<unsigned int>& vecDim);
};

