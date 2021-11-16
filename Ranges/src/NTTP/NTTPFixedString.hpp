#pragma once
#include "RangesHeaders.hpp"

template<typename CharT, std::size_t N>
struct fixedString
{
	CharT data[N];

	constexpr fixedString(const CharT(&str)[N])
	{
		//std::ranges::copy_n(str, N, data);
		std::copy_n(str, N, data);
	}
};


template<fixedString Str>
struct fixedStringContainer
{
	void print() { std::printf("%s", Str.data ); }
};

template<fixedString Str>
struct FormatString
{
	static constexpr auto fmt = Str;

	static constexpr auto numArgs = std::ranges::count(fmt.data, '%');

	// the book version is operator const auto ????? an also & 
	const auto operator*() const { return fmt.data; }
};

void print(auto fmt, auto&&... args)
{
	// if std::forward does not work then use args...
	std::printf(fmt, std::forward<decltype(args)>(args)...);
}