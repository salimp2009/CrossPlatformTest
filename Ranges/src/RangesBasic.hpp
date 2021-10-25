#pragma

#include "RangesHeaders.hpp"
#include "RangeUtils.hpp"
#include "CustomTakeView.hpp"

// Clang-13 has incomplete in Ranges gives error gcc and msvc is mostly OK;


inline void RangesBasics()
{
	std::puts("---RangesBasics---");

	auto vec1 = std::vector{ 3,4,6,5, 7,9 };

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

	for (const auto& number : filterTransform)
	{
		std::printf("%d ", number);
	}
	std::puts("");
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

	auto result = custom_take_view(numbers, 5);

	for (const auto& elem : custom_take_view(numbers, 2))
	{
		std::printf("%d ", elem);
	}
	
	std::puts("");
}
