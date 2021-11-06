// CrossPlatformTest.cpp : Defines the entry point for the application.
//

#include "CrossPlatformTest.h"
#include "Coroutines.hpp"
#include "Coroutines/CoroutineAsyncStreamParser.hpp"
#include "Coroutines/CoroutineAsyncStreamParserV2.hpp"
#include "Coroutines/CoroutinesCustomAllocator.hpp"
#include "Ranges/RangesBasic.hpp"



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
	Ranges_LazyEval();
	RangesSort_Strings();

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
	return 0;
}
