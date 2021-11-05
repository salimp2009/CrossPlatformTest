#pragma
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


