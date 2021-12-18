#pragma once

#include "RangesHeaders.hpp"
#include "RangeUtils.hpp"
#include "CustomTakeView.hpp"
#include "RangesUseCases.hpp"
#include "RangesViewsAdaptor.hpp"

// Clang-13 has incomplete in Ranges gives error gcc and msvc is mostly OK;

#if defined __GNUG__  || defined _MSC_VER && !defined(__clang__)

inline void RangesBasics()
{
	std::puts("---RangesBasics---");

	auto vec1 = std::vector{ 3,4,6,5, 7,9 };

	// ranges return a std::default_sentinel_t  for the type of end iterator. But std::accumulate algorith expect a comman_range which has the same type for begin an end
	// By adding std::views::common we convert range to return a common_range so we can use in regular STL algorithms
	// any ranges algorithm dont need that conversion
	auto range1 = vec1 | std::views::take_while([](int x) { return x < 5; }) | std::views::common;

	for (const auto& value : range1)
	{
		std::printf("%d", value);
	}

	auto result = std::accumulate(range1.begin(), range1.end(), 0);

	std::printf("\nranges: %d", result);

}


inline void RangesSort_Test()
{
	std::puts("---RangesSort---");
	std::vector<Book>bookList{
		{"Functional Programming", "978-3-16-148410-0"},
		{"Effective C++", "978-3-16-14810-0"} };

	std::puts("Before Sorting");
	for (const auto& book : bookList)
	{
		std::printf(" title: %s, ISBN: %s \n", book.title.data(), book.isbn.data());
	}

	std::ranges::sort(bookList, {}, &Book::title);
	std::puts("After Sorting");
	for (const auto& book : bookList)
	{
		std::printf(" title: %s, ISBN: %s \n", book.title.data(), book.isbn.data());
	}
}

inline void RangesViews_Filter()
{
	std::puts("\n---RangesViews_Filter---");
	std::vector<int>numbers{ 1,2,3,4,5,7,8,9 };

	auto filterTransform = numbers | std::views::filter([](auto number) { return number % 2!= 0; })
		
						  | std::views::transform([](auto elem) {return elem * 2; });
	//

	for (const auto& number : filterTransform)
	{
		std::printf("%d ", number);
	}
	std::puts("\nOriginal vector after views transform:");

	for (const auto& number : numbers)
	{
		std::printf("%d ", number);
	}

}

inline void RangeAdoptors()
{
	std::printf("\n--RangeAdoptors--\n");

	std::vector<int>numbers{ 1,2,3,4,5,7,8,9 };

	auto filtered = numbers | std::views::filter([](auto number) { return number % 2 != 0; });

	auto transformed = std::views::transform([](auto elem) {return elem * 2; });

	auto results = transformed(filtered);

	for (const auto& number : results)
	{
		std::printf("%d ", number);
	}
	std::puts("");

}

inline void IsConstEvaluated_Test()
{
	std::printf("\n--IsConstEvaluated_Test--\n");

	const int y{};
	constexpr auto result1 = std::is_constant_evaluated() ? y : 1;
	static_assert(result1 == y);
	std::printf("result1 : %d", result1);

}

inline void CustomTakeView_Test()
{
	std::printf("\n--CustomTakeView_Test--\n");
	
	std::vector<int>numbers{ 1,2,3,4,5,7,8,9 };

	[[maybe_unused]] auto result = custom_take_view(numbers, 5);

	for (const auto& elem : custom_take_view(numbers, 2))
	{
		std::printf("%d ", elem);
	}
	
	std::puts("");

	auto Iseven = [](const auto& elem) { return elem % 2 == 0; };

	auto rng = numbers | std::ranges::views::filter(Iseven) | view::custom_take(2);

	auto rng2 = numbers | view::custom_take(4);

	std::puts("print first 2 Even elems");
	std::ranges::copy(rng, std::ostream_iterator<int>(std::cout, " "));
	
	std::puts("\nprint first 4 elems ");
	std::ranges::copy(rng2, std::ostream_iterator<int>(std::cout, " "));

	std::puts("\nPrinting with for-loop ");
	for (const auto& elem : numbers | std::ranges::views::filter(Iseven) | view::custom_take(2))
	{
		std::printf("%d ", elem);
	}

	std::puts("");
}

#endif