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


// Sample requires Expressions

template<typename Coll>
concept  SubTypeIsPair = requires {
	typename Coll::value_type::first_type;
	typename Coll::value_type::second_type;
};

template<typename T>
concept AddSubtractSupport = requires (T x, T y)
{
	x + y;
	x - y;
};

// the sub types can be used to validate
template<typename Coll>
concept SubTypeValid = requires (typename Coll::value_type val)
{
	true;
};

template<typename T1, typename T2>
concept Sample1 = requires(T1 val, T2 p)
{
	*p;				// operator* supported for T2
	p[0];			//operator[] has to be supported for int as index
	p->value();		// calling member function value()
	*p > val;		// comparision operator valid between T1 and result operator* (not T2)
	p == nullptr;  // type T2 is comparable with nullptr (the type of nullptr is nullptr_t)

	// *p > val || p == nullptr; // this check only combines the result of both expression ; it does not imply either of those to be supported

};

template<typename T1, typename T2>
concept Sample2 = requires(T1 val, T2 p) { *p > val; } || requires (T2 p) { p == nullptr; };

// this wont work on unique_trs directly because std::equality_comparable_with requires  std::common_reference_with and that requires is_convertible_v<_From, _To>
template<typename T1, typename T2>
concept Sample3 = requires(T1 val, T2 p) { *p > val; } || requires { std::equality_comparable_with<T2, std::nullptr_t>; };

// this is does not imply T to be integral ; only implies std::integral<T> is valid;
template<typename T>
concept IntegralTypeWrong = requires { std::integral<T>; };

// this is OK 
static_assert(IntegralTypeWrong<int>);
// this test should fail for float
static_assert(IntegralTypeWrong<float>);

// this implies T to be integral
template<typename T>
concept IntegralTypeRight = requires { requires std::integral<T>; };

// this implies T to be integral
template<typename T>
concept IntegralTypeRight2 = std::integral<T>;

static_assert(IntegralTypeRight<int>);
static_assert(not IntegralTypeRight<float>);

static_assert(IntegralTypeRight2<int>);
static_assert(not IntegralTypeRight2<float>);
