#include "RangesHeaders.hpp"
#include "SpaceShipOperTests.hpp"

void SpaceShipOper_Test1()
{
	std::puts("--SpaceShipOper_Test1--");

	constexpr CompValue compA{ 20 };
	constexpr CompValue compB{ 30 };
	static_assert(not (compA == compB));
	static_assert(compA <= compB);
	static_assert(not (compA > compB));
	static_assert(((compA <=> compB) == std::strong_ordering::less));
}

void ComparisionTypes_Ordering()
{
	std::puts("--ComparisionTypes_Ordering--");

	constexpr int x = 45;
	constexpr int y = 17;

	static_assert(((x <=> y)== std::strong_ordering::greater));
	static_assert(((x <=> 45.0)== std::partial_ordering::equivalent));
	static_assert(((&x<=>&x)== std::strong_ordering::equal));
	
	// Comparision with <=> operator is not supported !!
	//static_assert(((&x<=>nullptr)== std::strong_ordering::equal));


	static_assert(not ((x <=> y) == std::partial_ordering::equivalent));

	
	// this is always OK; 
	if (x <=> y == std::partial_ordering::equivalent) 
	{ };

}

void CustomSpaceShip_Comparisions()
{
	std::puts("--CustomSpaceShip_Comparisions--");

}