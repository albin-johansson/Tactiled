cmake_minimum_required(VERSION 3.15)
project(TactiledTest)

set(TEST_FILES
        unittest/test_main.cpp
        unittest/tiled_map_test.h)

add_executable(${TACTILED_TEST_TARGET} ${TEST_FILES})

add_dependencies(${TACTILED_TEST_TARGET} ${TACTILED_LIB_TARGET})

set_target_properties(${TACTILED_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

add_library(Doctest INTERFACE)
target_include_directories(Doctest INTERFACE lib)

target_include_directories(${TACTILED_TEST_TARGET} PUBLIC unittests)
target_include_directories(${TACTILED_TEST_TARGET} PUBLIC lib)

target_include_directories(${TACTILED_TEST_TARGET} SYSTEM PUBLIC ${TACTILED_LIBRARY_DIR})
target_include_directories(${TACTILED_TEST_TARGET} SYSTEM PUBLIC ${TACTILED_INCLUDE_DIR})
target_include_directories(${TACTILED_TEST_TARGET} SYSTEM PUBLIC ${TACTILED_SOURCE_DIR})