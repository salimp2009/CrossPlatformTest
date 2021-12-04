#include "RangesHeaders.hpp"
#include "MetaProgramBasics.hpp"


void MetaProgramming_Test()
{
	std::puts("--MetaProgramming_Test--");
	//std::void_t ; checks if the type is valid and return void otherwise gives 
	static_assert(std::is_same_v<void, std::void_t<>>);
	static_assert(std::is_same_v<void, std::void_t<int>>);
	static_assert(std::is_same_v<void, std::void_t<int, char, double>>);


	static_assert(std::is_same_v<void, std::void_t<int&>>);
	static_assert(std::is_same_v<void, std::void_t<void>>);

	// gives a compiler hard error but it should not; it should only fail the static assert
	//static_assert(std::is_same_v<void, std::void_t<void&>>);

	typeA<int> myintA;
	static_assert(std::is_same_v<A<int>, decltype(myintA)>);
	auto result = std::is_same_v<A<int>, decltype(myintA)>;
	std::printf("%s \n", (result ? "true":"false"));

	typeA<int, float, double> mymultitypeA{};
	result = std::is_same_v<A<int, float, double>, decltype(mymultitypeA)>;
	std::printf("%s \n", (result ? "true" : "false"));

	static_assert(std::is_same_v<int&, typename Add_Lvalue_reference<int>::type>);
	static_assert(std::is_same_v<void, typename Add_Lvalue_reference<void>::type>);
	
	static_assert(std::is_same_v<void, typename std::add_lvalue_reference_t<void>>);

}