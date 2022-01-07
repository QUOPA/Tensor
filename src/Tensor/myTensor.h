#pragma once

#include "myTensorBase.h"
#include <vector>

template < typename T, unsigned int Rank>
class myTensor : public myTensorBase< T, Rank, typename myTensor::Type > {
public:
	using Type = myTensor<T, Rank>;
	using Scalar = T;


	myTensor(const std::vector<T>& vecData, const std::vector<unsigned int>& vecDim );
	myTensor(std::vector<T> && vecData , const std::vector<unsigned int>& vecDim);

private:
	std::vector<T> m_vecData;
	
	void setDimension(const std::vector<unsigned int>& vecDim);

	unsigned int calcVecsize(const std::vector<unsigned int> & vecDim);
	unsigned int Dimensions[Rank];
};

template<typename T, unsigned int Rank>
inline myTensor<T, Rank>::myTensor(const std::vector<T> & vecData, const std::vector<unsigned int> & vecDim)
{
	if (vecData.size() != calcVecsize(vecDim))
		throw std::exception("Tensor dimensions not match");

	if (vecDim.size() >  Rank)
		throw std::exception("Tensor rank out of bound");

	m_vecData = vecData;
	
	setDimension(vecDim);


}

template<typename T, unsigned int Rank>
inline myTensor<T, Rank>::myTensor(std::vector<T>&& vecData, const std::vector<unsigned int>& vecDim)
{
	if (vecData.size() != calcVecsize(vecDim))
		throw std::exception("Tensor dimensions not match");

	if (vecDim.size() > Rank)
		throw std::exception("Tensor rank out of bound");

	m_vecData = std::move(vecData);
	
	setDimension(vecDim);

}

template<typename T, unsigned int Rank>
inline void myTensor<T, Rank>::setDimension(const std::vector<unsigned int>& vecDim)
{
	for (int rnk = 0; rnk < vecDim.size(); rnk++)
	{
		Dimensions[rnk] = vecDim[rnk];
	}

	for (int rnk = vecDim.size(); rnk < Rank; rnk++)
	{
		Dimensions[rnk] = 1;
	}
}

template<typename T, unsigned int Rank>
inline unsigned int myTensor<T, Rank>::calcVecsize(const std::vector<unsigned int>& vecDim)
{
	unsigned int retVal = 1;
	for (auto vecElem : vecDim)
		retVal *= vecElem;
	return retVal;
}



