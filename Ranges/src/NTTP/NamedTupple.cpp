#include "RangesHeaders.hpp"
#include "NamedTupple.hpp"

void NamedTupple_Test()
{
	std::puts("--Named Tupple--");
	using namespace std::string_view_literals;
	// TDD; Test Driven Development ;write the test before implementation
	static_assert(""sv == fixed_string(""));
	static_assert("name"sv == fixed_string("name"));
	static_assert("name"sv == "name"_t);

	// This does fail; tested with the original version;
	// However it succeeds when the rest of implementation is in place especially any and arg classes
	//static_assert(not std::is_same_v<decltype("x"_t), decltype("y"_t)>);

	auto mytuple = "name"_t;
	std::printf("%s, %lu \n", mytuple.data, mytuple.size);
	std::printf("%s, %lu \n", ("Didem"_t).data, ("Didem"_t).size);

	auto fixedStrng1 = fixed_string("name");

	std::string_view val = fixedStrng1;

	std::printf("%s %lu \n" , fixedStrng1.data, fixedStrng1.size);
	std::printf("%s %lu \n" , val.data(), val.size());

}