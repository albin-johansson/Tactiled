#ifndef STEP_GRID_HEADER
#define STEP_GRID_HEADER

#include "common.hpp"

namespace step {

enum class grid_orientation
{
  orthogonal,
  isometric
};

struct grid final
{
  grid_orientation orientation;
  int width;
  int height;
};

inline void from_json(const json& json, grid& grid)
{
  json.at("width").get_to(grid.width);
  json.at("height").get_to(grid.height);
  json.at("orientation").get_to(grid.orientation);
}

NLOHMANN_JSON_SERIALIZE_ENUM(grid_orientation,
                             {{grid_orientation::orthogonal, "orthogonal"},
                              {grid_orientation::isometric, "isometric"}})

}  // namespace step

#endif  // STEP_GRID_HEADER
