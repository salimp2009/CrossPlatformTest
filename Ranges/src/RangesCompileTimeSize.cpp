#include "RangesHeaders.hpp"
#include "RangesCompileTimeSize.hpp"


// DOES NOT COMPILE; check with author!!!
template<typename T, typename...Args>
consteval auto mergeValues(const T& rng, Args&&... args)
{
	auto cmnRng = std::views::common(rng);
	std::vector<std::ranges::range_value_t<T>> tmpVec{ std::ranges::begin(cmnRng), std::ranges::end(cmnRng) };
	(tmpVec.push_back(std::forward<Args>(args)), ...);

	std::ranges::sort(tmpVec);

	constexpr auto maxSize= std::ranges::size(rng) + sizeof...(args);

	std::array<std::ranges::range_value_t<T>, maxSize>arr{};
	std::ranges::copy(tmpVec, arr.begin());
	return arr;
}



void RangesCompileTimeSize()
{
	std::puts("--RangesCompileTimeSize--");
	
	constexpr std::array origArray = { 0, 8, 15, 143,45,3,77 };

	//auto tmp = mergeValues(origArray, 255, -45);
	//std::puts("Merged & returned:");
	//for (auto elem : tmp )
	//{
	//	std::printf("%i ", elem);
	//}
}
