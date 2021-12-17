#include "RangesHeaders.hpp"
// Example from Jodi Hagins @CppCon 2021
// struct, tuple of different types and packed ; by sorting and aligning according to the size of given types

template<template<typename> class Orderable, typename ListT>
class SortTypes;

template<template<typename> class Orderable, template<typename...> class List, typename...Ts>
class SortTypes<Orderable, List<Ts...>>
{
	template<typename SeqT> struct Impl;

	template<std::size_t...Is>
	struct Impl<std::index_sequence<Is...>>
	{
		static constexpr std::array<std::size_t, sizeof...(Ts)> indexes = [] 
		{
			using Ord = std::common_type_t<decltype(Orderable<Ts>::value)...>;
			struct Pair { Ord ord; std::size_t ndx; };
			Pair arr[] = { {Orderable<Ts>::value, Is}... };
			std::sort(arr.begin(), arr.end(), [](auto x, auto y) { return x.ord < y.ord; });
			return std::array<std::size_t, sizeof...(Ts)>{arr[Is].ndx...};
		}();
		// Original implementation in presentation; TypeList is a list of types; 
		// since TypeList is not implemented used std::tuple to see if works 
		//using type = List<std::tuple_element_t<indexes[Is], TypeList<Ts...>>...>;
		using type = List<std::tuple_element_t<indexes[Is], std::tuple<Ts...>>...>;
	};
public:
	using type = typename Impl < std::make_index_sequence < sizeof...(Ts)>> ::type;
};

template<typename T>
using Orderable = std::integral_constant<std::size_t, alignof(T)>;

// This causes compile error ; somethng wron in the implementation ?????
// using Sorted = typename SortTypes<Orderable, std::tuple<int, double, unsigned, char>>::type;