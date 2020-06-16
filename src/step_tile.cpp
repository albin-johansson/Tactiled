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

#ifndef STEP_TILE_SOURCE
#define STEP_TILE_SOURCE

#include "step_tile.h"

#include "step_layer.h"
#include "step_utils.h"

namespace step {

STEP_DEF
Tile::Tile(const JSON& json) : m_id{json.at("id").get<int>()}
{
  detail::safe_bind(json, "properties", m_properties);

  if (json.contains("terrain")) {
    m_terrain.emplace();
    for (const auto& [key, value] : json.at("terrain").items()) {
      m_terrain->at(detail::convert<std::size_t>(key)) = value.get<int>();
    }
  }

  if (json.contains("objectgroup")) {
    m_objectGroup = std::make_shared<Layer>(json.at("objectgroup"));
  }

  detail::emplace_opt(json, "animation", m_animation);
//  detail::bind_opt(json, "animation", m_animation);
  detail::bind_opt(json, "type", m_type);
  detail::bind_opt(json, "image", m_image);
  detail::bind_opt(json, "imagewidth", m_imageWidth);
  detail::bind_opt(json, "imageheight", m_imageHeight);
  detail::bind_opt(json, "probability", m_probability);
}

STEP_DEF
LocalID Tile::id() const noexcept
{
  return m_id;
}

STEP_DEF
std::optional<Animation> Tile::animation() const noexcept
{
  return m_animation;
}

STEP_DEF
const Properties& Tile::properties() const
{
  return m_properties;
}

STEP_DEF
std::shared_ptr<Layer> Tile::object_group() const noexcept
{
  return m_objectGroup;
}

STEP_DEF
std::optional<std::string> Tile::type() const
{
  return m_type;
}

STEP_DEF
std::optional<std::string> Tile::image() const
{
  return m_image;
}

STEP_DEF
std::optional<int> Tile::image_width() const noexcept
{
  return m_imageWidth;
}

STEP_DEF
std::optional<int> Tile::image_height() const noexcept
{
  return m_imageHeight;
}

STEP_DEF
std::optional<double> Tile::probability() const noexcept
{
  return m_probability;
}

STEP_DEF
std::optional<int> Tile::terrain_at(TerrainPos position) const noexcept
{
  if (m_terrain) {
    return m_terrain->at(static_cast<std::size_t>(position));
  } else {
    return std::nullopt;
  }
}

}  // namespace step

#endif  // STEP_TILE_SOURCE
