cmake_minimum_required(VERSION 3.15)
project(TactiledSource)

set(SOURCE_FILES
        ${TACTILED_INCLUDE_DIR}/tactiled_cfg.h
        ${TACTILED_INCLUDE_DIR}/tiled_map.h
        tiled_map.cpp

        )

add_library(${TACTILED_LIB_TARGET} SHARED ${SOURCE_FILES})
if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

set_target_properties(${TACTILED_LIB_TARGET} PROPERTIES LINKER_LANGUAGE CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TACTILED_LIB_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wdouble-promotion
            -Wswitch-default
            -Wswitch-enum
            -Wunused
            -Wuninitialized
            -Wsuggest-final-types
            -Wsuggest-final-methods
            -Wsuggest-override
            -Wduplicated-cond
            -Wconversion)
endif ()

set_target_properties(${TACTILED_LIB_TARGET} PROPERTIES
        VERSION 0.1.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "Tactiled")

target_include_directories(${TACTILED_LIB_TARGET} PRIVATE ${TACTILED_INCLUDE_DIR}
        SYSTEM INTERFACE ${TACTILED_INCLUDE_DIR})
target_include_directories(${TACTILED_LIB_TARGET} PUBLIC ${TACTILED_SOURCE_DIR})
