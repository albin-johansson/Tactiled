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
set(STEP_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

set(STEP_LIB_TARGET libstep)
set(STEP_TEST_TARGET teststep)

set(STEP_DYNAMIC_LIB ${CMAKE_BINARY_DIR}/src/libstep${CMAKE_SHARED_LIBRARY_SUFFIX})
set(STEP_LIBRARIES ${CMAKE_BINARY_DIR}/src/libstep${CMAKE_IMPORT_LIBRARY_SUFFIX})

# FIXME for some reason, Clang ignores the system includes of the libraries

add_library(libNamedType INTERFACE)
target_sources(libNamedType INTERFACE
        ${STEP_LIBRARY_DIR}/namedtype/named_type.hpp
        ${STEP_LIBRARY_DIR}/namedtype/named_type_impl.hpp
        ${STEP_LIBRARY_DIR}/namedtype/underlying_functionalities.hpp
        ${STEP_LIBRARY_DIR}/namedtype/crtp.hpp)
target_include_directories(libNamedType SYSTEM INTERFACE ${STEP_LIBRARY_DIR}/namedtype)

add_library(libJSON INTERFACE)
target_sources(libJSON INTERFACE ${STEP_LIBRARY_DIR}/json/json.hpp)
target_include_directories(libJSON SYSTEM INTERFACE ${STEP_LIBRARY_DIR}/json)

include(CTest)

if (DEFINED ENV{ENABLE_COVERAGE})
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif ()

enable_testing()
add_subdirectory(src)
add_subdirectory(test)