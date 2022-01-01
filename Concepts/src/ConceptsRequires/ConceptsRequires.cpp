#include "ConceptsPCH.hpp"
#include "ConceptRequires.hpp"



void ConceptsRequirest_Test()
{
	std::puts("--ConceptsRequirest_Test--");

	const int val1 = 42;
	const int val2 = 77;
	
	constexpr auto result = maxxValue(val1, val2);
	std::printf("result maxxVal: %i\n", result);
	// Will not compile since the concept has a requirement not to have raw pointers !!
	//maxxValue(&val1, &val2);

	constexpr auto result2 = minnVal(val1, val2);
	std::printf("minnVal: %i\n", result2);
	minnVal(&val1, &val2);

	const int* p1 = &val1;
	const int* p2 = &val2;
	
	std::printf("minVal2: %i \n", minnVal2(p1, p2));

	auto result3 = minnVal3(p1, p2);
	std::printf("minVal3: %i", result3);

	static_assert(std::is_pointer_v<decltype(p1)>);
	static_assert(IsPointer<decltype(p1)>);
	
	constexpr std::array val3 = {"sdad"};
	const auto* p3 = &val3;
	// this wont compile as expected since it does not match requires clause that it has to 3 way comparable !!
	//minnVal3(p1, p3);


}