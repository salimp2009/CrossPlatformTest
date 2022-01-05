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

// version using concepts & if constexpr to support both insert and pushback
template<typename T, typename Coll>
requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
void addValue4(Coll& cont, T&& value)
{
	if constexpr (As_SupportPushBack<Coll>)
	{
		cont.push_back(value);
	}
	else
	{
		cont.insert(value);
	}
}


// concept of container that support both push_back and insert 
template<typename Coll>
concept PushBackContainer = SupportsPushBack<Coll> && requires(Coll cont)
{
	cont.insert(cont.end(), std::declval<typename Coll::value_type>());
};

// concept of container that supports insert only; sets 
template<typename Coll>
concept InsertContainer = requires(Coll cont)
{
	cont.insert(std::declval<typename Coll::value_type>());
};

// constraint the function to accept a range; insert single or multiple values
template<PushBackContainer Coll, std::ranges::input_range T>
requires ConvertsWithoutNarrowing<std::ranges::range_value_t<T>, typename Coll::value_type>
void addMultiValues(Coll& cont, T&& range)
{
	cont.insert(cont.end(), std::ranges::begin(range), std::ranges::end(range));
}

template<InsertContainer Coll, std::ranges::input_range T>
requires ConvertsWithoutNarrowing<std::ranges::range_value_t<T>, typename Coll::value_type>
void addMultiValues(Coll& cont, T&& range)
{
	cont.insert(std::ranges::begin(range), std::ranges::end(range));
}








