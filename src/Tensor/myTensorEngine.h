#pragma once

template< typename TenType >
TenType myTensorAdd(const TenType& lhs, const TenType& rhs);

template< typename TenType >
TenType myTensorAdd(TenType && lhs, const TenType& rhs);

template< typename TenType >
TenType myTensorAdd(const TenType& lhs, TenType && rhs);

template< typename TenType >
TenType myTensorSubtract(const TenType& lhs, const TenType& rhs);

template< typename TenType >
TenType myTensorSubtract(TenType&& lhs, const TenType& rhs);

template< typename TenType >
TenType myTensorSubtract(const TenType& lhs, TenType&& rhs);

template<typename TenType>
inline TenType myTensorAdd(const TenType& lhs, const TenType& rhs)
{

	return TenType();
}

template<typename TenType>
inline TenType myTensorAdd(TenType&& lhs, const TenType& rhs)
{
	return TenType();
}

template<typename TenType>
inline TenType myTensorAdd(const TenType& lhs, TenType&& rhs)
{
	return TenType();
}

template<typename TenType>
inline TenType myTensorSubtract(const TenType& lhs, const TenType& rhs)
{
	return TenType();
}

template<typename TenType>
inline TenType myTensorSubtract(TenType&& lhs, const TenType& rhs)
{
	return TenType();
}

template<typename TenType>
inline TenType myTensorSubtract(const TenType& lhs, TenType&& rhs)
{
	return TenType();
}
