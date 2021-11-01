cmake_minimum_required (VERSION 3.8)

project ("Ranges")
# Add source to this project's executable.

add_library(RangesTest
	STATIC
		src/RangesTest.cpp
		src/RangesHeaders.hpp
		src/RangesBasic.hpp
		src/RangeUtils.hpp
		src/Span/SpanTest.hpp 
		src/Span/SpanUtils.hpp
		src/CustomTakeView.hpp
		src/RangesUseCases.hpp
		src/RangesViewsAdaptor.hpp
)

target_include_directories(RangesTest PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

add_executable (RangeTest src/RangesTest.cpp) 
target_link_libraries(RangeTest PRIVATE RangesTest)
