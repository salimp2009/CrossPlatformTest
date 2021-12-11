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
	//static_assert(not std::is_same_v<decltype(fixed_string("x")), decltype(fixed_string("y"))>);

	auto mytuple = "name"_t;
	std::printf("%s, %lu \n", mytuple.data, mytuple.size);
	std::printf("%s, %lu \n", ("Didem"_t).data, ("Didem"_t).size);

	auto fixedStrng1 = fixed_string("name");

	std::string_view val = fixedStrng1;

	std::printf("%s %lu \n" , fixedStrng1.data, fixedStrng1.size);
	std::printf("%s %lu \n" , val.data(), val.size());

}

void NamedTupple_Test2()
{
	std::puts("--Named Tupple-Test2--");
	using namespace std::string_view_literals;
	
	// this fails in the original implementation
	//constexpr auto arg0 = ("name"_ts = 42);
	constexpr auto arg1 = arg<"name", int>{ 42 };
	
	// All of those fail 
	static_assert("name"sv == arg1.name);
	static_assert(42 == arg1.value);


	static_assert("test2"sv == (arg<"test2", int>{42}).name);
	static_assert(42 == (arg<"test2", int>{42}).value);

	[[maybe_unused]] const auto ntp1 = namedtuple<arg<"x", int>, arg<"y", int>>({ .value = 42 }, {.value=55});
	const auto ntp2 = namedtuple("z"_ts = 45, "y1"_ts = 155, ntp1);
	
	// TODO ; this does not compile 
	//static_assert(42 == ntp1["x"_ts]);

	//auto val0 = std::any_cast<int>(ntp1["x"_ts]);
	//std::printf("%i", val0);

	//auto val = ntp1["x"_ts];

	//std::printf("x: %i, y: %i", ntp1["x"_ts], ntp1["y"_ts]);

}