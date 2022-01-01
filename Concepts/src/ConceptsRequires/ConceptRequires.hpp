#include "ConceptsPCH.hpp"

void ConceptsRequirest_Test();

template<typename T>
concept NotRawPointer = ! std::is_pointer_v<T>;

template<typename T>
requires NotRawPointer<T>
constexpr T maxxValue(T a, T b)
{
	return b < a ? a : b;
}

template<typename T>
concept IsPointer = std::is_pointer_v<T>;

template<typename T>
constexpr T minnVal(T a, T b)
{
	return b < a ? b : a;
}

// constraint function
template<typename T>
requires IsPointer<T>
constexpr T minnVal(T a, T b)
{
	return *b < *a ? b : a;
}

// type constraint
template<IsPointer T>
constexpr auto minnVal2(T a, T b)
{
	return *b < *a ? *b : *a;
}template<IsPointer T>

// this does not compile if in header file but compiles in cpp
inline constexpr auto minnVal3(IsPointer auto a, IsPointer auto b)
{
	return *b < *a ? *b : *a;
	// Alternative
	return minnVal(*a, *b);
}

//this compiles ???
constexpr auto minnVal4(std::integral auto a, std::integral auto b)
{
	return minnVal(a, b);
}