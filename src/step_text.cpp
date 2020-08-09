#include "step_text.h"

#include "step_exception.h"

namespace step {

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
      m_halign = value.get<Text::HAlign>();

    } else if (key == "valign") {
      m_valign = value.get<Text::VAlign>();

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
