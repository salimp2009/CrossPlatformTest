// CrossPlatformTest.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <cstdio>
#include <memory_resource>
#include <ranges>
#include <unordered_map>
#include <string>
#include <source_location>
#include <map>
#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <ranges>



#if _GLIBCXX_RANGES || ! defined(__clang__)
	struct Empty {};
	
	struct NoUniqueAddress
	{
		int d{};
		[[no_unique_address]] Empty e;
	};
	
	struct UniqueAddress
	{
		int d{};
		Empty e;
	};

#endif





