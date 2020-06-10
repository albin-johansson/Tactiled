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

#ifndef STEP_WANG_SET_SOURCE
#define STEP_WANG_SET_SOURCE

#include "step_wang_set.h"

namespace step {

STEP_DEF
WangSet::WangSet(const JSON& json)
{
  json.at("name").get_to(m_name);
  json.at("tile").get_to(m_tile);
  json.at("properties").get_to(m_properties);

  for (const auto& [key, value] : json.at("cornercolors").items()) {
    m_cornerColors.emplace_back(value);
  }

  for (const auto& [key, value] : json.at("edgecolors").items()) {
    m_edgeColors.emplace_back(value);
  }

  for (const auto& [key, value] : json.at("wangtiles").items()) {
    m_wangTiles.emplace_back(value);
  }
}

STEP_DEF
const std::vector<WangColor>& WangSet::corner_colors() const
{
  return m_cornerColors;
}

STEP_DEF
const std::vector<WangColor>& WangSet::edge_colors() const
{
  return m_edgeColors;
}

STEP_DEF
const std::vector<WangTile>& WangSet::wang_tiles() const
{
  return m_wangTiles;
}

STEP_DEF
const Properties& WangSet::properties() const
{
  return m_properties;
}

STEP_DEF
const std::string& WangSet::name() const
{
  return m_name;
}

STEP_DEF
int WangSet::tile_id() const noexcept
{
  return m_tile;
}

}  // namespace step

#endif  // STEP_WANG_SET_SOURCE
