cmake_minimum_required(VERSION 3.12)
project(step-src CXX)

set(SOURCE_FILES
        ../include/step_api.hpp
    ../include/types.hpp
        ../include/step_exception.hpp
    ../include/map.hpp
    ../include/point.hpp
    ../include/utils.hpp
    ../include/property.hpp
    ../include/color.hpp
    ../include/text.hpp
    ../include/tileset.hpp
    ../include/tile.hpp
    ../include/frame.hpp
    ../include/animation.hpp
    ../include/grid.hpp
    ../include/tile_offset.hpp
    ../include/terrain.hpp
    ../include/layer.hpp
    ../include/chunk.hpp
    ../include/data.hpp
    ../include/tile_layer.hpp
    ../include/image_layer.hpp
    ../include/object_group.hpp
    ../include/object.hpp
    ../include/properties.hpp
    ../include/wang_set.hpp
    ../include/wang_color.hpp
    ../include/wang_tile.hpp
        ../include/step_fwd.hpp
    ../include/valid_property.hpp)

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
