#pragma once
#pragma once

//#include "NewMat11/newmat.h"
#include "Tensor.h"
#include <vector>
#include <string>
// Version 0.1.0

// namespace ten {
// 
// template<typename T>
// class CDLBatchManager;
// 
// // template<typename T, int Dim>
// // class CDLBatchAccess;
// 
// template<typename T>
// class CDLRowAccess
// {
// public:
// 
// DLTensor4D<T> & operator()(int c) { return *(_ptrTen->operator[](Rowidx) + c); };
// DLTensor4D<T> operator()(int c) const { return  *(_ptrTen->operator[](Rowidx) + c); };
// 
// DLTensor4D<T>& element(int c) { return _ptrTen->element(Rowidx, c); };
// DLTensor4D<T> element(int c) const { return  _ptrTen->element(Rowidx, c); };
// 
// DLTensor4D<T>& operator[] (int c) { return *(_ptrTen->operator[](Rowidx) + c); }
// T operator[] (int c) const { return *(_ptrTen->operator[](Rowidx) + c); }
// 
// void operator=(const DLTensor4D<T> & ten);
// //void operator=(const RowVector & vec);
// 
// void operator=(const T & scal);
// 
// operator DLTensor4D<T>() const { return createTensor(); }
// //operator RowVector() const { return createRowVec(); }
// 
// 
// //int ncols() const { return _ptrTen->Ncols(); }
// //int Ncols() const { return _ptrTen->Ncols(); }
// 
// DLTensor4D<T> createTensor() const;
// //RowVector createRowVec() const;
// //ColumnVector createColVec() const;
// 
// virtual ~CDLRowAccess() {}
// 
// CDLRowAccess(const CDLRowAccess& rhs) :_ptrTen(rhs._ptrTen), Rowidx(rhs.Rowidx) { }
// 
// private:
// 
// CDLRowAccess(DLTensor4D<T> * ten) :_ptrTen(ten){  }
// void setTensorSource(DLTensor4D<T>  * ten) { _ptrTen = ten; }
// 
// DLTensor4D<T> * _ptrTen;
// inline void setRow(int r) const { Rowidx = r; }
// 
// //mutable int Rowidx;
// //friend class CDLBatchAccess<T;
// 
// friend DLTensor4D<T> operator+(const CDLRowAccess<T> & lhs, const CDLRowAccess<T> & rhs);
// friend DLTensor4D<T> operator-(const CDLRowAccess<T> & lhs, const CDLRowAccess<T> & rhs);
// };
// 
// template<typename T>
// DLTensor4D<T> operator+(const CDLRowAccess<T> & lhs, const CDLRowAccess<T> & rhs);
// 
// template<typename T>
// DLTensor4D<T> operator-(const CDLRowAccess<T> & lhs, const CDLRowAccess<T> & rhs);
// 
// 
// template<typename T>
// class CDLBatchAccess
// {
// public:
// 	// notsafe but fast
// 	//T& operator()(int r, int c) { return *(_ptrTen->operator[](idxBegin + r) + c); };
// 	//T operator()(int r, int c) const { return  *(_ptrTen->operator[](idxBegin + r) + c); };
// 
// 	//T& element(int r, int c) { return _ptrTen->element(idxBegin + r, c); };
// 	//T element(int r, int c) const { return  _ptrTen->element(idxBegin + r, c); };
// 
// 	//CTensorRowAccess<T,Dim> & operator[](int r) {	RowIt.setRow(idxBegin + r); return RowIt; }
// 	//CTensorRowAccess<T,Dim> operator[](int r) const {	RowIt.setRow(idxBegin + r); return RowIt; };
// 
// 	//CTensorRowAccess<T,Dim> & row(int r) { RowIt.setRow(idxBegin + r); return RowIt; }
// 	//CTensorRowAccess<T,Dim> row(int r) const { RowIt.setRow(idxBegin + r); return RowIt; }
// 
// 	void operator=(const DLTensor4D<T>  & ten);
// 	void operator=(const T & scal);
// 
// 	// base ECMTensor<T, Dim>  등필요 내용은 추후 
// 	operator DLTensor4D<T>() const { return createTensor(); }
// 
// 	int nRecords() const { return NumRows; 
// 
// 	//int ncols() const { return _ptrTen->Ncols(); }
// 	//int Ncols() const { return _ptrTen->Ncols(); }
// 
// 	DLTensor4D<T>()  createTensor() const;
// 	virtual ~CDLBatchAccess() {}
// 	CDLBatchAccess(const CDLBatchAccess & rhs) : _ptrTen(rhs._ptrTen), RowIt(rhs.RowIt), idxBegin(rhs.idxBegin), NumRows(rhs.NumRows) {}
// 
// 
// 
// private:
// 	CDLBatchAccess(DLTensor4D<T> * ten) :_ptrTen(ten), RowIt(ten) {}
// 	void setDLSource(DLTensor4D<T> * ten) { _ptrTen = ten; RowIt._ptrTen = ten; }
// 
// 	DLTensor4D<T> * _ptrTen;
// 
// 	mutable int idxBegin;
// 	mutable int NumRows;
// 
// 	inline void setBeginEnd(int ibeg, int nRows) const { idxBegin = ibeg, NumRows = nRows; }
// 	//CTensorRowAccess<T, Dim> RowIt;
// 
// 	friend DLTensor4D<T> operator+(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs);
// 	friend DLTensor4D<T> operator-(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs);
// 
// };
// 
// template<typename T>
// DLTensor4D<T> operator+(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs);
// 
// template<typename T>
// DLTensor4D<T> operator-(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs);
// 
// template<typename T>
// class CDLBatchManager
// {
// public:
// 	enum IterStyle {
// 		Ordered = 1,
// 		//Random = 2
// 	};
// 
// 	enum ErrorCatalog
// 	{
// 		GOODSTATUS = 0,
// 		UNKNOWN = -1,
// 		BADBATCHSIZE = 1,
// 		MATSIZEERROR = 2,
// 		MATPTRERROR = 3,
// 	};
// 
// 	bool IdxInRange(int iBIdx);
// 
// 	CDLBatchManager<T>(const CDLBatchManager<T>& rhs);
// 	CDLBatchManager<T>(const DLTensor4D<T>  & ten, int batchsize, IterStyle Stle = Ordered);
// 
// 	ECMTensor<T, Dim>  & getSourceData() { return _Mat; }
// 	ECMTensor<T, Dim>  getSourceData() const { return _Mat; }
// 
// 
// 	bool hasError() const { return static_cast<bool>(ErrorStatus); }
// 	ErrorCatalog whichError() const { return ErrorStatus; }
// 
// 	CDLBatchAccess<T, Dim> & operator[](int i);
// 	CDLBatchAccess<T, Dim> operator[](int i) const;
// 
// 	//CTensorRowAccess<T, Dim> & getRowAccess(int global_idx) { return this->operator[](getBatchByGlobalIdx(global_idx))[getRowIdxByGlobalIdx(global_idx)]; }
// 	//CTensorRowAccess<T, Dim> getRowAccess(int global_idx) const { return this->operator[](getBatchByGlobalIdx(global_idx))[getRowIdxByGlobalIdx(global_idx)]; }
// 
// 	void setMatandBatch(const DLTensor4D<T>  & ten, int batchsize, IterStyle Stle = Ordered);
// 
// 	int getInitBatchSize() const { return BatchSize; }
// 	int getNumBatch() const { return NumBatch; }
// 	int getNRows() const { return NRows; }
// 	int getNCols() const { return NCols; }
// 
// private:
// 
// 	int NumBatch;
// 	int BatchSize;
// 	int LastBatchRows;
// 
// 	int NRows;
// 	int NCols;
// 
// 	int getBatchByGlobalIdx(int GlobIdx) const { return GlobIdx / BatchSize; }
// 	int getRowIdxByGlobalIdx(int GlobIdx) const { return GlobIdx % BatchSize; }
// 	int getRowsbyIdx(int BatIdx) const { return BatIdx == NumBatch - 1 ? LastBatchRows : (BatIdx > NumBatch - 1 ? 0 : BatchSize); }
// 	inline int CurrStartbyIdx(int BatIdx) const { return BatIdx*BatchSize; }
// 	inline int CurrPastofEndbyIdx(int BatIdx) const { return BatIdx*BatchSize + getRowsbyIdx(BatIdx); }
// 
// 	void _initBat(int batchsize, IterStyle Stle);
// 
// 	IterStyle itstyl;
// 	ErrorCatalog ErrorStatus;
// 
// 	CDLBatchAccess<T, Dim> BatIt;
// 	Tensor<T, Dim> _Ten;
// };
// 
// //template<typename T>
// //bool BatchSameSize(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T, Dim> & rhs);
// 
// // template<typename T, int Dim>
// // bool RowSameSize(const CTensorRowAccess<T, Dim>  & lhs, const CTensorRowAccess<T, Dim>  & rhs);
// 
// template<typename T>
// bool CDLBatchManager<T>::IdxInRange(int iBIdx)
// {
// 	if (iBIdx >= NumBatch)
// 		return false;
// 	else
// 		return true;
// }
// 
// template<typename T>
// CDLBatchManager<T>::CDLBatchManager(const CDLBatchManager<T> & rhs)
// 	: _Mat(rhs._Mat)
// 	, BatIt(&_Mat)
// 	, itstyl(rhs.itstyl)
// 	, ErrorStatus(rhs.ErrorStatus)
// 	, NumBatch(rhs.NumBatch)
// 	, BatchSize(rhs.BatchSize)
// 	, LastBatchRows(rhs.LastBatchRows)
// 	, NRows(rhs.NRows)
// 	, NCols(rhs.NCols)
// {
// }
// 
// template<typename T>
// CDLBatchManager<T>::CDLBatchManager(const DLTensor4D<T> & ten, int batchsize, IterStyle Stle)
// 	:_Mat(ten), BatIt(&_Mat)
// {
// 	_initBat(batchsize, Stle);
// }
// 
// template<typename T>
// CDLBatchAccess<T> & CDLBatchManager<T>::operator[](int i)
// {
// 	BatIt.setBeginEnd(CurrStartbyIdx(i), getRowsbyIdx(i));
// 	return BatIt;
// }
// 
// template<typename T>
// CDLBatchAccess<T> CDLBatchManager<T>::operator[](int i) const
// {
// 	BatIt.setBeginEnd(CurrStartbyIdx(i), getRowsbyIdx(i));
// 	return BatIt;
// }
// 
// template<typename T>
// void CDLBatchManager<T>::setMatandBatch(const DLTensor4D<T>  & ten, int batchsize, IterStyle Stle)
// {
// 	_Mat = ten;
// 	BatIt.setTensorSource(&_Mat);
// 	_initBat(batchsize, Stle);
// }
// 
// template<typename T>
// void CDLBatchManager<T>::_initBat(int batchsize, IterStyle Stle)
// {
// 	if (&_Mat != nullptr)
// 	{
// 		NCols = _Mat.Ncols();
// 		NRows = _Mat.Nrows();
// 
// 		if (NRows > 0 && NCols > 0)
// 		{
// 
// 			if (batchsize > 0 && batchsize <= NRows)
// 			{
// 
// 
// 				ErrorStatus = GOODSTATUS;
// 				itstyl = Stle;
// 				BatchSize = batchsize;
// 				NumBatch = NRows / BatchSize + (NRows%BatchSize > 0 ? 1 : 0);
// 				LastBatchRows = NRows % BatchSize > 0 ? NRows % BatchSize : BatchSize;
// 
// 			}
// 			else
// 				ErrorStatus = BADBATCHSIZE;
// 		}
// 		else
// 		{
// 			ErrorStatus = MATSIZEERROR;
// 		}
// 	}
// 	else
// 	{
// 		ErrorStatus = MATPTRERROR;
// 	}
// }
// 
// template<typename T>
// DLTensor4D<T>  CDLBatchAccess<T>::createTensor() const
// {
// 	/*
// 	int NumCols = _ptrTen->Ncols();
// 	ECMTensor<T, Dim>  ret(NumRows, NumCols);
// 	for (int r = 0; r < NumRows; r++)
// 	{
// 	for (int c = 0; c < NumCols; c++)
// 	{
// 	ret[r][c] = *(_ptrTen->operator[](idxBegin + r) + c);
// 	}
// 	}
// 	return ret;
// 	*/
// }
// 
// template<typename T>
// void CDLBatchAccess<T>::operator=(const DLTensor4D<T>  & ten)
// {
// 	/*
// 	int NumCols = _ptrTen->Ncols();
// 	assert(ten.Ncols() == NumCols && ten.Nrows() == NumRows);
// 	for (int r = 0; r < NumRows; r++)
// 	{
// 	for (int c = 0; c < NumCols; c++)
// 	{
// 	*(_ptrTen->operator[](idxBegin + r) + c) = ten[r][c];
// 	}
// 	}
// 	*/
// }
// 
// template<typename T>
// void CDLBatchAccess<T>::operator=(const T & scal)
// {
// 	/*
// 	int NumCols = _ptrTen->Ncols();
// 	for (int r = 0; r < NumRows; r++)
// 	{
// 	for (int c = 0; c < NumCols; c++)
// 	{
// 	*(_ptrTen->operator[](idxBegin + r) + c) = scal;
// 	}
// 	}
// 	*/
// }
// 
// 
// // template<typename T, int Dim>
// // ECMTensor<T, Dim>  CTensorRowAccess<T, Dim>::createTensor() const
// // {
// // 	/*
// // 	int NumCols = _ptrTen->Ncols();
// // 	ECMTensor<T, Dim>  ret(1, NumCols);
// // 	for (int c = 0; c < NumCols; c++)
// // 	{
// // 		ret[0][c] = *(_ptrTen->operator[](Rowidx) + c);
// // 	}
// // 	return ret;
// // 	*/
// // }
// // 
// // /*
// // template<typename T, int Dim>
// // RowVector CTensorRowAccess<T, Dim>::createRowVec() const
// // {
// // 	int NumCols = _ptrTen->Ncols();
// // 	RowVector ret(NumCols);
// // 	for (int c = 0; c < NumCols; c++)
// // 	{
// // 		ret[c] = *(_ptrTen->operator[](Rowidx) + c);
// // 	}
// // 	return ret;
// // }
// // ColumnVector CTensorRowAccess::createColVec() const
// // {
// // 	int NumCols = _ptrTen->Ncols();
// // 	ColumnVector ret(NumCols);
// // 	for (int c = 0; c < NumCols; c++)
// // 	{
// // 		ret[c] = *(_ptrTen->operator[](Rowidx) + c);
// // 	}
// // 	return ret;
// // }
// // 
// // */
// // 
// // template<typename T, int Dim>
// // void CTensorRowAccess<T, Dim>::operator=(const ECMTensor<T, Dim>  & ten)
// // {
// // 	/*
// // 	int NumCols = _ptrTen->Ncols();
// // 	assert(ten.Ncols() == NumCols && ten.Nrows() == 1);
// // 	for (int c = 0; c < NumCols; c++)
// // 	{
// // 		*(_ptrTen->operator[](Rowidx) + c) = ten[0][c];
// // 	}
// // 	*/
// // }
// // 
// // /*
// // void CTensorRowAccess<T, Dim>::operator=(const RowVector & vec)
// // {
// // 	int NumCols = _ptrTen->Ncols();
// // 	assert(vec.Ncols() == NumCols);
// // 	for (int c = 0; c < NumCols; c++)
// // 	{
// // 		*(_ptrTen->operator[](Rowidx) + c) = vec[c];
// // 	}
// // }
// // */
// // 
// // template<typename T, int Dim>
// // void CTensorRowAccess<T, Dim>::operator=(const T & scal)
// // {
// // 	/*
// // 	int NumCols = _ptrTen->Ncols();
// // 	for (int c = 0; c < NumCols; c++)
// // 	{
// // 		*(_ptrTen->operator[](Rowidx) + c) = scal;
// // 	}
// // 	*/
// // }
// // 
// // 
// // template<typename T, int Dim>
// // ECMTensor<T, Dim> operator+ (const CTensorRowAccess<T, Dim> & lhs, const CTensorRowAccess<T, Dim> & rhs)
// // {
// // 	if (!RowSameSize(lhs, rhs))
// // 		throw (Exception("특정 데이터 행에서 열의 크기가 일치하지 않습니다."));
// // 
// // 	int NCols = lhs.Ncols();
// // 	ECMTensor<T, Dim> ret(NCols);
// // 	for (int c = 0; c < NCols; c++)
// // 	{
// // 		ret[c] = lhs(c) + rhs(c);
// // 	}
// // 	return ret;
// // }
// // 
// // template<typename T, int Dim>
// // ECMTensor<T, Dim> operator- (const CTensorRowAccess<T, Dim> & lhs, const CTensorRowAccess<T, Dim> & rhs)
// // {
// // 	if (!RowSameSize(lhs, rhs))
// // 		throw (Exception("특정 데이터 행에서 열의 크기가 일치하지 않습니다."));
// // 
// // 	int NCols = lhs.Ncols();
// // 	ECMTensor<T, Dim> ret(NCols);
// // 	for (int c = 0; c < NCols; c++)
// // 	{
// // 		ret[c] = lhs(c) - rhs(c);
// // 	}
// // 	return ret;
// // }
// 
// template<typename T>
// DLTensor4D<T>  operator+(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs)
// {
// 	if (!BatchSameSize(lhs, rhs))
// 		throw (Exception("배치의 크기가 일치하지 않습니다."));
// 
// 	int NRows = lhs.Nrows();
// 	int NCols = lhs.Ncols();
// 	DLTensor4D<T> ret(NRows, NCols);
// 	for (int r = 0; r < NRows; r++)
// 	{
// 		for (int c = 0; c < NCols; c++)
// 		{
// 			ret[r][c] = lhs(r, c) + rhs(r, c);
// 		}
// 	}
// 	return ret;
// }
// 
// template<typename T>
// DLTensor4D<T>  operator-(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs)
// {
// 	if (!BatchSameSize(lhs, rhs))
// 		throw (Exception("배치의 크기가 일치하지 않습니다."));
// 
// 	int NRows = lhs.Nrows();
// 	int NCols = lhs.Ncols();
// 	DLTensor4D<T>  ret(NRows, NCols);
// 	for (int r = 0; r < NRows; r++)
// 	{
// 		for (int c = 0; c < NCols; c++)
// 		{
// 			ret[r][c] = lhs(r, c) - rhs(r, c);
// 		}
// 	}
// 	return ret;
// }
// 
// template<typename T>
// bool BatchSameSize(const CDLBatchAccess<T> & lhs, const CDLBatchAccess<T> & rhs)
// {
// 	return true;
// 	//return lhs.Ncols() == rhs.Ncols() && lhs.Nrows() == rhs.Nrows();
// }
// 
// // template<typename T, int Dim>
// // bool RowSameSize(const CTensorRowAccess<T, Dim> & lhs, const CTensorRowAccess<T, Dim> & rhs)
// // {
// // 	return true;
// // 	//return lhs.Ncols() == rhs.Ncols();
// // }
// 
// 
// 
// }
// 
// 
// 
