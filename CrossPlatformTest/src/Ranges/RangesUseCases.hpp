#pragma once
#include "RangesHeaders.hpp"


#if defined __GNUG__  || defined _MSC_VER && !defined(__clang__)

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


	auto functList0 = { funcTrue, funcFalse };
	auto anyFailure = std::ranges::any_of(functList0, [](auto&& f) {return f()==false; });
	if (anyFailure)
	{
		printf("Failure!!!\n");
	}

	// Just tring random silly things :)
	constexpr auto functList = std::array{ funcTrue, funcFalse };
	// Does not compile : if we pass the initializer directly into list 
	for (auto res : functList | std::views::filter([](auto f) {return f() == false; }))
	{
		if (anyFailure)
		{
			printf("Failure!!!\n");
		}
	}

	auto functList2 = { funcTrue, funcFalse };

	for (const auto& res : functList2 | std::views::filter([](auto f) {return f() == false; }))
	{
		if (anyFailure)
		{
			printf("Failure!!!\n");
		}
	}
}

inline void RangesSentinels_NullTermin()
{
	std::puts("---RangesSentinels_NullTermin---");

	const char* rawString = "watching CppCon2021";

	std::ranges::for_each(rawString, NullTerm{}, [](auto elem) {std::printf("%c ", elem); });
}

inline void RangesSubRanges_Sentinels()
{
	std::puts("---RangesSubRanges_Sentinels---");
	
	const char* rawString2 = "Hello my friend Demir...!";

	auto RawStrRange = std::ranges::subrange(rawString2, NullTerm{});

	std::ranges::for_each(RawStrRange, [](auto elem) { std::printf("%c ", elem); } );

	std::puts("");
	for (auto c : RawStrRange)
	{
		std::printf("%c ", c);
	}

	std::puts("");
}

inline void RangesSentinels_EndValue()
{
	std::puts("---RangesSentinels_EndValue---");

	std::vector nums = { 50, 415, 10, -3, -1 }; 

	// Note begin() iterator needs to be first ofr STL containers; in the previous exam we used a C-String( const char*) which is the beginning of the string!!
	std::ranges::subrange rangeInt{ nums.begin(), EndValue<10>{} };
	
	
	for (auto elem : rangeInt)
	{
		std::printf("%d ", elem);
	}
	std::puts("");
}


inline void Ranges_BeginCount()
{
	std::puts("---Ranges_BeginCount---");

	const std::vector<int> nums = { 1,2,3,4,5,6,7,8,9};

	// this gives the position of required value in the container
	auto posFive = std::ranges::find(nums, 5);

	int countValue = 3;

	//check if (current position + count value) is not greater then container.end()
	// if the countValue + currentPos > container.end() then it is UB because you are accessing beyond the end of container 
	// if count = 0 then the range will be empty
	// Note: distance check can be EXPENSIVE if the container does not have random access iterator
	if (std::ranges::distance(posFive, nums.end()) >= countValue)
	{
		for (auto value : std::views::counted(posFive, countValue))
		{
			std::printf("%i ", value);
		}
	}

	std::puts("");
}


inline void Ranges_Projections()
{
	std::puts("---Ranges_Projections---");
	std::vector<int> nums = { 25, 49, 0, -1, 125, 15, 17};

	std::puts("");
	std::ranges::sort(nums, std::less{}, [](auto val) { return std::abs(val); });
	for (const auto& val : nums)
	{
		std::printf("%i ", val);
	}

	std::puts("");

}

#endif 