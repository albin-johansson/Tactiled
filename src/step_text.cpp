#include "step_text.hpp"

#include "step_exception.hpp"

namespace step {

text::text(const json& json)
{
  if (!json.count("text")) {
    throw step_exception{"Text > Missing \"text\" attribute!"};
  }

  for (const auto& [key, value] : json.items()) {
    if (key == "text") {
      m_text = value.get<std::string>();

    } else if (key == "fontfamily") {
      m_fontFamily = value.get<std::string>();

    } else if (key == "color") {
      m_color = Color{value.get<std::string>()};

    } else if (key == "halign") {
      m_halign = value.get<text::halign>();

    } else if (key == "valign") {
      m_valign = value.get<text::valign>();

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

auto text::get_text() const -> std::string
{
  return m_text;
}

auto text::font_family() const -> std::string
{
  return m_fontFamily;
}

auto text::color() const noexcept -> Color
{
  return m_color;
}

auto text::horizontal_alignment() const noexcept -> text::halign
{
  return m_halign;
}

auto text::vertical_alignment() const noexcept -> text::valign
{
  return m_valign;
}

auto text::pixel_size() const noexcept -> int
{
  return m_pixelSize;
}

auto text::bold() const noexcept -> bool
{
  return m_bold;
}

auto text::italic() const noexcept -> bool
{
  return m_italic;
}

auto text::kerning() const noexcept -> bool
{
  return m_kerning;
}

auto text::strikeout() const noexcept -> bool
{
  return m_strikeout;
}

auto text::underline() const noexcept -> bool
{
  return m_underline;
}

auto text::wrap() const noexcept -> bool
{
  return m_wrap;
}

}  // namespace step
