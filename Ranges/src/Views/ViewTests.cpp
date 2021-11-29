#include "RangesHeaders.hpp"
#include "ViewTests.hpp"



void JoinViewTest1()
{
	std::puts("--JoinViewTest1--");
	std::vector vec1{ 1,2,3,4 };
	std::vector vec2{ 0,4, 9,15 };
	std::vector vec3{ 5,4,3,2,1,0 };
	std::array arr1{ vec1, vec2, vec3 };

	// intellisense shows false error; red squigels but it compiles
	for (const auto& elem : std::ranges::join_view(arr1))
	{
		std::printf("%i ", elem);
	}

	std::puts(" ");
	
	int arr2[]{ 1,2,3,4 };
	int arr3[]{ 0,4, 9,15 };
	int arr4[10]{ 5,4,3,2,1,0 };
	std::array<std::ranges::subrange<int*>, 3> coll2{arr2, arr3, arr4};

	for (const auto& elem : std::ranges::join_view(coll2))
	{
		std::printf("%i ", elem);
	}
	//
	std::puts(" ");
}