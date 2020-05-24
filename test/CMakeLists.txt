cmake_minimum_required(VERSION 3.12)
project(StepTest)

set(doctest_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/doctest)
find_package(doctest REQUIRED)

set(STEP_TEST_RESOURCES ${PROJECT_SOURCE_DIR}/resource)
set(TEST_FILES
        unittest/test_main.cpp
        unittest/step_map_test.cpp
        unittest/step_point_test.cpp
        unittest/step_property_test.cpp
        unittest/step_color_test.cpp
        unittest/step_utils_test.cpp
        unittest/step_text_test.cpp
        unittest/step_frame_test.cpp)

add_executable(${STEP_TEST_TARGET} ${TEST_FILES})
add_dependencies(${STEP_TEST_TARGET} ${STEP_LIB_TARGET})

set_target_properties(${STEP_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

add_library(Doctest INTERFACE)
target_include_directories(Doctest INTERFACE doctest)

include(doctest)

add_test(NAME ${STEP_TEST_TARGET}
        COMMAND ${STEP_TEST_TARGET})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${STEP_TEST_TARGET} PRIVATE
            -Wno-unused-result
            )
endif ()

target_include_directories(${STEP_TEST_TARGET} PUBLIC unittest)
target_include_directories(${STEP_TEST_TARGET} SYSTEM PUBLIC ${STEP_LIBRARY_DIR})
target_include_directories(${STEP_TEST_TARGET} SYSTEM PUBLIC ${STEP_INCLUDE_DIR})
target_include_directories(${STEP_TEST_TARGET} SYSTEM PUBLIC ${STEP_SOURCE_DIR})

target_link_libraries(${STEP_TEST_TARGET}
        PUBLIC ${STEP_LIBRARIES}
        PUBLIC Doctest)

copy_directory_post_build(
        ${STEP_TEST_TARGET}
        ${STEP_TEST_RESOURCES}
        ${CMAKE_CURRENT_BINARY_DIR}/resource)

if (WIN32)
    copy_file_post_build(
            ${STEP_TEST_TARGET}
            ${STEP_DYNAMIC_LIB}
            ${CMAKE_CURRENT_BINARY_DIR})
endif ()