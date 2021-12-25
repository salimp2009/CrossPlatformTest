#include "RangesHeaders.hpp"
#include "GenericFunctions.hpp"


void ConceptAuto_inFunctionParams()
{
	std::puts("--ConceptAuto_inFunctionParams--");
	std::vector vec1 = { 1,2,35,4,54,25 };
	printColl(vec1);

	std::array arr1 = { 45.6, 24.67, 78.7 };
	// will not compile because although auto is used for function paramter type we constrained to except int only !!
	//printColl(arr1);
	
	std::array arr2 = { 25,65,85,45};
	printColl(arr2);

	std::array arr3 = { 'C', 'C', 'F'};
	// will not compile because although auto is used for function paramter type we constrained to except int only !!
	//printColl(arr3);
}