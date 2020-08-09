#include "step_tile_offset.h"

namespace step {

TileOffset::TileOffset(const JSON& json)
    : m_x{json.at("x").get<int>()}, m_y{json.at("y").get<int>()}
{}

int TileOffset::x() const noexcept
{
  return m_x;
}

int TileOffset::y() const noexcept
{
  return m_y;
}

}  // namespace step
