#pragma once
#include "RangesHeaders.hpp"

void SpaceShipOper_Test1();
void CustomSpaceShip_Comparisions();
void ComparisionTypes_Ordering();
void SpaceShipDefaulted_Inheritance();
void SpaceShipBug_ImplicitConversion();

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


class Person2
{
private:
	std::string Name{};
	double ID{};
public:
	//if auto is used as the return type of then it wont compile since one returns partial the other partial
	// if there is a weaker return type chose the return type as the weakest since strong ordering covers all 
	std::partial_ordering operator<=>(const Person2& other) const
	{
		auto cmp1 = Name <=> other.Name;
		if (cmp1 != 0) { return cmp1;}   // returns strong_ordering
		return ID <=> other.ID;			 // returns weak_ordering ; 
	}
};

class Person3
{
private:
	std::string Name{};
	double ID{};
public:
	//if auto is used as the return type of then it wont compile since one returns partial the other partial
	// if there is a weaker return type chose the return type as the weakest since strong ordering covers all 
	auto operator<=>(const Person3& other) const ->std::common_comparison_category_t<decltype(Name <=> other.Name), decltype(ID <=> other.ID)>
	{
		auto cmp1 = Name <=> other.Name;
		if (cmp1 != 0) { return cmp1; }   // returns strong_ordering
		return ID <=> other.ID;			 // returns weak_ordering ; 
	}
};

struct Coord
{
	double x{};
	double y{};
	double z{};
	constexpr auto operator<=>(const Coord& other) const = default;
};

struct ABase
{
	bool operator==(const ABase&) const { std::puts("Equal");  return false; }
	bool operator<(const ABase&) const { std::puts("Less"); return true; }
};

struct ADerived : public ABase
{
	// compiler calls base class == operator if true it is done if not calls < base operator
	// auto cannot be used since the compiler cannot deduce the type
	 std::strong_ordering operator<=>(const ADerived&) const = default;
};

struct ADerived2 : public ABase
{
	// compiler calls base class == operator if true it is done if not calls < base operator
	// auto cannot be used since the compiler cannot deduce the type
	std::partial_ordering operator<=>(const ADerived2&) const = default;
};

// Will not compile since auto is used base class cannot deduce the ordering; see cpp file for the test case !!
struct ADerived3 : public ABase
{
	// compiler calls base class == operator if true it is done if not calls < base operator
	// auto cannot be used since the compiler cannot deduce the type
	auto operator<=>(const ADerived3&) const = default;
};

class MyTypee
{
private:
	int value;
public:
	// implicit constructor
	 MyTypee(int i):value{i} {}

	bool operator==(const MyTypee& other) const { return value == other.value; }

};










