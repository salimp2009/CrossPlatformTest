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

	// gives a compiler error if the minnVal3() is defined in a seperate header because cannot deduce the types ??
	// if minnVal3() is defined in the same cpp file it is OK
	//auto result3 = minnVal3(p1, p2);
	//std::printf("minVal3: %i", result3);

	minnVal4(5, 45);

}