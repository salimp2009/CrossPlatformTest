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