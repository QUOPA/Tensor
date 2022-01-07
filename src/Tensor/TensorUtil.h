#pragma once

#include <iostream>
//#include <algorithm>
#include <vector>
#include "Tensor.h"

namespace tens{


template<typename Scalar_>
Tensor<Scalar_, 4> makeDLTensorFromData(Scalar_ * ptrdata, IndexType _B, IndexType _D = 1, IndexType _H = 1, IndexType _W = 1);

template<typename Derived, typename Scalar_, int NumIndices_>
std::ostream& operator << (std::ostream& os, const TensorBaseReadOnly<Derived, Scalar_, NumIndices_>& ten)
{
	return operator<<(os, static_cast<Derived>(ten.derived()).eval() );
}

template<typename Scalar_, int NumInd_>
void printDimensions(const Eigen::Tensor<Scalar_, NumInd_>& ten)
{
	for (int i = 0; i < ten.rank(); i++)
	{
		std::cout << ten.dimension(i);
		if (i != ten.rank() - 1)
			std::cout << ", ";
	}
	std::cout << endl;
}

template<typename Derived ,typename Scalar_, int NumIndices_>
void printDimensions(const TensorBaseReadOnly<Scalar_, Derived, NumIndices_>& ten)
{
	for (int i = 0; i < ten.derived().rank(); i++)
	{
		std::cout << ten.derived().dim(i);
		if (i != ten.derived().rank() - 1)
			std::cout << ", ";
	}
	std::cout << endl;
}





// template<typename Scalar_, int Dims>
// void printTensor(const Tensor<Scalar_, Dims> & ten)
// {
// 	printDimensions(ten);
// 	std::vector<IndexType> momoVec;
// 	printTensor(ten, momoVec);
// }
// 
// template<typename Scalar_, int Dims>
// void printTensor(const Tensor<Scalar_, Dims> & ten, std::vector<IndexType> & DimMemo)
// {
// 	for (int j = 0; j < ten.dim(0); j++)
// 	{
// 		DimMemo.push_back(j);
// 		Tensor<Scalar_, Dims-1> tmpDLTen = ten.chip<0>(j);
// 		printTensor(tmpDLTen, DimMemo);
// 		DimMemo.pop_back();
// 	}
// 	std::cout << std::endl;
// }
// 
// 
// template<typename Scalar_>
// void printTensor(const Tensor<Scalar_, 2>& ten, std::vector<int> & DimMemo)
// {
// 
// 	for (int i = 0; i < DimMemo.size(); i++)
// 	{
// 		if (i == 0)
// 			std::cout << "<";
// 		else
// 			std::cout << ",";
// 		std::cout << DimMemo[i];
// 	}
// 	if (DimMemo.size() == 0)
// 	{
// 		std::cout << "<:,:>" << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << ",:,:>" << std::endl;
// 	}
// 	std::cout << ten << std::endl;
// 
// };
// 
// 
// template<typename Scalar_>
// void printTensor(const Tensor<Scalar_, 1>& ten, std::vector<int> & DimMemo)
// {
// 	std::cout << "<:>" << std::endl;
// 	std::cout << ten << std::endl;
// };


template<typename Scalar_>
Tensor<Scalar_ , 4> makeDLTensorFromData(Scalar_ * ptrdata, IndexType _B, IndexType _D, IndexType _H, IndexType _W)
{
	return Tensor<Scalar_  , 4 >(Eigen::Tensor<Scalar_, 4>(Eigen::TensorMap<Eigen::Tensor<Scalar_, 4>>(ptrdata, _B, _D, _H,_W)));
}



template<typename Scalar_>
Tensor< Scalar_, 4> makeDLTensorFromData(Scalar_ * ptrdata, std::vector<IndexType> DimVec)
{
	int Dim = DimVec.size();
	if (Dim < 1 || Dim > 4)
		throw tensor_rank_error("fail to create DLtensor : vector dimension input should have size 4");
	
	for (int i = Dim; i <  4 ; i++)
	{
		DimVec.push_back(1);
	}

	return Tensor<Scalar_, 4>(Eigen::Tensor<Scalar_, 4>(Eigen::TensorMap<Eigen::Tensor<Scalar_, 4>>(ptrdata, DimVec[0], DimVec[1], DimVec[2], DimVec[3])));
}


//DLTensor4D makeDLTensor()

}
