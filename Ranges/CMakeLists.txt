cmake_minimum_required (VERSION 3.8)

project ("Ranges")
# Add source to this project's executable.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#ADDED extra checks from Andreas Fertig's' "Programming with C++20" code examples
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(IS_GNU On)
    add_definitions(-DIS_GCC=true)
else()
    set(IS_GNU Off)
    add_definitions(-DIS_GCC=false)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(IS_CLANG On)
    add_definitions(-DIS_CLANG=true)
else()
    set(IS_CLANG Off)
    add_definitions(-DIS_CLANG=false)
endif()

if(MSVC)
    add_definitions(-DIS_MSVC=true)
    #add_definitions(/WX)
    add_definitions(/W3)
    add_definitions(/wd4189)
    add_definitions(/wd4100)
    add_definitions(/wd4996) # 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
    add_definitions(/wd4267)
    add_definitions(/wd4505)
    #add_definitions(/await) # enable coroutine support

    # Use sane and nice C++ for MSVC.
    # This makes alternative tokens (not, and, ...) as actual keywords and
    # enables more conformant C++ in general
    add_definitions(/permissive-)
    #add_definitions(/std:c++latest)

    
else()
    add_definitions(-DIS_MSVC=false)
    #add_definitions(-Werror)
    add_definitions(-Wall)
    add_definitions(-Wextra)
    add_definitions(-Wold-style-cast)
    add_definitions(-Wno-unused-variable)
    add_definitions(-Wno-unused-parameter)
    add_definitions(-Wno-unused-value)
    add_definitions(-Wno-cpp)

    if(IS_CLANG)
      add_definitions(-Wno-unused-private-field)
      add_definitions(-Wno-unneeded-internal-declaration)
      
    else()
      add_definitions(-fcoroutines) # required for GCC-10    
      #add_definitions(-fpermissive) # to relax typename requirement    
      
    endif()
endif()


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


add_library(RangesTestLib
		src/RangesTest.cpp
		src/RangesViewsComponents.cpp
		src/RangesBasic.hpp
		src/RangeUtils.hpp
		src/Span/SpanTest.hpp 
		src/Span/SpanUtils.hpp
		src/CustomTakeView.hpp
		src/RangesUseCases.hpp
		src/RangesViewsAdaptor.hpp
		src/RangesViewsComponents.hpp	
        src/RangesCompileTimeSize.hpp
        src/RangesCompileTimeSize.cpp
        src/NTTP/NTTP.hpp 
        src/NTTP/NTTP.cpp
        src/NTTP/NTTPUtils.hpp
        src/NTTP/NTTPFixedString.hpp
        src/CompileTimeThings/CompileRunTime.hpp
        src/CompileTimeThings/CompileRunTime.cpp
        src/CompileTimeThings/CompileTimeByteSwap.hpp
        src/CompileTimeThings/CompileTimeCarRacing.hpp
        src/CompileTimeThings/ConstexprUniquePtr.hpp
        src/Views/ViewTests.hpp 
        src/Views/ViewTests.cpp
        src/CompileTimeThings/ConstEvalUseCases.hpp src/CompileTimeThings/ConstEvalUseCases.cpp
        src/CompileTimeThings/CustomFormatterTypeSafe.hpp 
        src/CompileTimeThings/ConstexprString.hpp
        src/TemplatesMetaProg/MetaProgramBasics.hpp
        src/TemplatesMetaProg/MetaProgramBasics.cpp
        src/NTTP/NamedTupple.hpp 
        src/NTTP/NamedTupple.cpp
        src/TemplatesMetaProg/MetaProgLinearSearch.hpp 
        src/TemplatesMetaProg/MetaProgInHeritance.hpp
        src/TemplatesMetaProg/DecltypeAutoUses.hpp 
        src/TemplatesMetaProg/MetaProgramSortTypes.hpp
        src/SpaceShipOperator/SpaceShipOperTests.hpp 
        src/SpaceShipOperator/SpaceShipOperTests.cpp
        src/GenericFunctionsCpp20/GenericFunctions.hpp 
        src/GenericFunctionsCpp20/GenericFunctions.cpp
 
 )

target_include_directories(RangesTestLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

target_link_libraries(RangesTestLib PRIVATE CommonPCH)

add_executable (RangeTest src/RangesTest.cpp) 
# if Ranges is used in another project as a library then make it INTERFACE or PUBLIC
# if only Ranges needs the specified list then use PRIVATE
target_link_libraries(RangeTest PRIVATE project_options RangesTestLib)


