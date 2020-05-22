cmake_minimum_required(VERSION 3.12)
project(TactiledTest)

set(doctest_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/doctest)
find_package(doctest REQUIRED)

set(TACTILED_TEST_RESOURCES ${PROJECT_SOURCE_DIR}/resource)
set(TEST_FILES
        unittest/test_main.cpp
        unittest/tactiled_map_test.cpp
        unittest/tactiled_point_test.cpp
        unittest/tactiled_utils_test.cpp)

add_executable(${TACTILED_TEST_TARGET} ${TEST_FILES})
add_dependencies(${TACTILED_TEST_TARGET} ${TACTILED_LIB_TARGET})

set_target_properties(${TACTILED_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

add_library(Doctest INTERFACE)
target_include_directories(Doctest INTERFACE doctest)

include(doctest)

add_test(NAME ${TACTILED_TEST_TARGET}
        COMMAND ${TACTILED_TEST_TARGET})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TACTILED_TEST_TARGET} PRIVATE
            -Wno-unused-result
            )
endif ()

target_include_directories(${TACTILED_TEST_TARGET} PUBLIC unittests)
target_include_directories(${TACTILED_TEST_TARGET} SYSTEM PUBLIC ${TACTILED_LIBRARY_DIR})
target_include_directories(${TACTILED_TEST_TARGET} SYSTEM PUBLIC ${TACTILED_INCLUDE_DIR})
target_include_directories(${TACTILED_TEST_TARGET} SYSTEM PUBLIC ${TACTILED_SOURCE_DIR})

target_link_libraries(${TACTILED_TEST_TARGET}
        PUBLIC ${TACTILED_LIBRARIES}
        PUBLIC Doctest)

copy_directory_post_build(
        ${TACTILED_TEST_TARGET}
        ${TACTILED_TEST_RESOURCES}
        ${CMAKE_CURRENT_BINARY_DIR}/resource)

if (WIN32)
    copy_file_post_build(
            ${TACTILED_TEST_TARGET}
            ${TACTILED_DYNAMIC_LIB}
            ${CMAKE_CURRENT_BINARY_DIR})
endif ()