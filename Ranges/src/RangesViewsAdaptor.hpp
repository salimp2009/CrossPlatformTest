#pragma
#include "RangesHeaders.hpp"

#if defined __GNUG__  || defined _MSC_VER && !defined(__clang__)

inline void RangesAdaptors_all()
{
	std::puts("---RangesAdaptors_all---");

	// Excerpts Nicolais Jositos book "c++20 the complete guide - First Edition"
	//"std::views::all() is an adaptor converts any range (that is not already a view) into a view 
	// and handling to deal with elementof range"

	std::vector vec = { 1,2,3,5,6,6,7 };
	std::ranges::iota_view iotaView{ 1, 10 };
	
	// std::views::all() accepts only views or lvalues ; temporary objects wont compilie :) !!!
	auto rangeView1 = std::views::all(vec);
	auto rangeView2 = std::views::all(iotaView);
	auto rangeView3 = std::views::all( std::views::all(vec) );

	// TODO; check if string_view can be converted to a view because (CHECK THIS !!!)currently you cannot use string_view if a view is expected in some cases!
	constexpr std::string_view strView = { "Hello Cmake" };
	
	//views::counted returns a range from string_view
	auto rangeView4 = std::views::counted(strView.data(), strView.size());
	auto rangeView5 = std::views::all(rangeView4);

	//TODO; std::views::all returns a string_view so it may not work if you want pipe it to an adaptor if it expects a std::views (TO BE CHECKED!!!)
	auto rangeView6 = std::views::all(strView);
	auto rangeView7 = std::views::all(rangeView6);

	auto rangeView8 = std::views::counted(rangeView6.data(), rangeView6.size());

	std::puts("passing string view into an adaptor: Only 3 first characters");
	//rangeView type is string_view and accepted by std::views::take() adaptor
	for (auto elem : std::views::take(rangeView6, 3))
	{
		std::printf("%c ", elem);
	}

	std::puts("\nfull characters in string_view");
	for (auto elem : rangeView6)
	{
		std::printf("%c ", elem);
	}

	// piping string_view; TEST
	std::puts("\npiping string_view; TEST");
	for (const auto& elem : strView | std::views::take(std::ssize(strView)-3))
	{
		std::printf("%c", elem);
	}

	std::puts("");
	// const char* not compile with ranges
	//const char* CString = "C-Style String Testing";
	//auto rangeViewCStr1 = std::views::all(CString);
}

inline void Ranges_LazyEval()
{
	std::puts("---Ranges_LazyEval---");

	std::vector vec = { 28, 35, 0, 45, 13 };

	// Always use the args pass in views as copy or const&; even for the predicated
	// However you can pass the view into another functions that may change the values; like in a for loop; or ranges algorithms
	auto vecView = vec 
		| std::views::filter([](auto elem) 
			{ 
					std::printf("filter: %i\n", elem);
					return elem % 2 == 0; 
			})
		| std::views::transform([] (auto elem)
			{
				std::printf("transform: %i \n", elem);
				return -elem;

			});

	for (auto elem : vecView)
	{
		std::printf("%i \n", elem);
	}

	std::puts("Testing if the original vec has changed or not?");

	for (auto elem : vec)
	{
		std::printf("%i ", elem);
	}


	auto pos = std::ranges::find(vecView, 0);

	std::puts("testing if the views changed the original container:");
	for (const auto& val : vec)
	{
		std::printf("%i ", val);
	}

	std::puts("");

	for (auto& elem : vec | std::views::drop(3))
	{
		elem+=155;
	}

	std::puts("testing after changing the original container except the first 3:");
	for (const auto& val : vec)
	{
		std::printf("%i ", val);
	}

	std::puts("");
}

inline void RangesViews_WriteAccess()
{
	std::puts("---RangesViews_WriteAccess---");

	std::vector vec = { 1,4,7,10,13,16,19, 20, 29 };

	// testing passing args in filter view by && then will test by copy
	auto isEven = [](auto&& val) { return val % 2 == 0; };
	
	// creating a view with that predicated return true; if this view is used twice in a function  that 
	// changes the value of the original container then this cached view hold the position begin() iterator from the original vec
	// if that is changed and the predicate does not apply there, the view will not check the begin for the predicate; so it gives false results
	auto evenNumsView = vec | std::views::filter(isEven);

	// modify the view; even number of the container
	for (auto& elem : evenNumsView)
	{
		elem += 1;
	}

	std::puts("checking the original container should be modified as expected!!");
	for (const auto& val : vec)
	{
		std::printf("%i ", val);
	}
	std::puts("");
	// modify the view again; even number of the container
	// suggested way to safely use view the second time use a classic for loop by incrementing and checking predicate or
	// dont cache it
	for (auto& elem : evenNumsView)
	{
		elem += 1;
	}
	// It is better not to cache view if the elemensts of the container is going to be changed 
	// but then you loose performance; Prefer correctness
	
	//for (auto& elem : vec | std::views::filter(isEven))
	//{
	//	elem += 1;
	//}
	
	// second time using the evennumView in a function that changes the element of container
	// may break the predicate and gives false results
	std::puts("checking the original container should be modified as expected or not!!");
	for (const auto& val : vec)
	{
		std::printf("%i ", val);
	}

	std::puts("");
}



#endif