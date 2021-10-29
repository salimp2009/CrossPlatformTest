#pragma once
//#include "RangesHeaders.hpp"

#if defined __GNUG__ || defined _MSVC_VER

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

	auto functList2 = { funcTrue, funcFalse };

	for (const auto& res : functList2 | std::views::filter([](auto&& f) {return f() == false; }))
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

	std::ranges::for_each(RawStrRange, [](auto&& elem) { std::printf("%c ", elem); } );

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

	subrange 

#endif 