#include "step_grid.hpp"

namespace step {

void from_json(const json& json, Grid& grid)  // FIXME
{
  json.at("width").get_to(grid.m_width);
  json.at("height").get_to(grid.m_height);
  json.at("orientation").get_to(grid.m_orientation);
}

}  // namespace step
