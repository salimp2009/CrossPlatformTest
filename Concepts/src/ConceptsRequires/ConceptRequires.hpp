#include "ConceptsPCH.hpp"

void ConceptsRequirest_Test();
void RequirementExpression_Test();
void OverloadResolution_Concepts();

template<typename T>
concept NotRawPointer = ! std::is_pointer_v<T>;

template<typename T>
requires NotRawPointer<T>
constexpr T maxxValue(T a, T b)
{
	return b < a ? a : b;
}

template<typename T>
concept IsPointer =  requires(T p)
{
	*p;
	{p < p}->std::convertible_to<bool>;
	p == nullptr;
};

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
}

// intellisense gives false error squigless
constexpr auto minnVal3(IsPointer auto a, IsPointer auto b) 
requires std::three_way_comparable_with<decltype(*a), decltype(*b)>
{
	return *b < *a ? *b : *a;
	// Alternative
	//return minnVal(*a, *b);
}


constexpr auto minnVal4(std::integral auto a, std::integral auto b)
{
	return minnVal(a, b);
}


template<typename T>
concept IntegerType = std::is_same_v<std::remove_cvref_t<T>, int>;

template<typename T>
concept IntegerCont = std::is_same_v<typename T::value_type, int>;

// Basic usage of auto & constraints(concepts) in function paramaters
// Not ideal example since we bet
void printColl(IntegerCont auto const& coll)
{
	for (IntegerType auto const& elem : coll)
	{
		std::printf("%i ", elem);
	}
	std::puts("");
}

template<typename Cont, typename T>
concept ContainerType = requires(Cont cont, T val)
{
	{cont.push_back(val)};
};

template<typename T1, ContainerType<T1> Cont>
requires std::is_same_v<T1, typename Cont::value_type>
constexpr void add(Cont& coll, const T1& t)
{
	coll.push_back(t);
}