#include "step_tileset.hpp"

#include "step_exception.hpp"
#include "step_utils.hpp"

namespace step {

Tileset::Tileset(std::string_view root, global_id id, std::string_view path)
    : m_firstGID{id}, m_source{path.data()}
{
  std::string fullPath{root.data()};
  fullPath += path.data();
  parse(detail::parse_json(fullPath));
}

Tileset::Tileset(const json& json)
{
  parse(json);
}

Tileset Tileset::embedded(const json& json)
{
  return Tileset{json};
}

Tileset Tileset::external(std::string_view root,
                          global_id id,
                          std::string_view src)
{
  return {root, id, src};
}

void Tileset::parse(const json& json)
{
  if (json.at("type").get<std::string>() != "tileset") {
    throw StepException{"Tileset > \"type\" must be \"tileset\"!"};
  }

  json.at("tilewidth").get_to(m_tileWidth);
  json.at("tileheight").get_to(m_tileHeight);
  json.at("tilecount").get_to(m_tileCount);
  json.at("columns").get_to(m_nColumns);
  json.at("imagewidth").get_to(m_imageWidth);
  json.at("imageheight").get_to(m_imageHeight);
  json.at("margin").get_to(m_margin);
  json.at("spacing").get_to(m_spacing);
  json.at("image").get_to(m_image);
  json.at("name").get_to(m_name);

  if (json.contains("firstgid")) {
    m_firstGID = global_id{json.at("firstgid").get<unsigned>()};
  }

  if (json.contains("properties")) {
    m_properties = std::make_unique<Properties>(json.at("properties"));
  }

  detail::safe_bind(json, "tiledversion", m_tiledVersion);
  detail::safe_bind(json, "version", m_jsonVersion);

  detail::bind_opt(json, "grid", m_grid);
  detail::emplace_opt(json, "tileoffset", m_tileOffset);

  if (json.contains("tiles") && json.at("tiles").is_array()) {
    for (const auto& [key, value] : json.at("tiles").items()) {
      m_tiles.emplace_back(value);
    }
  }

  if (json.contains("terrains") && json.at("terrains").is_array()) {
    m_terrains = detail::fill<std::vector<Terrain>>(json, "terrains");
  }

  if (json.contains("wangsets") && json.at("wangsets").is_array()) {
    for (const auto& [key, value] : json.at("wangsets").items()) {
      m_wangSets.emplace_back(value);
    }
  }

  if (json.contains("backgroundcolor")) {
    m_backgroundColor = Color{json.at("backgroundcolor").get<std::string>()};
  }

  if (json.contains("transparentcolor")) {
    m_transparentColor = Color{json.at("transparentcolor").get<std::string>()};
  }
}

global_id Tileset::first_gid() const noexcept
{
  return m_firstGID;
}

int Tileset::tile_width() const noexcept
{
  return m_tileWidth;
}

int Tileset::tile_height() const noexcept
{
  return m_tileHeight;
}

int Tileset::tile_count() const noexcept
{
  return m_tileCount;
}

int Tileset::columns() const noexcept
{
  return m_nColumns;
}

int Tileset::image_width() const noexcept
{
  return m_imageWidth;
}

int Tileset::image_height() const noexcept
{
  return m_imageHeight;
}

int Tileset::margin() const noexcept
{
  return m_margin;
}

int Tileset::spacing() const noexcept
{
  return m_spacing;
}

const std::vector<tile>& Tileset::tiles() const noexcept
{
  return m_tiles;
}

const std::vector<WangSet>& Tileset::wang_sets() const
{
  return m_wangSets;
}

const Properties* Tileset::properties() const noexcept
{
  return m_properties.get();
}

const std::vector<Terrain>& Tileset::terrains() const noexcept
{
  return m_terrains;
}

std::string Tileset::source() const
{
  return m_source;
}

std::string Tileset::image() const
{
  return m_image;
}

std::string Tileset::name() const
{
  return m_name;
}

std::optional<Color> Tileset::background_color() const noexcept
{
  return m_backgroundColor;
}

std::optional<Color> Tileset::transparent_color() const noexcept
{
  return m_transparentColor;
}

std::optional<Grid> Tileset::grid() const noexcept
{
  return m_grid;
}

std::optional<TileOffset> Tileset::tile_offset() const noexcept
{
  return m_tileOffset;
}

std::string Tileset::tiled_version() const
{
  return m_tiledVersion;
}

double Tileset::json_version() const noexcept
{
  return m_jsonVersion;
}

}  // namespace step
