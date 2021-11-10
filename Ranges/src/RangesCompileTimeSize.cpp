#include "RangesHeaders.hpp"
#include "RangesCompileTimeSize.hpp"

template<typename T, typename...Args>
consteval auto mergeValues(T&& rng, Args&&... args)
{
	// TO BE completed
	return std::ranges::range_value_t<T>{};
}



void RangesCompileTimeSize()
{
	std::puts("--RangesCompileTimeSize--");
	
	constexpr std::array origArray = { 0, 8, 15, 143,45,3,77 };

	auto tmp = mergeValues(origArray, 255, -45);
}
