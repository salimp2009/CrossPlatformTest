// CrossPlatformTest.cpp : Defines the entry point for the application.
//

#include "CrossPlatformTest.h"
#include "Coroutines.hpp"
#include "Coroutines/CoroutineAsyncStreamParser.hpp"
#include "Coroutines/CoroutineAsyncStreamParserV2.hpp"
#include "Coroutines/CoroutinesCustomAllocator.hpp"

#include <list>
#include <stdalign.h>

int main()
{

#if _GLIBCXX_RANGES || ! defined(__clang__)

	CoroutineAsyncStreamParser();
	AsyncStreamParserV2::AysncStreamParserV2_Corotn();
	CustomAllocator_Corotn();

	std::printf("\n--EagerFuture_Coroutine--\n");
	auto fut = createFuture(2021);
	std::printf("eager future result : %d\n", fut.get());
	std::printf("eager future result : %d\n", fut.get());

#endif

	return 0;
}
