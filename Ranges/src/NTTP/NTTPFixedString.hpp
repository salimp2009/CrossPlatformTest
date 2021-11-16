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

template<typename... Ts>
void print(auto fmt, const Ts&... args)
{
	// if std::forward does not work then use args...

	static_assert(fmt.numArgs == sizeof...(Ts));
	std::printf(fmt, args...);
}

// this will be deleted
template<fixedString Str>
struct fixedStringContainer
{
	void print() { std::printf("%s", Str.data); }
};