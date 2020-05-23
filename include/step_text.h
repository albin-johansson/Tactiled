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

#ifndef STEP_TEXT_HEADER
#define STEP_TEXT_HEADER

#include <memory>
#include <string>

#include "step_api.h"
#include "step_color.h"
#include "step_types.h"

namespace step {

class Text final {
 public:
  enum class HAlign { Center, Right, Left, Justify };
  enum class VAlign { Center, Bottom, Top };

  STEP_API explicit Text(const JSONValue& json);

  [[nodiscard]] std::string text() const { return m_text; };

  [[nodiscard]] std::string font_family() const { return m_fontFamily; }

  [[nodiscard]] Color color() const noexcept { return m_color; }

  [[nodiscard]] HAlign horizontal_alignment() const noexcept
  {
    return m_halign;
  }

  [[nodiscard]] VAlign vertical_alignment() const noexcept { return m_valign; }

  [[nodiscard]] int pixel_size() const noexcept { return m_pixelSize; }

  [[nodiscard]] bool bold() const noexcept { return m_bold; }

  [[nodiscard]] bool italic() const noexcept { return m_italic; }

  [[nodiscard]] bool kerning() const noexcept { return m_kerning; }

  [[nodiscard]] bool strikeout() const noexcept { return m_strikeout; }

  [[nodiscard]] bool underline() const noexcept { return m_underline; }

  [[nodiscard]] bool wrap() const noexcept { return m_wrap; }

 private:
  std::string m_text;
  std::string m_fontFamily = "sans-serif";
  Color m_color;
  HAlign m_halign = HAlign::Left;
  VAlign m_valign = VAlign::Top;
  int m_pixelSize = 16;
  bool m_bold = false;
  bool m_italic = false;
  bool m_kerning = true;
  bool m_strikeout = false;
  bool m_underline = false;
  bool m_wrap = false;
};

STEP_SERIALIZE_ENUM(Text::HAlign,
                    {{Text::HAlign::Center, "center"},
                     {Text::HAlign::Right, "right"},
                     {Text::HAlign::Left, "left"},
                     {Text::HAlign::Justify, "justify"}})

STEP_SERIALIZE_ENUM(Text::VAlign,
                    {{Text::VAlign::Center, "center"},
                     {Text::VAlign::Top, "top"},
                     {Text::VAlign::Bottom, "bottom"}})
}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_text.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TEXT_HEADER
