# CMakeList.txt : CMake project for CrossPlatformTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("CrossPlatformTest")
# Add source to this project's executable.

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
add_executable (CrossPlatformTest "src/CrossPlatformTest.cpp" "src/CrossPlatformTest.h" "src/Coroutines.hpp" 
								"src/Coroutines/CoroutineAsyncStreamParser.hpp" "src/Modules/ModuleTest01.cpp" 
								"src/Coroutines/CoroutineAsyncStreamParserV2.hpp" "src/Coroutines/CoroutinesHeader.hpp" "src/Coroutines/CoroutinesCustomAllocator.hpp" 
								    
								   )


# TODO: Add tests and install targets if needed.
