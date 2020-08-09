#include "step_tile.h"

#include "step_layer.h"
#include "step_utils.h"

namespace step {

Tile::Tile(const json& json) : m_id{json.at("id").get<int>()}
{
  m_properties = detail::safe_bind_unique<Properties>(json, "properties");

  if (json.contains("terrain")) {
    m_terrain.emplace();
    for (const auto& [key, value] : json.at("terrain").items()) {
      m_terrain->at(detail::convert<std::size_t>(key)) = value.get<int>();
    }
  }

  if (json.contains("objectgroup")) {
    const auto j = json.at("objectgroup");
    m_objectGroup = std::make_shared<Layer>(j);
  }

  detail::emplace_opt(json, "animation", m_animation);

  detail::bind_opt(json, "type", m_type);
  detail::bind_opt(json, "image", m_image);
  detail::bind_opt(json, "imagewidth", m_imageWidth);
  detail::bind_opt(json, "imageheight", m_imageHeight);
  detail::bind_opt(json, "probability", m_probability);
}

local_id Tile::id() const noexcept
{
  return m_id;
}

std::optional<Animation> Tile::animation() const noexcept
{
  return m_animation;
}

const Properties* Tile::properties() const
{
  return m_properties.get();
}

std::shared_ptr<Layer> Tile::object_group() const noexcept
{
  return m_objectGroup;
}

std::optional<std::string> Tile::type() const
{
  return m_type;
}

std::optional<std::string> Tile::image() const
{
  return m_image;
}

std::optional<int> Tile::image_width() const noexcept
{
  return m_imageWidth;
}

std::optional<int> Tile::image_height() const noexcept
{
  return m_imageHeight;
}

std::optional<double> Tile::probability() const noexcept
{
  return m_probability;
}

std::optional<int> Tile::terrain_at(TerrainPos position) const noexcept
{
  if (m_terrain) {
    return m_terrain->at(static_cast<std::size_t>(position));
  } else {
    return std::nullopt;
  }
}

}  // namespace step
