#pragma once
#include "RangesHeaders.hpp"

template<typename CharT, std::size_t N>
struct fixedString
{
	CharT data[N]{};

	constexpr fixedString(const CharT(&str)[N])
	{
		std::copy_n(str, N, data);
	}
};


template<fixedString Str>
struct FormatString
{
	static constexpr auto fmt = Str;

	static constexpr auto numArgs = std::ranges::count(fmt.data, '%');

	// this is a conversion operator overload; e.g. operator int() {}
	//  see https://en.cppreference.com/w/cpp/language/cast_operator
	operator const auto*() const { return fmt.data; }
};

template<fixedString Str>
constexpr auto operator""_fs()
{
	return FormatString<Str>{};
}

template<typename T, typename U>
constexpr bool plainSame_v = std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

// Added this to test if using Concept is better probably not much better because each case is different for the match function
template<typename T, typename U>
concept AsPlainSafe = plainSame_v<T, U> && plainSame_v<U, T>;

template<typename T>
constexpr static bool match(const char c)
{
	switch (c)
	{
		case 'd': [[fallthrough]];
		case 'i': return plainSame_v<int, T>;
		case 'c': return plainSame_v<char, T>;
		case 'e': [[fallthrough]];
		case 'a': [[fallthrough]];
		case 'g': [[fallthrough]];
		case 'f': return plainSame_v<double, T>;
		case 'p': return std::is_pointer_v<T>;
		case 'x': [[fallthrough]];
		case 'o': return plainSame_v<unsigned, T>;
		case 's': return (plainSame_v<char, std::remove_all_extents_t<T>> && std::is_array_v<T>)			// std::remove_all_extents_t ; gives the value removing all the array info
					  || (plainSame_v<char*, std::remove_all_extents_t<T>> && std::is_pointer_v<T>);
	}
	return false;
}


template<int I, typename CharT>
constexpr auto get(const std::span<const CharT>& str)
{
	auto start	= std::begin(str);
	auto end	= std::end(str);

	// find the position of identfier after each %
	// I is an index sequence to go thru each identifier one by one
	// once the identifier is found return the value at position to IsMatching function to be checked if matches the argument type
	for (int i = 0; i <= I; ++i)
	{
		start = std::ranges::find(start, end, '%');
		++start;
	}
	return *start;
}

template<typename CharT, typename... Args>
constexpr bool IsMatching(std::span<const CharT> str)
{
	return[&]<std::size_t... I>(std::index_sequence<I...>)
	{
		return ((match<Args>(get<I>(str))) && ...);
	}(std::make_index_sequence<sizeof...(Args)>{});
}

template<typename... Ts>
void print(auto fmt, const Ts&... args)
{
	// if std::forward does not work then use args...

	static_assert(fmt.numArgs == sizeof...(Ts), "Too many Arguments!");
	
	static_assert(IsMatching<std::decay_t<decltype(fmt.fmt.data[0])>, Ts...>(fmt.fmt.data), "Data dont match Identifiers!");

	std::printf(fmt, args...);
}


// this will for special cases and runtime only
void print(char* str, const auto&... args)
{
	std::printf(str, args...);
}

// Tis Overload is for the case when user forgets to use the _fs literal ""_fs; 
// it will be always with a nicer error message
template<typename...>
constexpr bool always_false_v = false;

template<typename...Ts>
void print(const char* str, const Ts&... args)
{
	static_assert(always_false_v<Ts...>, "Please Use _fs!");
}

// this maybe be deleted; Used for testing the fixedString works as a template parameter (NTTP)
template<fixedString Str>
struct fixedStringContainer
{
	void print() { std::printf("%s", Str.data); }
};