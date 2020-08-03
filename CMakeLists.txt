cmake_minimum_required(VERSION 3.0.2)

project(unicons)

set(UNICONS_PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(UNICONS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Versioning
# ==========

file(STRINGS "${UNICONS_INCLUDE_DIR}/unicode_traits.hpp" unicons_version_defines
     REGEX "#define UNICONS_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${unicons_version_defines})
    if(ver MATCHES "#define UNICONS_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(UNICONS_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION
    ${UNICONS_VERSION_MAJOR}.${UNICONS_VERSION_MINOR}.${UNICONS_VERSION_PATCH})
message(STATUS "unicons v${${PROJECT_NAME}_VERSION}")

# Build
# =====

file(GLOB_RECURSE UNICONS_HEADERS ${UNICONS_INCLUDE_DIR}/*.hpp)

add_library(unicons INTERFACE)
target_include_directories(unicons INTERFACE $<BUILD_INTERFACE:${UNICONS_INCLUDE_DIR}>
                                           $<INSTALL_INTERFACE:include>)

OPTION(BUILD_TESTS "unicons test suite" ON)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS unicons
        EXPORT ${PROJECT_NAME}-targets)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

install(DIRECTORY ${UNICONS_INCLUDE_DIR}/unicode_traits
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# GNUInstallDirs "DATADIR" wrong here; CMake search path wants "share".
set(UNICONS_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for uniconsConfig.cmake")

configure_package_config_file(build_files/cmake/config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${UNICONS_CMAKECONFIG_INSTALL_DIR})

# unicons is header-only and does not depend on the architecture.

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${UNICONS_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${UNICONS_CMAKECONFIG_INSTALL_DIR})

