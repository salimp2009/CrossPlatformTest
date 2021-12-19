#pragma once
#include "RangesHeaders.hpp"

void SpaceShipOper_Test1();
void CustomSpaceShip_Comparisions();
void ComparisionTypes_Ordering();

class CompValue
{
private:
	long id{};
public:
	constexpr CompValue(long i) noexcept : id{i} { }

	constexpr bool operator==(const CompValue& rhs) const { return id == rhs.id;  }
	constexpr auto operator<=>(const CompValue& rhs) const = default;
};


class Person1
{
private:
	std::string firstName{};
	std::string lastName{};
	int value{};
public:
	constexpr Person1() = default;
	auto operator<=>(const Person1& other) const
	{
		auto cmp1 = firstName <=> other.firstName;
		if (cmp1 != 0)			// if result not equal to zero
		{
			return cmp1;
		}

		auto cmp2 = firstName <=> other.firstName;
		if (cmp2 != 0)			// if result not equal to zero
		{
			return cmp2;
		}

		return value <=> other.value;
	}
};

