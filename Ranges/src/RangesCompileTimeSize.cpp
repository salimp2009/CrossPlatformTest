#include "RangesHeaders.hpp"
#include "RangesCompileTimeSize.hpp"

#if !defined (__GNUG__)  || defined _MSC_VER && !defined(__clang__)
// COMPILEs with MSVC only
template<typename T, typename...Args>
consteval auto mergeValues(T rng, Args&&... args)
{
	//auto cmnRng = std::views::common(rng);
	std::vector<std::ranges::range_value_t<T>> tmpVec{ std::ranges::begin(rng), std::ranges::end(rng) };
	(..., tmpVec.push_back(std::forward<Args>(args)));

	std::ranges::sort(tmpVec);

	constexpr auto maxSz = rng.size() + sizeof...(args);     // OK
	std::array<std::ranges::range_value_t<T>, maxSz> arr{}; // OK
	auto res = std::ranges::unique_copy(tmpVec, arr.begin());
	return std::pair{ arr, res.out - arr.begin() };
}

#endif

void RangesCompileTimeSize()
{
	std::puts("--RangesCompileTimeSize--");
	
	constexpr std::array origArray = { 0, 8, 15, 143,45,3,77 };

#if !defined (__GNUG__)  || defined _MSC_VER && !defined(__clang__)
	auto tmp = mergeValues(origArray, 42, 4);
	auto merged = std::views::counted(tmp.first.begin(), tmp.second);
	for (const auto& i : merged) {
		std::cout << i << ' ';
	}
#endif
}


// Example from Chris Csuiak to write a Ardunio project
#if defined (__GNUG__)  || defined _MSC_VER && !defined(__clang__)
void LambdaVariadicCapture_ContEval()
{
	std::puts("--LambdaVariadicCapture_ContEval--");

	[[maybe_unused]] constexpr auto sum = [](auto arg, auto... args)
	{
		if (std::is_constant_evaluated())
		//if consteval     //C++23 feature; works for GCC 11.3+ 
		{
			return (arg + ... + args);
		}
		else
		{
			([&arg, ...args](auto value)
			{
				// assembly code valid for GCC only MSVC has different assembly codes
				asm("leal (%1, %2), %0"
					:"=r" (arg)
					: "r" (arg),
					  "r" (value));
			}(args), ...);
			return arg;
		}
	};

	auto val = sum(1, 2, 3);
	std::printf("%i\n", val);
}
#endif

void Ranges_CountedIterator()
{
	std::puts("--Ranges_CountedIterator--");
	// std::counted_iterator is an iterator that has a count to specify the end of a range
	std::vector vec{ 1,2,3,3,4,5,6,7,8,9 };

	// pos.count == 0 means the end of count
	for (auto pos = std::counted_iterator{ vec.begin(), 4 }; pos.count() > 0; ++pos)
	{
		std::printf("%i ", *pos);
	}

	std::puts(" ");

	for (auto pos = std::counted_iterator{ vec.begin(), 5 }; pos != std::default_sentinel; ++pos)
	{
		std::printf("%i ", *pos);
	}

}


