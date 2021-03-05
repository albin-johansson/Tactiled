cmake_minimum_required(VERSION 3.12)

project(step-test-unit CXX)

set(TEST_FILES
    main.cpp
    property_test.cpp)

add_executable(${STEP_TEST_TARGET} ${TEST_FILES})

target_include_directories(${STEP_TEST_TARGET}
    SYSTEM PUBLIC ${STEP_SOURCE_DIR}
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gtest_SOURCE_DIR}
    SYSTEM PUBLIC ${gmock_SOURCE_DIR}/include
    SYSTEM PUBLIC ${gmock_SOURCE_DIR})

target_link_libraries(${STEP_TEST_TARGET}
    PUBLIC gtest
    PUBLIC libJSON)

copy_directory_post_build(${STEP_TEST_TARGET}
    ${STEP_RESOURCES_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)
