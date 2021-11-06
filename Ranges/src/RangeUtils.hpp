#pragma once
#include "RangesHeaders.hpp"

struct Book
{
	std::string title;
	std::string isbn;
};


inline bool funcTrue()
{
	return true;
}

inline bool funcFalse()
{
	return false;
}

struct NullTerm
{
	auto operator==(auto pos) const
	{
		return *pos == '\0';
	}
};

template<auto EndVal>
struct EndValue
{
	bool operator==(auto pos) const
	{
		return *pos == EndVal;
	}
};

template<std::ranges::input_range Range>
constexpr std::ranges::range_value_t<Range> maxValue(Range&& rg)
{
	if (std::ranges::empty(rg))
	{
		return std::ranges::range_value_t<Range>{};
		// better to do;
		// return {};
	}

	auto pos = std::ranges::begin(rg);
	auto max = *pos;
	while (++pos != std::ranges::end(rg))
	{
		if (*pos > max)
		{
			max = *pos;
		}
	}
	return max;
}


