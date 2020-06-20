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
        unittest/step_tileset_test.cpp
        unittest/step_tile_test.cpp
        unittest/step_frame_test.cpp
        unittest/step_animation_test.cpp
        unittest/step_grid_test.cpp
        unittest/step_tile_offset_test.cpp
        unittest/step_terrain_test.cpp
        unittest/step_layer_test.cpp
        unittest/step_test_utils.h
        unittest/step_chunk_test.cpp
        unittest/step_data_test.cpp
        unittest/step_properties_test.cpp
        unittest/step_object_test.cpp
        unittest/step_test.cpp
        unittest/step_wang_color_test.cpp
        unittest/step_wang_tile_test.cpp
        unittest/step_wang_set_test.cpp)

add_executable(${STEP_TEST_TARGET} ${TEST_FILES})
add_dependencies(${STEP_TEST_TARGET} ${STEP_LIB_TARGET})

set_target_properties(${STEP_TEST_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

add_library(Doctest INTERFACE)
target_include_directories(Doctest INTERFACE doctest)

include(doctest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${STEP_TEST_TARGET} PRIVATE -Wno-unused-result)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${STEP_TEST_TARGET} PRIVATE "/MP")
endif ()

target_include_directories(${STEP_TEST_TARGET}
        PUBLIC unittest
        PUBLIC ${STEP_INCLUDE_DIR}
        SYSTEM PUBLIC ${STEP_LIBRARY_DIR}/json
        SYSTEM PUBLIC ${STEP_LIBRARY_DIR}/namedtype)

target_link_libraries(${STEP_TEST_TARGET}
        PUBLIC ${STEP_LIBRARIES}
        PUBLIC libJSON
        PUBLIC libNamedType
        PUBLIC Doctest)

#doctest_discover_tests(${STEP_TEST_TARGET})

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