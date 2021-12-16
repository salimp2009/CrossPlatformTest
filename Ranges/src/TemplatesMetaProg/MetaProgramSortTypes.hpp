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
			Ord arr[] = { {Orderable<Ts>::value, Is}... };
			std::ranges::sort(arr, {}, &Pair::ord);
			return std::array<std::size_t, sizeof...(Ts)>{arr[Is].ndx...};
		}();
		// Original implementation in presentation; TypeList is a list of types; 
		// since TypeList is not implemented used std::tuple to see if works 
		//using type = List<std::tuple_element_t<indexes[Is], TypeList<Ts...>>...>;
		using type = List<std::tuple_element_t<indexes[Is], std::tuple<Ts...>>...>;
	};
public:
	using type = typename Impl<std::make_index_sequence<sizeof...(Ts)>>::type;
};
