#include "step_terrain.hpp"

#include "step_utils.hpp"

namespace step {

Terrain::Terrain(const json& json)
    : m_tile{json.at("tile").get<int>()},
      m_name{json.at("name").get<std::string>()}
{
  if (json.contains("properties")) {
    m_properties = std::make_unique<Properties>(json.at("properties"));
  }
}

local_id Terrain::tile() const noexcept
{
  return m_tile;
}

std::string Terrain::name() const
{
  return m_name;
}

const Properties* Terrain::properties() const noexcept
{
  return m_properties.get();
}

}  // namespace step
