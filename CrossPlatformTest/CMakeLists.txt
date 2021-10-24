# CMakeList.txt : CMake project for CrossPlatformTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CrossPlatformTest")
# Add source to this project's executable.
add_executable (CrossPlatformTest "src/CrossPlatformTest.cpp" "src/CrossPlatformTest.h" "src/Coroutines.hpp" 
								"src/Coroutines/CoroutineAsyncStreamParser.hpp" "src/Modules/ModuleTest01.cpp" 
								"src/Coroutines/CoroutineAsyncStreamParserV2.hpp" "src/Coroutines/CoroutinesHeader.hpp" "src/Coroutines/CoroutinesCustomAllocator.hpp")

# TODO: Add tests and install targets if needed.
