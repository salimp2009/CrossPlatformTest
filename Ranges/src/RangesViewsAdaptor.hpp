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

	// TODO; check if string_view can be converted to a view because (CHECK THIS !!!)currently you cannot use string_view if a view is expected !
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



}
#endif