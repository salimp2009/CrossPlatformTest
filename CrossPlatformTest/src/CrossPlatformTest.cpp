// CrossPlatformTest.cpp : Defines the entry point for the application.
//

#include "CrossPlatformTest.h"
#include "Coroutines.hpp"
#include "Coroutines/CoroutineAsyncStreamParser.hpp"
#include "Coroutines/CoroutineAsyncStreamParserV2.hpp"
#include "Coroutines/CoroutinesCustomAllocator.hpp"

#include <list>



#if _GLIBCXX_RANGES 
	void foo()
	{
		std::pmr::map<int, std::pair<int, int>> tags;
		tags[0] = { 5,5 };
		std::printf("first: %d, second: %d\n", tags[0].first, tags[0].second);
	}
	
#endif

int main()
{
#if _GLIBCXX_RANGES 
		foo();
#endif

	std::vector<int> vec1{ 1,2,3,4,5,6,7,8,9,10 };
	auto noOfDeletedElems = std::erase_if(vec1, [](auto&& elem) { return elem % 2 == 0; });
	std::printf("deleted element count: %zu\n", noOfDeletedElems);
	for (auto elems : vec1)
	{
		std::printf("%d ", elems);
	}
	std::putchar('\n');

#if _GLIBCXX_RANGES || ! defined(__clang__)

	std::unordered_map<std::string, int>freqWord = { {"witch", 25}, {"wizard", 33}, {"tale", 45}, {"dog", 4}, {"cat", 34}, {"fish", 23} };
	std::puts("Keys:");
	auto names = std::views::keys(freqWord);
		
	for (const auto& name : names)
	{
		std::printf("%s ", name.c_str());
	}
	std::puts("\nValues: ");

	std::printf("sizeof NoUniqueAddress %zd \n", sizeof(NoUniqueAddress));
	std::printf("sizeof UniqueAddress %zd \n", sizeof(UniqueAddress));

	CoroutineAsyncStreamParser();
	AsyncStreamParserV2::AysncStreamParserV2_Corotn();
	CustomAllocator_Corotn();


#endif

#if _GLIBCXX_RANGES 
	std::map<std::string, int>freqWord2 = { {"witch", 25}, {"wizard", 33}, {"tale", 45}, {"dog", 4}, {"cat", 34}, {"fish", 23} };

	for (const auto& name : std::views::keys(freqWord2) | std::views::take(4))
	{
		std::printf("%s ", name.c_str());
	}



	std::printf("\n--EagerFuture_Coroutine--\n");

	auto fut = createFuture(2021);

	std::printf("eager future result : %d\n", fut.get());
	std::printf("eager future result : %d\n", fut.get());

#endif

	std::list lst = { 1,2,3,4,5,6,7,8 };
	std::ranges::iota_view iv{ 1, 10 };

	// the begin and end iterator types are not the same 
	//auto tkView1 = std::views::take(lst, 5);

	auto v1 = std::views::common(lst);
	// by using views::common returns a view that has same begin and end iterator types
	//auto v2 = std::views::common(tkView1);

	std::puts("Original List: all members:");
	std::for_each(v1.begin(), v1.end(), [](auto elem) {std::printf("%i ", elem); });
	std::puts("\nstd::views::take(); list with 5 elems:");
	//std::for_each(v2.begin(), v2.end(), [](auto elem) {std::printf("%i ", elem); });

	auto vecRg = std::vector{ 3,4,6,5, 7,9 };

	// ranges return a std::default_sentinel_t  for the type of end iterator. But std::accumulate algorith expect a comman_range which has the same type for begin an end
	// By adding std::views::common we convert range to return a common_range so we can use in regular STL algorithms
	// any ranges algorithm dont need that conversion
	auto range1 = vecRg | std::views::take_while([](int x) { return x < 5; }) | std::views::common;

	std::puts("");

	return 0;
}
