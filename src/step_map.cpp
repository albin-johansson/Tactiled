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

#include "step_utils.h"

namespace step {

STEP_DEF
bool Map::infinite() const noexcept
{
  return m_infinite;
}

STEP_DEF
void from_json(const JSON& json, Map& map)
{
  json.at("width").get_to(map.m_width);
  json.at("height").get_to(map.m_height);
  json.at("tilewidth").get_to(map.m_tileWidth);
  json.at("tileheight").get_to(map.m_tileHeight);
  json.at("infinite").get_to(map.m_infinite);
  json.at("nextlayerid").get_to(map.m_nextLayerID);
  json.at("nextobjectid").get_to(map.m_nextObjectID);
  json.at("orientation").get_to(map.m_orientation);
  json.at("version").get_to(map.m_jsonVersion);
  json.at("tiledversion").get_to(map.m_tiledVersion);

  detail::safe_bind(json, "properties", map.m_properties);
  detail::safe_bind(json, "renderorder", map.m_renderOrder);
  detail::safe_bind(json, "staggeraxis", map.m_staggerAxis);
  detail::safe_bind(json, "staggerindex", map.m_staggerIndex);
  detail::safe_bind(json, "hexSideLength", map.m_hexSideLength);

  if (json.contains("backgroundColor")) {
    map.m_backgroundColor =
        Color{json.at("backgroundColor").get<std::string>()};
  }

  for (const auto& [key, value] : json.at("layers").items()) {
    auto& layer = map.m_layers.emplace_back();
    value.get_to(layer);
  }

  for (const auto& [key, value] : json.at("tilesets").items()) {
    auto& tileset = map.m_tilesets.emplace_back();
    value.get_to(tileset);
  }
}

}  // namespace step

#endif  // STEP_TILED_MAP_SOURCE
