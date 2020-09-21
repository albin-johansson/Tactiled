cmake_minimum_required(VERSION 3.12)
project(StepSource CXX)

set(SOURCE_FILES
        ../include/step_api.hpp
        ../include/step_types.hpp
        ../include/step_exception.hpp
        ../include/step_map.hpp
        ../include/step_point.hpp
        ../include/step_utils.hpp
        ../include/step_property.hpp
        ../include/step_color.hpp
        ../include/step_text.hpp
        ../include/step_tileset.hpp
        ../include/step_tile.hpp
        ../include/step_frame.hpp
        ../include/step_animation.hpp
        ../include/step_grid.hpp
        ../include/step_tile_offset.hpp
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
        ../include/step_wang_tile.hpp
        ../include/step_fwd.hpp
        ../include/step_valid_property.hpp)

add_library(${STEP_LIB_TARGET} INTERFACE)
if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(STEP_OUTPUT_NAME step)
else ()
    set(STEP_OUTPUT_NAME libstep)
endif ()

target_include_directories(${STEP_LIB_TARGET}
        PUBLIC INTERFACE ${STEP_INCLUDE_DIR}
        SYSTEM PUBLIC INTERFACE ${STEP_LIBRARY_DIR}/json
        SYSTEM PUBLIC INTERFACE ${STEP_LIBRARY_DIR}/namedtype)

target_link_libraries(${STEP_LIB_TARGET}
        PUBLIC INTERFACE libNamedType
        PUBLIC INTERFACE libJSON)
