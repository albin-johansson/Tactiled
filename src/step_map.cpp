#include "step_map.hpp"

#include "step_exception.hpp"
#include "step_utils.hpp"

namespace step {

Map::Map(const fs::path& path)
{
  auto parent = path.parent_path();
  parent += fs::path::preferred_separator;

  parse(parent.string(), detail::parse_json(path.string()));
}

Map::Map(std::string_view root, std::string_view file)
{
  std::string map{root.data()};
  map += file;
  parse(root, detail::parse_json(map));
}

void Map::parse(std::string_view root, const json& json)
{
  if (!json.contains("type") || json.at("type") != "map") {
    throw step_exception{R"(Map > "type" attribute must be "map"!)"};
  }

  json.at("width").get_to(m_width);
  json.at("height").get_to(m_height);
  json.at("tilewidth").get_to(m_tileWidth);
  json.at("tileheight").get_to(m_tileHeight);
  json.at("infinite").get_to(m_infinite);
  json.at("nextlayerid").get_to(m_nextLayerID);
  json.at("nextobjectid").get_to(m_nextObjectID);
  json.at("orientation").get_to(m_orientation);
  json.at("version").get_to(m_jsonVersion);
  json.at("tiledversion").get_to(m_tiledVersion);

  if (json.contains("properties")) {
    m_properties = std::make_unique<properties>(json.at("properties"));
  }

  detail::safe_bind(json, "renderorder", m_renderOrder);
  detail::safe_bind(json, "staggeraxis", m_staggerAxis);
  detail::safe_bind(json, "staggerindex", m_staggerIndex);
  detail::safe_bind(json, "hexSideLength", m_hexSideLength);

  if (json.contains("backgroundColor")) {
    m_backgroundColor = color{json.at("backgroundColor").get<std::string>()};
  }

  for (const auto& [key, value] : json.at("layers").items()) {
    m_layers.emplace_back(value);
  }

  for (const auto& [key, value] : json.at("tilesets").items()) {
    if (value.contains("source")) {
      const auto firstgid = global_id{value.at("firstgid").get<unsigned>()};
      const auto src = value.at("source").get<std::string>();
      m_tilesets.push_back(Tileset::external(root, firstgid, src.data()));
    } else {
      m_tilesets.push_back(Tileset::embedded(value));
    }
  }
}

int Map::width() const noexcept
{
  return m_width;
}

int Map::height() const noexcept
{
  return m_height;
}

int Map::tile_width() const noexcept
{
  return m_tileWidth;
}

int Map::tile_height() const noexcept
{
  return m_tileHeight;
}

int Map::next_layer_id() const noexcept
{
  return m_nextLayerID;
}

int Map::next_object_id() const noexcept
{
  return m_nextObjectID;
}

const std::vector<layer>& Map::layers() const noexcept
{
  return m_layers;
}

const std::vector<Tileset>& Map::tilesets() const noexcept
{
  return m_tilesets;
}

const properties* Map::get_properties() const noexcept
{
  return m_properties.get();
}

Map::Orientation Map::orientation() const noexcept
{
  return m_orientation;
}

Map::RenderOrder Map::render_order() const noexcept
{
  return m_renderOrder;
}

Map::StaggerAxis Map::stagger_axis() const noexcept
{
  return m_staggerAxis;
}

Map::StaggerIndex Map::stagger_index() const noexcept
{
  return m_staggerIndex;
}

bool Map::infinite() const noexcept
{
  return m_infinite;
}

int Map::hex_side_length() const noexcept
{
  return m_hexSideLength;
}

std::optional<color> Map::background_color() const noexcept
{
  return m_backgroundColor;
}

double Map::json_version() const noexcept
{
  return m_jsonVersion;
}

std::string Map::tiled_version() const
{
  return m_tiledVersion;
}

}  // namespace step
