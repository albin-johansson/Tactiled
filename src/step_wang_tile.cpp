#include "step_wang_tile.h"

namespace step {

WangTile::WangTile(const JSON& json) : m_tileID{json.at("tileid").get<int>()}
{
  json.at("wangid").get_to(m_wangColorIndices);
  json.at("dflip").get_to(m_flippedDiagonally);
  json.at("hflip").get_to(m_flippedHorizontally);
  json.at("vflip").get_to(m_flippedVertically);
}

LocalID WangTile::tile_id() const noexcept
{
  return m_tileID;
}

const std::array<int, 8>& WangTile::wang_color_indices() const
{
  return m_wangColorIndices;
}

bool WangTile::flipped_diagonally() const noexcept
{
  return m_flippedDiagonally;
}

bool WangTile::flipped_horizontally() const noexcept
{
  return m_flippedHorizontally;
}

bool WangTile::flipped_vertically() const noexcept
{
  return m_flippedVertically;
}

}  // namespace step
