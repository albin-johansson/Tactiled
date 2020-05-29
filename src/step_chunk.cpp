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

#ifndef STEP_CHUNK_SOURCE
#define STEP_CHUNK_SOURCE

#include "step_chunk.h"

namespace step {

STEP_DEF
int Chunk::x() const noexcept
{
  return m_x;
}

STEP_DEF
int Chunk::y() const noexcept
{
  return m_y;
}

STEP_DEF
int Chunk::width() const noexcept
{
  return m_width;
}

STEP_DEF
int Chunk::height() const noexcept
{
  return m_height;
}

STEP_DEF
const detail::Data& Chunk::data() const noexcept
{
  return m_data;
}

STEP_DEF
void from_json(const JSON& json, Chunk& chunk)
{
  json.at("x").get_to(chunk.m_x);
  json.at("y").get_to(chunk.m_y);
  json.at("width").get_to(chunk.m_width);
  json.at("height").get_to(chunk.m_height);
  json.at("data").get_to(chunk.m_data);
}

}  // namespace step

#endif  // STEP_CHUNK_SOURCE
