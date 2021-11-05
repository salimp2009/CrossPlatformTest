cmake_minimum_required (VERSION 3.8)

project ("Ranges")
# Add source to this project's executable.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Uncomment if Shared Library is given as an option
#set(BUILD_SHARED_LIBS NO)

#added to use precompiled headers
add_library(CommonPCH INTERFACE)
target_precompile_headers(CommonPCH INTERFACE 
	[["RangesHeaders.hpp"]]
)

target_include_directories(CommonPCH INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)


add_library(RangesTest
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

target_link_libraries(RangesTest PRIVATE CommonPCH)

add_executable (RangeTest src/RangesTest.cpp) 
# if Ranges is used in another project as a library then make it INTERFACE or PUBLIC
# if only Ranges needs the specified list then use PRIVATE
target_link_libraries(RangeTest PRIVATE RangesTest)

