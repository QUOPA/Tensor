#pragma once

#include "Tensor.h"
#include "TensorException.h"

#include <tuple>
#include <numeric>
#include <vector>
#include <array>
#include <algorithm>

namespace tens 
{

	
template <typename Scalar_, int NumIndices_ , typename FnType>
Tensor<Scalar_, NumIndices_> EWiseCalc(const Tensor<Scalar_, NumIndices_> & a, FnType Fn)
{
	auto it = a.begin();
	auto itEnd = a.end();

	auto vecDims = a.dimensions();
	Tensor<Scalar_, NumIndices_> retTen(vecDims);

	auto retit = retTen.begin();

	for (; it != itEnd; ++it, ++retit)
	{
		*retit = Fn(*it);
	}
	return retTen;
}

template <typename Scalar_, int NumIndices_>
Tensor<Scalar_, NumIndices_> clip(const Tensor<Scalar_, NumIndices_> & a, int cmin, int cmax)
{
	auto it = a.begin();
	auto itEnd = a.end();

	auto vecDims = a.dimensions();
	Tensor<Scalar_, NumIndices_> retTen(vecDims);

	auto retit = retTen.begin();

	for (; it != itEnd; ++it, ++retit)
	{
		*retit = *it > cmax ? cmax : (*it < cmin ? cmin : *it);
	}
	return retTen;
}

template <typename Scalar_, int NumIndices_>
double meansquare(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();

	auto vecDims = a.dimensions();

	double retVal = 0;

	for (; it != itEnd; ++it)
	{
		retVal += (*it) * (*it);
	}
	return retVal;
}

template <typename Scalar_, int NumIndices_>
Scalar_ max_elem(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();

	return *std::max_element(it, itEnd);
}

template <typename Scalar_, int NumIndices_>
IndexType max_idx(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();
	
	return std::max_element(it, itEnd) - it;
}

template <typename Scalar_, int NumIndices_>
std::pair<IndexType, Scalar_> max_idx_elem(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();

	auto maxit = std::max_element(it, itEnd);
	return std::make_pair(maxit - it, *maxit);
}

template <typename Scalar_, int NumIndices_>
Scalar_ min_elem(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();

	return *std::min_element(it, itEnd);
}

template <typename Scalar_, int NumIndices_>
IndexType min_idx(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();

	return std::min_element(it, itEnd) - it;
}

template <typename Scalar_, int NumIndices_>
std::pair<IndexType, Scalar_> min_idx_elem(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();

	auto retit = std::min_element(it, itEnd);
	return std::make_pair(retit - it, *retit);
}


template <typename Scalar_, int NumIndices_>
Scalar_ sum(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();
	return std::accumulate(it, itEnd, 0);
}

template <typename Scalar_, int NumIndices_>
double mean(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();
	return std::accumulate(it, itEnd,0)/a.size();
}

template <typename Scalar_, int NumIndices_>
Scalar_ product(const Tensor<Scalar_, NumIndices_> & a)
{
	auto it = a.begin();
	auto itEnd = a.end();
	return std::accumulate(it, itEnd, 1, std::multiplies<double>() );
}

template <typename Scalar_, int NumIndices_>
Scalar_ find(const Tensor<Scalar_, NumIndices_> & a, const Scalar_ & val)
{
	auto it = a.begin();
	auto itEnd = a.end();
	return *std::find(it, itEnd, val);
}

template <typename Scalar_, int NumIndices_, typename PrediFn>
Scalar_ find_if(const Tensor<Scalar_, NumIndices_> & a, PrediFn Fn)
{
	auto it = a.begin();
	auto itEnd = a.end();
	return *std::find_if(it, itEnd, Fn);
}


// 
// template <typename Scalar_, int NumIndices_>
// Scalar_ minval(const Tensor<Scalar_, NumIndices_> & a)
// {
// 	auto it = a.begin();
// 	auto itEnd = a.end();
// 
// 	Scalar_ retVal = std::numeric_limits<Scalar_>::min();
// 	for (; it != itEnd; ++it)
// 	{
// 		if (*it > retVal)
// 			retVal = *it;
// 	}
// 	return retVal;
// }
// 
// template <typename Scalar_, int NumIndices_>
// IndexType minidx(const Tensor<Scalar_, NumIndices_> & a)
// {
// 	auto it = a.begin();
// 	auto itEnd = a.end();
// 
// 	auto vecDims = a.dimensions();
// 
// 	Scalar_ maxVal_ = std::numeric_limits<Scalar_>::min();
// 	IndexType retIdx = -1;
// 	IndexType idxIter = 0;
// 
// 	for (; it != itEnd; ++it)
// 	{
// 		if (*it > retVal)
// 		{
// 			retVal = *it;
// 			retIdx = idxIter;
// 		}
// 		++idxIter;
// 	}
// 	return retIdx;
// 
// }
// 
// template <typename Scalar_, int NumIndices_>
// std::pair<IndexType, Scalar> minval(const Tensor<Scalar_, NumIndices_> & a)
// {
// 	auto it = a.begin();
// 	auto itEnd = a.end();
// 
// 	auto vecDims = a.dimensions();
// 
// 	Scalar_ maxVal_ = std::numeric_limits<Scalar_>::min();
// 	IndexType retIdx = -1;
// 	IndexType idxIter = 0;
// 
// 	for (; it != itEnd; ++it)
// 	{
// 		if (*it > retVal)
// 		{
// 			retVal = *it;
// 			retIdx = idxIter;
// 		}
// 		++idxIter;
// 	}
// 	return std::make_pair(retIdx, retVal)
// }
// 



// 
// template <typename Scalar_, int NumIndices_>
// Tensor<Scalar_, NumIndices_> clip(const Tensor<Scalar_, NumIndices_> & a)
// {
// 	auto it = a.begin();
// 	auto itEnd = a.end();
// 
// 	auto vecDims = a.dimensions();
// 	Tensor<Scalar_, NumIndices_> retTen(vecDims);
// 
// 	auto retit = retTen.begin();
// 
// 	for (; it != itEnd; ++it, ++retit)
// 	{
// 		*retit = *it > cmax ? cmax : (*it < cmin ? cmin : *it)
// 	}
// 	return retTen;
// }





}
