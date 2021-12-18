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


}
