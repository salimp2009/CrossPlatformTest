#include "RangesHeaders.hpp"
#include "MetaProgramBasics.hpp"
#include "MetaProgLinearSearch.hpp"
#include "MetaProgInHeritance.hpp"
#include "DecltypeAutoUses.hpp"

void MetaProgramming_Test()
{
	std::puts("--MetaProgramming_Test--");
	//std::void_t ; checks if the type is valid and return void otherwise gives 
	static_assert(std::is_same_v<void, std::void_t<>>);
	static_assert(std::is_same_v<void, std::void_t<int>>);
	static_assert(std::is_same_v<void, std::void_t<int, char, double>>);

	static_assert(std::is_same_v<void, std::void_t<int&>>);
	static_assert(std::is_same_v<void, std::void_t<void>>);

	// gives a compiler hard error because it is illegal to refer to void
	//static_assert(std::is_same_v<void, Void_t<void&>>);
	static_assert(std::is_same_v<void, std::void_t<std::add_lvalue_reference_t<void>>>);
	static_assert(std::is_same_v<void, Void_t<std::add_lvalue_reference_t<void>>>);

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
	
	static_assert(not recursive_IsInPack<int, char, char, char, float, std::string, char>{});
	static_assert( recursive_IsInPack<int, char, char, char, float, std::string, std::vector<int>, char, float, int>{});

	constexpr auto val = packArgs(1, 'c', 'c', 333);
	static_assert(val);

	// if you give 255 ; it will be testing 255*2
	constexpr auto val2 = packNArgs<255, false>();
	static_assert(!val2);
	
	constexpr auto val3 = packNArgs<std::numeric_limits<signed char>::max(), true>();
	static_assert(val3);

	std::printf("false case:% i, true case:%i \n", val2, val3);
	std::printf("max size of signed char:%i \n", std::numeric_limits<unsigned char>::max());

	// Examples where std::void_t fails but custom Void_t implementation does not
	// this one uses Void_T which used indirect aliasing
	func<One>();
	func<Two>();

	// this example uses std::void_t and does not compile
	//func2<One>();

	BartFart<int, float> bf1{};
	BartFart<TType, UType> bf2{};

	static_assert(std::is_invocable_v<decltype(blargLamda), int&>);

	static_assert(not std::is_invocable_v<decltype(blargLamda), Bar&>);

}

std::string str1 = "my function";

void MetaProgLinearSearch()
{
	std::puts("--MetaProgLinearSearch--");

	auto prettyFuncName = std::string_view(__PRETTY_FUNCTION__);
	std::printf("__PRETTY_FUNCTION__ = %s \n", prettyFuncName.data());
	std::printf("__FUNCTION__		 = %s \n", __FUNCTION__);

	auto fn1 = []() { return std::string_view{ str1 }; };

	PackImpl< void(*)(int), int(*)(int), void(*)(), std::string_view(*)(), decltype(fn1) > mypack{};
	// this does not give correct result ; need to check but i did not quite like the implementation :)
	auto result = mypack.contains([]() { return std::string_view{ str1 }; });
	printf("IsInPack CompileTimeCheck thru Linear Search: %s \n", (result ? "true" : "false"));

}

void MetaProgInheritanceCheck()
{
	std::puts("--MetaProgInheritanceCheck--");
	
	constexpr auto result = inherit_checkPtr_IsInPack<int, char, float, double, int>{};
	static_assert(result);
	printf("IsInPack CompileTimeCheck thru Inheritance: %s \n", (result ? "true" : "false"));

	constexpr auto result2 = inherit_checkPtr_IsInPack<int, char, float, double, bool>{};
	static_assert(not result2);
	printf("IsInPack CompileTimeCheck thru Inheritance: %s \n", (result2 ? "true" : "false"));

}


void DecltypeAutoUseCases()
{
	std::puts("--DecltypeAutoUseCases--");

	std::string str{ "decltype is tricky" };

	auto&& str2 = std::move(str);

	static_assert(not std::is_same_v<decltype(str2), std::string>);		// expected false
	static_assert(std::is_same_v<decltype(str2), std::string&&>);		// expected true
	static_assert(not std::is_same_v<decltype(str2), std::string&>);	// expected false

	static_assert(std::is_reference_v<decltype(str2)>);					// true
	static_assert(not std::is_lvalue_reference_v<decltype(str2)>);		// false
	static_assert(std::is_rvalue_reference_v<decltype(str2)>);			// true


}
