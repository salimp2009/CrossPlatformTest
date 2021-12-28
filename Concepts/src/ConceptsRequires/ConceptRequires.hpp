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

template<typename T>
requires IsPointer<T>
constexpr T minnVal(T a, T b)
{
	return *b < *a ? b : a;
}