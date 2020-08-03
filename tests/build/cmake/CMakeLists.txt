
#
# unicode_traits tests CMake file 
#

cmake_minimum_required (VERSION 2.8)

# load global config
include (../../../build/cmake/config.cmake)

project (Tests CXX) 

# load per-platform configuration
include (../../../build/cmake/${CMAKE_SYSTEM_NAME}.cmake)

include_directories (../../src
                     ../../../include)

file(GLOB_RECURSE Test_sources ../../src/*.cpp)

add_executable (unicode_traits_tests ${Test_sources})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  # special link option on Linux because llvm stl rely on GNU stl
  target_link_libraries (unicode_traits_tests -Wl,-lstdc++)
endif()
