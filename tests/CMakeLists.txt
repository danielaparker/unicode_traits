cmake_minimum_required(VERSION 3.0.2)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(unicons-test)

    find_package(unicons REQUIRED CONFIG)
    set(UNICONS_INCLUDE_DIR ${unicons_INCLUDE_DIRS})
endif ()

if(NOT CMAKE_BUILD_TYPE)
message(STATUS "Forcing tests build type to Release")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

include(CheckCXXCompilerFlag)

string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

include (CTest)

# load per-platform configuration
include (${UNICONS_PROJECT_DIR}/build_files/cmake/${CMAKE_SYSTEM_NAME}.cmake)

if (UNICONS_SANITIZE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MP /bigobj")
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif()

set(CTEST_OUTPUT_ON_FAILURE ON)

set(UNICONS_TESTS_DIR ${UNICONS_PROJECT_DIR}/tests)
set(UNICONS_INCLUDE_DIR ${UNICONS_PROJECT_DIR}/include)
set(UNICONS_THIRD_PARTY_INCLUDE_DIR ${UNICONS_PROJECT_DIR}/third_party)

set(CATCH_INCLUDE_DIR ${UNICONS_THIRD_PARTY_INCLUDE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories (Catch INTERFACE ${CATCH_INCLUDE_DIR})

#file(GLOB_RECURSE UNICONS_TESTS_SOURCES ${UNICONS_TESTS_DIR}/*.cpp)
#message((${UNICONS_TESTS_SOURCES}))

set(UNICONS_TESTS_SOURCES
   ${UNICONS_TESTS_DIR}/src/convert_tests.cpp
   ${UNICONS_TESTS_DIR}/src/detect_encoding_tests.cpp
   ${UNICONS_TESTS_DIR}/src/helper_tests.cpp
   ${UNICONS_TESTS_DIR}/src/sequence_at_tests.cpp
   ${UNICONS_TESTS_DIR}/src/sequence_generator_tests.cpp
   ${UNICONS_TESTS_DIR}/src/u8_length_tests.cpp
   ${UNICONS_TESTS_DIR}/src/u32_length_tests.cpp
   ${UNICONS_TESTS_DIR}/src/unicode_traits_tests.cpp
   ${UNICONS_TESTS_DIR}/src/validate_tests.cpp
   ${UNICONS_TESTS_DIR}/src/tests_main.cpp
)
set(UNICONS_TARGET test_unicons)
add_executable(${UNICONS_TARGET} EXCLUDE_FROM_ALL ${UNICONS_TESTS_SOURCES} ${UNICONS_HEADERS})

add_test(example_test ${UNICONS_TARGET})

target_include_directories (${UNICONS_TARGET} PUBLIC ${UNICONS_INCLUDE_DIR}
                                           PUBLIC ${UNICONS_THIRD_PARTY_INCLUDE_DIR})

target_link_libraries(${UNICONS_TARGET} Catch)

add_custom_target(jtest COMMAND test_unicons DEPENDS ${UNICONS_TARGET})


