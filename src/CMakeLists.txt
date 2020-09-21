cmake_minimum_required(VERSION 3.12)
project(StepSource)

set(SOURCE_FILES
        ../include/step_api.hpp
        ../include/step_types.hpp
        ../include/step_exception.hpp

        ../include/step.hpp

        ../include/step_map.hpp
        step_map.cpp

        ../include/step_point.hpp
        ../include/step_utils.hpp
        ../include/step_property.hpp
        ../include/step_color.hpp
        ../include/step_text.hpp

        ../include/step_tileset.hpp
        step_tileset.cpp

        ../include/step_tile.hpp
        step_tile.cpp

        ../include/step_frame.hpp

        ../include/step_animation.hpp

        ../include/step_grid.hpp

        ../include/step_tile_offset.hpp
        step_tile_offset.cpp

        ../include/step_terrain.hpp

        ../include/step_layer.hpp

        ../include/step_chunk.hpp

        ../include/step_data.hpp

        ../include/step_tile_layer.hpp

        ../include/step_image_layer.hpp

        ../include/step_object_group.hpp

        ../include/step_object.hpp

        ../include/step_properties.hpp

        ../include/step_wang_set.hpp

        ../include/step_wang_color.hpp
        step_wang_color.cpp

        ../include/step_wang_tile.hpp
        ../include/step_fwd.hpp
        ../include/step_valid_property.hpp)

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
        VERSION ${STEP_VERSION}
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