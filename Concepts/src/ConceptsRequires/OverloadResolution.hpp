#include "ConceptsPCH.hpp"
#include <experimental/type_traits>

//template<typename T>



// the signatures of the overloaded function should match
// otherwise the more constrained version for floating point will not be selected
template<std::floating_point T, ContainerType<T> Coll>
void addValue(Coll& cont, T value)
{
	cont.push_back(value);
}

// if the function signatures needs to be different than the T should have contraint Not to Have Floating Point
template<typename T, ContainerType<T> Coll>
requires (!std::floating_point<T>)
void addValue(Coll& cont, T&& value)
{
	cont.push_back(std::forward<T>(value));
}


// concept for allowing implicit type conversion without Narrowing

template<typename From, typename To>
concept ConvertsWithoutNarrowing = std::convertible_to<From, To> && requires(From && x) 
{
	{std::type_identity_t<To[]>{std::forward<From>(x)}} -> std::same_as<To[1]>;
};


template<typename T, ContainerType<T> Coll>
requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
void addValue2(Coll& cont, T&& value)
{
	cont.push_back(std::forward<T>(value));
}

// Alternative supporting functions / variable to be able support push_back and insert for different type of containers
template<typename T>
constexpr bool SupportsPushBack = requires(T coll) { coll.push_back(std::declval<typename T::value_type>()); };

template<typename T>
concept As_SupportPushBack = requires(T coll) 
{ 
	coll.push_back(std::declval<typename T::value_type>());
};

// version to support both insert and pushback
template<typename T, typename Coll>
requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
void addValue3(Coll& cont, T&& value)
{
	if constexpr (requires {cont.push_back(value); })
	{
		cont.push_back(value);
	}
	else
	{
		cont.insert(value);
	}
}






