#include "RangesHeaders.hpp"
#include "RangesCompileTimeSize.hpp"

#if !defined (__GNUG__)  || defined _MSC_VER && !defined(__clang__)
// COMPILEs with MSVC only
template<typename T, typename...Args>
consteval auto mergeValues(T rng, Args&&... args)
{
	constexpr auto maxSz = rng.size() + sizeof...(args);     // OK

	//auto cmnRng = std::views::common(rng);
	std::vector<std::ranges::range_value_t<T>> tmpVec{ std::ranges::begin(rng), std::ranges::end(rng) };
	(..., tmpVec.push_back(std::forward<Args>(args)));

	std::ranges::sort(tmpVec);

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
	std::puts("");
}


// Example from Chris Csuiak to write a Ardunio project
#if defined (__GNUG__)  || !defined _MSC_VER && !defined(__clang__)
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

#if !defined (_MSC_VER)
	// check count val is not greater than the vec.size()
	auto countVal = 4;
	// if auto is used the type is ptrdiff_t and std::min does not work
	// better to use unsigned int then no conversions will be neccessary but sometime signed int is better optimized
	int vecSize = vec.size();
	countVal = std::min(countVal, vecSize);

// pos.count == 0 means the end of count
// pos.count gives how many elements left from the counted value
	for (auto pos = std::counted_iterator{ vec.begin(), countVal }; pos.count() > 0; ++pos)
	{
		std::printf("%i ", *pos);
	}

	std::puts(" ");
#endif

	// pos!=std::default_sentinel means end != vec.end() because we are only using a given number of elems which may not be 
	// equal to the end ; NOTE the count value + vec.begin() should be at least equal or less than vec.end() in order to avoid 
	// Undefined Behaviour !!!!
	for (auto pos = std::counted_iterator{ vec.begin(), 5 }; pos != std::default_sentinel; ++pos)
	{
		std::printf("%i ", *pos);
	}

}


struct Starmatch
{
	auto operator==(auto pos) const
	{
		return *pos == "Didem";
	}
};


void Ranges_CommonIterator()
{
	std::puts("\n--Ranges_CommonIterator--");

	auto FireCopy = []<typename ForwardIter>(ForwardIter first, ForwardIter last) { std::copy(first, last, std::ostream_iterator<std::string_view>{std::cout, " "}); };

	std::list<std::string> starNames = { "Semos","Demir", "Didem", "Semsi" };

	using IT = std::common_iterator<std::counted_iterator<std::list<std::string>::iterator>, std::default_sentinel_t>;

	FireCopy(IT(std::counted_iterator(starNames.begin(), starNames.size() - 1)), IT(std::default_sentinel));

	auto v = std::views::common(std::ranges::subrange(starNames.begin(), starNames.end()));
	std::puts("");
	std::copy(v.begin(), v.end(), std::ostream_iterator<decltype(v.begin())::value_type>{std::cout, " "});

	std::puts("");
	auto rng = v | std::views::take_while([](std::string_view name) { return name != "Semsi"; }) | std::views::common;
	FireCopy(rng.begin(), rng.end());

	
	auto rng2 = std::ranges::subrange(starNames.begin(), Starmatch{});

	std::puts("");
	for (auto name : rng2)
	{
		std::printf("%s ", name.c_str());
	}

	std::puts("");
}


