cmake_minimum_required(VERSION 3.12)

project(step-src CXX)

add_header_only_lib(libJSON ${STEP_LIBRARY_DIR}/json ${STEP_LIBRARY_DIR}/json/json.hpp)

set(SOURCE_FILES
    step/step_api.hpp
    step/common.hpp
    step/step_exception.hpp
    step/map.hpp
    step/point.hpp
    step/step_detail.hpp
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

target_include_directories(${STEP_LIBRARY_TARGET} PUBLIC INTERFACE ${STEP_SOURCE_DIR})
#target_link_libraries(${STEP_LIBRARY_TARGET} PUBLIC INTERFACE libJSON)
