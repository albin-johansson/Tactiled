cmake_minimum_required(VERSION 3.12)
project(Tactiled)

# Copies a file.
#   target: the associated target.
#   from: the file that will be copied.
#   to: the target destination of the copied file.
function(copy_file_post_build [target [from [to]]])
    add_custom_command(
            TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${ARGV1}
            ${ARGV2})
endfunction()

# Copies a directory.
#   target: the associated target.
#   from: the directory that will be copied.
#   to: the target destination of the copied directory.
function(copy_directory_post_build [target [from [to]]])
    add_custom_command(
            TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${ARGV1}
            ${ARGV2})
endfunction()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

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

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

# Prepare doctest for other targets to use
set(doctest_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/doctest)
find_package(doctest REQUIRED)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)