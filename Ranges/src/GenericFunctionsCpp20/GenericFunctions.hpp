#include "RangesHeaders.hpp"

void ConceptAuto_inFunctionParams();


template<typename T>
concept IntegerType = std::is_same_v<std::remove_cvref_t<T>, int>;

template<typename T>
concept IntegerCont = std::is_same_v<typename T::value_type, int>;

// Basic usage of auto & constraints(concepts) in function paramaters
// Not ideal example since we bet
void printColl(IntegerCont auto const & coll)
{
	for (IntegerType auto const& elem: coll)
	{
		std::printf("%i ", elem);
	}
	std::puts("");
}