#include "step_terrain.hpp"

#include "step_utils.hpp"

namespace step {

Terrain::Terrain(const json& json)
    : m_tile{json.at("tile").get<int>()},
      m_name{json.at("name").get<std::string>()}
{
  if (const auto it = json.find("properties"); it != json.end()) {
    m_properties = std::make_unique<properties>(*it);
  }
}

auto Terrain::tile() const noexcept -> local_id
{
  return m_tile;
}

auto Terrain::name() const -> std::string
{
  return m_name;
}

auto Terrain::get_properties() const noexcept -> const properties*
{
  return m_properties.get();
}

}  // namespace step
