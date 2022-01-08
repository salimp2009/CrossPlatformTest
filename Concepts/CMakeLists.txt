cmake_minimum_required (VERSION 3.16)

project ("Concepts")
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
add_library(ConceptsPCH INTERFACE)
target_precompile_headers(ConceptsPCH INTERFACE 
	[["ConceptsPCH.hpp"]]
)

target_include_directories(ConceptsPCH  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)


add_library(ConceptsTestLib
		#src/ConceptsTest.cpp
        src/ConceptsRequires/ConceptRequires.hpp 
        src/ConceptsRequires/ConceptsRequires.cpp
        src/ConceptsRequires/OverloadResolution.hpp
        src/ConceptsRequires/OverloadResOLD.hpp 
        src/ConceptsRequires/ConstraintSamples.hpp
)

target_include_directories(ConceptsTestLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

target_link_libraries(ConceptsTestLib PRIVATE ConceptsPCH)

add_executable (ConceptsTest src/ConceptsTest.cpp) 
# if Ranges is used in another project as a library then make it INTERFACE or PUBLIC
# if only Ranges needs the specified list then use PRIVATE
target_link_libraries(ConceptsTest PRIVATE project_options ConceptsTestLib)


