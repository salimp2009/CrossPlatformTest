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
	std::printf("result2 minnVal: %i\n", result2);
	minnVal(&val1, &val2);

}