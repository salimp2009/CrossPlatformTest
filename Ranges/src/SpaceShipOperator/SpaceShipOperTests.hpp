#pragma once
#include "RangesHeaders.hpp"

void SpaceShipOper_Test1();

class CompValue
{
private:
	long id{};
public:
	constexpr CompValue(long i) noexcept : id{i} { }

	constexpr bool operator==(const CompValue& rhs) const { return id == rhs.id;  }
	constexpr auto operator<=>(const CompValue& rhs) const = default;
};

