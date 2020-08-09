#include "step_terrain.h"

#include "step_utils.h"

namespace step {

Terrain::Terrain(const JSON& json)
    : m_tile{json.at("tile").get<int>()},
      m_name{json.at("name").get<std::string>()}
{
  if (json.contains("properties")) {
    m_properties = std::make_unique<Properties>(json.at("properties"));
  }
}

LocalID Terrain::tile() const noexcept
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
