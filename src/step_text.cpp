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

#ifndef STEP_TEXT_SOURCE
#define STEP_TEXT_SOURCE

#include <step_text.h>

#include "step_exception.h"

namespace step {

STEP_DEF
Text::Text(const JSON& json)
{
  if (!json.count("text")) {
    throw StepException{"Text > Missing \"text\" attribute!"};
  }

  for (const auto& [key, value] : json.items()) {
    if (key == "text") {
      m_text = value.get<std::string>();

    } else if (key == "fontfamily") {
      m_fontFamily = value.get<std::string>();

    } else if (key == "color") {
      m_color = Color{value.get<std::string>()};

    } else if (key == "halign") {
      m_halign = value.get<HAlign>();

    } else if (key == "valign") {
      m_valign = value.get<VAlign>();

    } else if (key == "pixelsize") {
      m_pixelSize = value.get<int>();

    } else if (key == "bold") {
      m_bold = value.get<bool>();

    } else if (key == "italic") {
      m_italic = value.get<bool>();

    } else if (key == "kerning") {
      m_kerning = value.get<bool>();

    } else if (key == "strikeout") {
      m_strikeout = value.get<bool>();

    } else if (key == "underline") {
      m_underline = value.get<bool>();

    } else if (key == "wrap") {
      m_wrap = value.get<bool>();
    }
  }
}

}  // namespace step

#endif  // STEP_TEXT_SOURCE
