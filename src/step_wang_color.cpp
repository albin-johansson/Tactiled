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

#ifndef STEP_WANG_COLOR_SOURCE
#define STEP_WANG_COLOR_SOURCE

#include "step_wang_color.h"

namespace step {

STEP_DEF
WangColor::WangColor(const JSON& json)
{
  json.at("name").get_to(m_name);
  m_color = Color{json.at("color").get<std::string>()};
  json.at("tile").get_to(m_tile);
  json.at("probability").get_to(m_probability);
}

STEP_DEF
const std::string& WangColor::name() const
{
  return m_name;
}

STEP_DEF
const Color& WangColor::color() const noexcept
{
  return m_color;
}

STEP_DEF
int WangColor::tile() const noexcept
{
  return m_tile;
}

STEP_DEF
double WangColor::probability() const noexcept
{
  return m_probability;
}

}  // namespace step

#endif  // STEP_WANG_COLOR_SOURCE
