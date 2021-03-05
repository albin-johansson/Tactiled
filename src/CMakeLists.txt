cmake_minimum_required(VERSION 3.12)
project(step-src CXX)

set(SOURCE_FILES
    step/step_api.hpp
    step/types.hpp
    step/step_exception.hpp
    step/map.hpp
    step/point.hpp
    step/utils.hpp
    step/property.hpp
    step/color.hpp
    step/text.hpp
    step/tileset.hpp
    step/tile.hpp
    step/frame.hpp
    step/animation.hpp
    step/grid.hpp
    step/tile_offset.hpp
    step/terrain.hpp
    step/layer.hpp
    step/chunk.hpp
    step/data.hpp
    step/tile_layer.hpp
    step/image_layer.hpp
    step/object_group.hpp
    step/object.hpp
    step/properties.hpp
    step/wang_set.hpp
    step/wang_color.hpp
    step/wang_tile.hpp
    step/step_fwd.hpp
    step/valid_property.hpp)

add_library(${STEP_LIB_TARGET} INTERFACE)
if (WIN32)
    add_definitions(-DWIN_EXPORT)
endif ()

target_include_directories(${STEP_LIB_TARGET}
        PUBLIC INTERFACE ${STEP_INCLUDE_DIR}
        SYSTEM PUBLIC INTERFACE ${STEP_LIBRARY_DIR}/json
        SYSTEM PUBLIC INTERFACE ${STEP_LIBRARY_DIR}/namedtype)

target_link_libraries(${STEP_LIB_TARGET}
        PUBLIC INTERFACE libNamedType
        PUBLIC INTERFACE libJSON)
