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

#ifndef TACTILED_COLOR_SOURCE
#define TACTILED_COLOR_SOURCE

#include "tactiled_color.h"

#include "tactiled_exception.h"

namespace tactiled {
namespace {

uint8_t from_hex(const std::string& str)
{
  try {
    return static_cast<uint8_t>(std::stoul(str, nullptr, 16));
  } catch (...) {
    throw TactiledException{"Failed to convert hex string to value!"};
  }
}

}  // namespace

TACTILED_DEF
Color::Color(const std::string& value)
{
  const auto len = value.length();
  if (len == 6 || len == 8) {
    // TODO this feature could be added to CTN 4.1
    m_red = from_hex(value.substr(0, 2));
    m_green = from_hex(value.substr(2, 2));
    m_blue = from_hex(value.substr(4, 2));
    if (len == 8) {
      m_alpha = from_hex(value.substr(6, 2));
    }
  } else {
    throw TactiledException{"Couldn't create color from color string!"};
  }
}

}  // namespace tactiled

#endif  // TACTILED_COLOR_SOURCE
