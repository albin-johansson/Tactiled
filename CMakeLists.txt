cmake_minimum_required(VERSION 3.12)
project(Step)

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

set(STEP_ROOT ${PROJECT_SOURCE_DIR})
set(STEP_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(STEP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(STEP_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/include/lib)

set(STEP_LIB_TARGET libstep)
set(STEP_TEST_TARGET teststep)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(STEP_DYNAMIC_LIB "${CMAKE_BINARY_DIR}/src/libstep${CMAKE_SHARED_LIBRARY_SUFFIX}")
    set(STEP_LIBRARIES "${CMAKE_BINARY_DIR}/src/libstep${CMAKE_IMPORT_LIBRARY_SUFFIX}")
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" OR DEFINED ENV{TRAVIS})
    set(STEP_LIBRARIES "${CMAKE_BINARY_DIR}/src/libstep.so")
else ()
    message(FATAL_ERROR "Did not recognize the platform!")
endif ()

include(CTest)

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

enable_testing()
add_subdirectory(src)
add_subdirectory(test)