cmake_minimum_required(VERSION 3.12)
project(StepSource)

set(SOURCE_FILES
        ../include/step_api.h
        ../include/step_types.h
        ../include/step_exception.h

        ../include/step.h
        step.cpp

        ../include/step_map.h
        step_map.cpp

        ../include/step_point.h
        step_point.cpp

        ../include/step_utils.h
        step_utils.cpp

        ../include/step_property.h
        step_property.cpp

        ../include/step_color.h
        step_color.cpp

        ../include/step_text.h
        step_text.cpp

        ../include/step_tileset.h
        step_tileset.cpp

        ../include/step_tile.h
        step_tile.cpp

        ../include/step_frame.h
        step_frame.cpp

        ../include/step_animation.h
        step_animation.cpp

        ../include/step_grid.h
        step_grid.cpp

        ../include/step_tile_offset.h
        step_tile_offset.cpp

        ../include/step_terrain.h
        step_terrain.cpp

        ../include/step_layer.h
        step_layer.cpp

        ../include/step_chunk.h
        step_chunk.cpp

        ../include/step_data.h
        step_data.cpp

        ../include/step_tile_layer.h
        step_tile_layer.cpp

        ../include/step_image_layer.h
        step_image_layer.cpp

        ../include/step_object_group.h
        step_object_group.cpp

        ../include/step_group.h
        step_group.cpp

        ../include/step_object.h
        step_object.cpp

        ../include/step_properties.h
        step_properties.cpp

        ../include/step_wang_set.h
        step_wang_set.cpp

        ../include/step_wang_color.h
        step_wang_color.cpp

        ../include/step_wang_tile.h
        step_wang_tile.cpp)

add_library(${STEP_LIB_TARGET} SHARED ${SOURCE_FILES})
if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(STEP_OUTPUT_NAME step)
else ()
    set(STEP_OUTPUT_NAME libstep)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${STEP_LIB_TARGET} PRIVATE "/MP")
endif ()

set_target_properties(${STEP_LIB_TARGET} PROPERTIES
        VERSION 0.1.0
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        OUTPUT_NAME ${STEP_OUTPUT_NAME})

target_include_directories(${STEP_LIB_TARGET}
        PUBLIC ${STEP_INCLUDE_DIR}
        PUBLIC ${STEP_SOURCE_DIR}
        SYSTEM PUBLIC ${STEP_LIBRARY_DIR}/json
        SYSTEM PUBLIC ${STEP_LIBRARY_DIR}/namedtype)

target_link_libraries(${STEP_LIB_TARGET}
        PUBLIC libNamedType
        PUBLIC libJSON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${STEP_LIB_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wdouble-promotion
            -Wswitch-default
            -Wswitch-enum
            -Wunused
            -Wsuggest-final-types
            -Wsuggest-final-methods
            -Wsuggest-override
            -Wduplicated-cond
            -Wconversion
            -Wno-c++14-compat
            -Wno-c++11-compat)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${STEP_LIB_TARGET} PRIVATE
            /EHsc
            -Wall
            -Wextra
            -Wpedantic
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-documentation-unknown-command
            -Wno-documentation-pedantic
            -Wno-newline-eof)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${STEP_LIB_TARGET} PRIVATE
            /EHsc
            /MP
            /W3)
endif ()