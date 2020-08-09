#include "step_tile.hpp"

#include "step_layer.hpp"
#include "step_properties.hpp"
#include "step_utils.hpp"

namespace step {

tile::tile(const json& json) : m_id{json.at("id").get<int>()}
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
    m_objectGroup = std::make_unique<Layer>(j);
  }

  detail::emplace_opt(json, "animation", m_animation);

  detail::bind_opt(json, "type", m_type);
  detail::bind_opt(json, "image", m_image);
  detail::bind_opt(json, "imagewidth", m_imageWidth);
  detail::bind_opt(json, "imageheight", m_imageHeight);
  detail::bind_opt(json, "probability", m_probability);
}

auto tile::id() const noexcept -> local_id
{
  return m_id;
}

auto tile::get_animation() const noexcept -> std::optional<animation>
{
  return m_animation;
}

auto tile::get_properties() const -> const Properties*
{
  return m_properties.get();
}

auto tile::object_group() const noexcept -> const Layer*
{
  return m_objectGroup.get();
}

auto tile::type() const -> std::optional<std::string>
{
  return m_type;
}

auto tile::image() const -> std::optional<std::string>
{
  return m_image;
}

auto tile::image_width() const noexcept -> std::optional<int>
{
  return m_imageWidth;
}

auto tile::image_height() const noexcept -> std::optional<int>
{
  return m_imageHeight;
}

auto tile::probability() const noexcept -> std::optional<double>
{
  return m_probability;
}

auto tile::terrain_at(terrain_pos position) const noexcept -> std::optional<int>
{
  if (m_terrain) {
    return m_terrain->at(static_cast<std::size_t>(position));
  } else {
    return std::nullopt;
  }
}

}  // namespace step
