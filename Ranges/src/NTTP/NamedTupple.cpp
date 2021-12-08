#include "RangesHeaders.hpp"
#include "NamedTupple.hpp"

void NamedTupple_Test()
{
	std::puts("--Named Tupple--");

	// TDD; Test Driven Development ;write the test before implementation
	//static_assert(""sv == fixed_string(""));
	//static_assert("name"sv == fixed_string("name"));

	auto fixedStrng1 = fixed_string("name");

	std::string_view val = fixedStrng1;

	std::printf("%s %lu \n" , fixedStrng1.data, fixedStrng1.size);
	std::printf("%s %lu \n" , val.data(), val.size());
}