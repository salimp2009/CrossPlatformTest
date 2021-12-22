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
	std::vector<Coord> points = { 
		{.x = 20.4, .y = 5.45, .z = -15.25}, 
		{.x = 45.4, .y = 155.45, .z = 15.25}, 
		{.x = 24.4, .y = 145.45, .z = 35.25},
		{.x = 16.4, .y = 25.45, .z = 25.25}
	};

	std::ranges::sort(points/*, {}, &Coord::x*/);

	for (auto& elem : points)
	{
		std::printf("x: %f, y: %f, z: %f \n", elem.x, elem.y, elem.z);
	}

	std::puts("");

}

void SpaceShipDefaulted_Inheritance()
{
	std::puts("--SpaceShipDefaulted_Inheritance--");
	ADerived ad1;
	ADerived ad2;
	ad1 > ad2 ;
}
