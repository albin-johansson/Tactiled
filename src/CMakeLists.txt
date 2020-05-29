cmake_minimum_required(VERSION 3.12)
project(StepSource)

set(SOURCE_FILES
        ${STEP_INCLUDE_DIR}/step_cfg.h
        ${STEP_INCLUDE_DIR}/step_api.h
        ${STEP_INCLUDE_DIR}/step_types.h
        ${STEP_INCLUDE_DIR}/step_exception.h

        ${STEP_INCLUDE_DIR}/step_map.h
        step_map.cpp

        ${STEP_INCLUDE_DIR}/step_point.h
        step_point.cpp

        ${STEP_INCLUDE_DIR}/step_utils.h
        step_utils.cpp

        ${STEP_INCLUDE_DIR}/step_property.h
        step_property.cpp

        ${STEP_INCLUDE_DIR}/step_color.h
        step_color.cpp

        ${STEP_INCLUDE_DIR}/step_text.h
        step_text.cpp

        ${STEP_INCLUDE_DIR}/step_tileset.h
        step_tileset.cpp

        ${STEP_INCLUDE_DIR}/step_tile.h
        step_tile.cpp

        ${STEP_INCLUDE_DIR}/step_frame.h
        step_frame.cpp

        ${STEP_INCLUDE_DIR}/step_animation.h
        step_animation.cpp

        ${STEP_INCLUDE_DIR}/step_grid.h
        step_grid.cpp

        ${STEP_INCLUDE_DIR}/step_tile_offset.h
        step_tile_offset.cpp

        ${STEP_INCLUDE_DIR}/step_terrain.h
        step_terrain.cpp

        ${STEP_INCLUDE_DIR}/step_layer.h
        step_layer.cpp)
        ${STEP_INCLUDE_DIR}/step_chunk.h
        step_chunk.cpp
        )

add_library(${STEP_LIB_TARGET} SHARED ${SOURCE_FILES})
if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${STEP_LIB_TARGET} PRIVATE
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

set_target_properties(${STEP_LIB_TARGET} PROPERTIES
        VERSION 0.1.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        OUTPUT_NAME "step")

target_include_directories(${STEP_LIB_TARGET} PUBLIC ${STEP_INCLUDE_DIR})
target_include_directories(${STEP_LIB_TARGET} PUBLIC ${STEP_SOURCE_DIR})
target_include_directories(${STEP_LIB_TARGET} SYSTEM PUBLIC ${STEP_LIBRARY_DIR})

target_link_libraries(${STEP_LIB_TARGET})
