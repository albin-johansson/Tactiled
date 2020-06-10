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

#ifndef STEP_WANG_TILE_SOURCE
#define STEP_WANG_TILE_SOURCE

#include "step_wang_tile.h"

namespace step {

STEP_DEF
WangTile::WangTile(const JSON& json)
{
  json.at("tileid").get_to(m_tileID);
  json.at("wangid").get_to(m_wangColorIndices);
  json.at("dflip").get_to(m_flippedDiagonally);
  json.at("hflip").get_to(m_flippedHorizontally);
  json.at("vflip").get_to(m_flippedVertically);
}

STEP_DEF
int WangTile::tile_id() const noexcept
{
  return m_tileID;
}

STEP_DEF
const std::array<int, 8>& WangTile::wang_color_indices() const
{
  return m_wangColorIndices;
}

STEP_DEF
bool WangTile::flipped_diagonally() const noexcept
{
  return m_flippedDiagonally;
}

STEP_DEF
bool WangTile::flipped_horizontally() const noexcept
{
  return m_flippedHorizontally;
}

STEP_DEF
bool WangTile::flipped_vertically() const noexcept
{
  return m_flippedVertically;
}

}  // namespace step

#endif  // STEP_WANG_TILE_SOURCE
