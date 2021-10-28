#pragma once
#include "RangesHeaders.hpp"

bool funcTrue()
{
	return true;
}

bool funcFalse()
{
	return false;
}

inline void RangesSort_Strings()
{
	std::puts("---RangesSort_Strings---");

	std::vector<std::string> coll{ "Rio", "Istanbul", "New York", "Berlin"};

	std::ranges::sort(coll);

	std::puts("After sorting!");
	for (const auto& city : coll)
	{
		std::printf("%s ", city.c_str());
	}
	std::ranges::sort(coll[1]);

	std::puts("Sort only the characters in 1st element");
	std::printf("%s \n", coll[1].c_str());
	std::puts("");

	
	 auto anyFailure = std::ranges::any_of(std::initializer_list{ funcTrue, funcFalse }, [](auto&& f) {return f()==false; });
	if (anyFailure)
	{
		printf("Failure!!!\n");
	}

	// Just tring random silly things :)
	constexpr auto functList = std::array{ funcTrue, funcFalse };
	// Does not compile : if we pass the initializer directly into list 
	for (auto res : functList | std::views::filter([](auto&& f) {return f() == false; }))
	{
		if (anyFailure)
		{
			printf("Failure!!!\n");
		}
	}
}