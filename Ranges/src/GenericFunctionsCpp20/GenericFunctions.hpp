#include "RangesHeaders.hpp"

void ConceptAuto_inFunctionParams();
void Templates_inLambdas();


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


template<typename T, int Nums>
constexpr auto primeNum2 = []()
{
	std::array<T, Nums> primes{};
	// TODO; primes num calcs to be implemented ; compile time....
	
	return primes;
};