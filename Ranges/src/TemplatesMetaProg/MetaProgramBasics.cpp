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



}