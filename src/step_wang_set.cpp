#include "step_wang_set.hpp"

namespace step {
namespace {

using WangColors = std::vector<WangColor>;
using WangTiles = std::vector<WangTile>;

}  // namespace

WangSet::WangSet(const json& json)
    : m_cornerColors{detail::fill<WangColors>(json, "cornercolors")},
      m_edgeColors{detail::fill<WangColors>(json, "edgecolors")},
      m_wangTiles{detail::fill<WangTiles>(json, "wangtiles")},
      m_properties{json.at("properties")},
      m_name{json.at("name").get<std::string>()},
      m_tile{json.at("tile").get<int>()}
{}

const std::vector<WangColor>& WangSet::corner_colors() const
{
  return m_cornerColors;
}

const std::vector<WangColor>& WangSet::edge_colors() const
{
  return m_edgeColors;
}

const std::vector<WangTile>& WangSet::wang_tiles() const
{
  return m_wangTiles;
}

const Properties& WangSet::properties() const
{
  return m_properties;
}

const std::string& WangSet::name() const
{
  return m_name;
}

local_id WangSet::tile_id() const noexcept
{
  return m_tile;
}

}  // namespace step
