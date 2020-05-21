cmake_minimum_required(VERSION 3.15)
project(Tactiled)

set(TACTILED_ROOT ${PROJECT_SOURCE_DIR})
set(TACTILED_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(TACTILED_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TACTILED_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/include/lib)

set(TACTILED_LIB_TARGET libTactiled)
set(TACTILED_TEST_TARGET testTactiled)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(TACTILED_DYNAMIC_LIB "${CMAKE_BINARY_DIR}/src/libTactiled${CMAKE_SHARED_LIBRARY_SUFFIX}")
    set(TACTILED_LIBRARIES "${CMAKE_BINARY_DIR}/src/libTactiled${CMAKE_IMPORT_LIBRARY_SUFFIX}")
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" OR DEFINED ENV{TRAVIS})
    set(TACTILED_LIBRARIES "${CMAKE_BINARY_DIR}/src/libTactiled.so")
else ()
    message(FATAL_ERROR "Did not recognize the platform!")
endif ()

include(CTest)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)