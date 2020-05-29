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

#ifndef STEP_TILE_LAYER_SOURCE
#define STEP_TILE_LAYER_SOURCE

#include "step_tile_layer.h"

#include "step_utils.h"

namespace step {

STEP_DEF
TileLayer::Encoding TileLayer::encoding() const noexcept
{
  return m_encoding;
}

STEP_DEF
TileLayer::Compression TileLayer::compression() const noexcept
{
  return m_compression;
}

STEP_DEF
const detail::Data& TileLayer::data() const noexcept
{
  return m_data;
}

STEP_DEF
const std::vector<Chunk>& TileLayer::chunks() const noexcept
{
  return m_chunks;
}

STEP_DEF
void from_json(const JSON& json, TileLayer& layer)
{
  detail::safe_bind(json, "compression", layer.m_compression);
  detail::safe_bind(json, "encoding", layer.m_encoding);
  if (json.contains("data")) {
    json.at("data").get_to(layer.m_data);
  }
  if (json.contains("chunks") && json.at("chunks").is_array()) {
    for (const auto& [key, value] : json.at("chunks").items()) {
      layer.m_chunks.emplace_back(value);
    }
  }
}

}  // namespace step

#endif  // STEP_TILE_LAYER_SOURCE
