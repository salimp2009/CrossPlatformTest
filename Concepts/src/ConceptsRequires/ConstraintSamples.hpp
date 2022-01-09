#include "ConceptsPCH.hpp"


// try to avoid ad-hoc constraint; use concepts 
// order of constraints dont matter

template<typename T>
requires (sizeof(T) > 4) 
		&& requires { typename T::value_type; }
		&& std::contiguous_iterator<typename T::iterator>
void SampleAdHoc(T val)
{
	std::puts("SampleAdHoc Function 1");
}

template<typename T, std::size_t Sz>
requires (Sz>0)
constexpr void ArraySizeCheck()
{
	std::puts("ArraySizeCheck");
}


template<typename T>
concept IsIntegral = std::integral<T>;

template<typename T>
struct CustomType { using type = T; };

template<typename T>
struct CustomTypeDerived : CustomType<T> {};

static_assert(IsIntegral<CustomType<int>::type>);
static_assert(IsIntegral<CustomTypeDerived<int>::type>);

// if direct T* is used it is deduced as reference but decltype(*std::declval<T>()) gives a pointer to type or object
template<typename T>
concept IsPointerToIntegral = std::integral<std::remove_cvref_t<decltype(*std::declval<T>())>>;

static_assert(IsPointerToIntegral<int*>);
static_assert(not std::integral<std::optional<int>>);
static_assert(IsPointerToIntegral<std::optional<int>>);






