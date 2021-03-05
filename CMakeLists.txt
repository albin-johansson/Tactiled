cmake_minimum_required(VERSION 3.12)

project(step
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/albin-johansson/step"
    LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(STEP_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(STEP_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/step)
set(STEP_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)
set(STEP_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/test/resource)

set(STEP_LIBRARY_TARGET step_lib)
set(STEP_TEST_TARGET step_tests)

include(Utilities)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

add_library(${STEP_LIBRARY_TARGET} INTERFACE)

add_subdirectory(src)
add_subdirectory(test)