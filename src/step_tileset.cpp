/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_TILESET_SOURCE
#define STEP_TILESET_SOURCE

#include "step_tileset.h"

#include "step_exception.h"
#include "step_utils.h"

namespace step {

STEP_DEF
Tileset::Tileset(std::string_view root, int id, std::string_view path)
    : m_firstGID{id}, m_source{path.data()}
{
  std::string fullPath{root.data()};
  fullPath += path.data();
  parse(detail::parse_json(fullPath));
}

STEP_DEF
Tileset::Tileset(const JSON& json)
{
  parse(json);
}

STEP_DEF
Tileset Tileset::embedded(const JSON& json)
{
  return Tileset{json};
}

STEP_DEF
Tileset Tileset::external(std::string_view root, int id, std::string_view src)
{
  return {root, id, src};
}

STEP_DEF
void Tileset::parse(const JSON& json)
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
    m_firstGID = GlobalID{json.at("firstgid").get<unsigned>()};
  }
  detail::safe_bind(json, "properties", m_properties);
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
    for (const auto& [key, value] : json.at("terrains").items()) {
      m_terrains.emplace_back(value.get<Terrain>());
    }
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

STEP_DEF
GlobalID Tileset::first_gid() const noexcept
{
  return m_firstGID;
}

STEP_DEF
int Tileset::tile_width() const noexcept
{
  return m_tileWidth;
}

STEP_DEF
int Tileset::tile_height() const noexcept
{
  return m_tileHeight;
}

STEP_DEF
int Tileset::tile_count() const noexcept
{
  return m_tileCount;
}

STEP_DEF
int Tileset::columns() const noexcept
{
  return m_nColumns;
}

STEP_DEF
int Tileset::image_width() const noexcept
{
  return m_imageWidth;
}

STEP_DEF
int Tileset::image_height() const noexcept
{
  return m_imageHeight;
}

STEP_DEF
int Tileset::margin() const noexcept
{
  return m_margin;
}

STEP_DEF
int Tileset::spacing() const noexcept
{
  return m_spacing;
}

STEP_DEF
const std::vector<Tile>& Tileset::tiles() const noexcept
{
  return m_tiles;
}

STEP_DEF
const std::vector<WangSet>& Tileset::wang_sets() const
{
  return m_wangSets;
}

STEP_DEF
const Properties& Tileset::properties() const noexcept
{
  return m_properties;
}

STEP_DEF
const std::vector<Terrain>& Tileset::terrains() const noexcept
{
  return m_terrains;
}

STEP_DEF
std::string Tileset::source() const
{
  return m_source;
}

STEP_DEF
std::string Tileset::image() const
{
  return m_image;
}

STEP_DEF
std::string Tileset::name() const
{
  return m_name;
}

STEP_DEF
std::optional<Color> Tileset::background_color() const noexcept
{
  return m_backgroundColor;
}

STEP_DEF
std::optional<Color> Tileset::transparent_color() const noexcept
{
  return m_transparentColor;
}

STEP_DEF
std::optional<Grid> Tileset::grid() const noexcept
{
  return m_grid;
}

STEP_DEF
std::optional<TileOffset> Tileset::tile_offset() const noexcept
{
  return m_tileOffset;
}

STEP_DEF
std::string Tileset::tiled_version() const
{
  return m_tiledVersion;
}

STEP_DEF
double Tileset::json_version() const noexcept
{
  return m_jsonVersion;
}

}  // namespace step

#endif  // STEP_TILESET_SOURCE
