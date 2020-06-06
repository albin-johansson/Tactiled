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

#ifndef STEP_TILED_MAP_SOURCE
#define STEP_TILED_MAP_SOURCE

#include "step_map.h"

#include <iostream>

#include "step_exception.h"
#include "step_utils.h"

namespace step {

STEP_DEF
Map::Map(std::string_view root, std::string_view file)
{
  std::string map = root.data();
  map += file;
  parse(root, detail::parse_json(map));
}

STEP_DEF
void Map::parse(std::string_view root, const JSON& json)
{
  if (!json.contains("type") || json.at("type") != "map") {
    throw StepException{"Map > \"type\" attribute must be \"map\"!"};
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

  detail::safe_bind(json, "properties", m_properties);
  detail::safe_bind(json, "renderorder", m_renderOrder);
  detail::safe_bind(json, "staggeraxis", m_staggerAxis);
  detail::safe_bind(json, "staggerindex", m_staggerIndex);
  detail::safe_bind(json, "hexSideLength", m_hexSideLength);

  if (json.contains("backgroundColor")) {
    m_backgroundColor = Color{json.at("backgroundColor").get<std::string>()};
  }

  for (const auto& [key, value] : json.at("layers").items()) {
    auto& layer = m_layers.emplace_back();
    value.get_to(layer);
  }

  for (const auto& [key, value] : json.at("tilesets").items()) {
    if (value.contains("source")) {
      const auto firstgid = value.at("firstgid").get<int>();
      const auto src = value.at("source").get<std::string>();
      m_tilesets.push_back(Tileset::external(root, firstgid, src.data()));
    } else {
      m_tilesets.push_back(Tileset::embedded(value));
    }
  }
}

STEP_DEF
int Map::width() const noexcept
{
  return m_width;
}

STEP_DEF
int Map::height() const noexcept
{
  return m_height;
}

STEP_DEF
int Map::tile_width() const noexcept
{
  return m_tileWidth;
}

STEP_DEF
int Map::tile_height() const noexcept
{
  return m_tileHeight;
}

STEP_DEF
int Map::next_layer_id() const noexcept
{
  return m_nextLayerID;
}

STEP_DEF
int Map::next_object_id() const noexcept
{
  return m_nextObjectID;
}

STEP_DEF
const std::vector<Layer>& Map::layers() const noexcept
{
  return m_layers;
}

STEP_DEF
const std::vector<Tileset>& Map::tilesets() const noexcept
{
  return m_tilesets;
}

STEP_DEF
const Properties& Map::properties() const noexcept
{
  return m_properties;
}

STEP_DEF
Map::Orientation Map::orientation() const noexcept
{
  return m_orientation;
}

STEP_DEF
Map::RenderOrder Map::render_order() const noexcept
{
  return m_renderOrder;
}

STEP_DEF
Map::StaggerAxis Map::stagger_axis() const noexcept
{
  return m_staggerAxis;
}

STEP_DEF
Map::StaggerIndex Map::stagger_index() const noexcept
{
  return m_staggerIndex;
}

STEP_DEF
bool Map::infinite() const noexcept
{
  return m_infinite;
}

STEP_DEF
int Map::hex_side_length() const noexcept
{
  return m_hexSideLength;
}

STEP_DEF
Maybe<Color> Map::background_color() const noexcept
{
  return m_backgroundColor;
}

STEP_DEF
double Map::json_version() const noexcept
{
  return m_jsonVersion;
}

STEP_DEF
std::string Map::tiled_version() const
{
  return m_tiledVersion;
}

}  // namespace step

#endif  // STEP_TILED_MAP_SOURCE
