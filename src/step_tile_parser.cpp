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

#ifndef STEP_TILE_PARSER_SOURCE
#define STEP_TILE_PARSER_SOURCE

#include "step_api.h"
#include "step_layer.h"
#include "step_tile.h"
#include "step_utils.h"

namespace step {

STEP_DEF
void from_json(const JSON& json, Tile& tile)
{
  json.at("id").get_to(tile.m_id);

  detail::safe_bind(json, "properties", tile.m_properties);

  if (json.contains("terrain")) {
    tile.m_terrain.emplace();  // TODO test this terrain stuff
    for (const auto& [key, value] : json.at("terrain").items()) {
      const auto index = static_cast<size_t>(std::stoi(key));
      tile.m_terrain->at(index) = value.get<int>();
    }
  }

  if (json.contains("objectgroup")) {
    // TODO ...
    //    tile.m_objectGroup = std::make_unique<Layer>();
    //    json.at("objectgroup").get_to(*tile.m_objectGroup);
  }

  detail::bind_maybe(json, "animation", tile.m_animation);
  detail::bind_maybe(json, "type", tile.m_type);
  detail::bind_maybe(json, "image", tile.m_image);
  detail::bind_maybe(json, "imagewidth", tile.m_imageWidth);
  detail::bind_maybe(json, "imageheight", tile.m_imageHeight);
  detail::bind_maybe(json, "probability", tile.m_probability);
}

}  // namespace step

#endif  // STEP_TILE_PARSER_SOURCE
