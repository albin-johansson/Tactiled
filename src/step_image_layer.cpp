#include "step_image_layer.h"

namespace step {

std::string ImageLayer::image() const
{
  return m_image;
}

std::optional<Color> ImageLayer::transparent_color() const noexcept
{
  return m_transparentColor;
}

void from_json(const JSON& json, ImageLayer& layer)  // FIXME
{
  json.at("image").get_to(layer.m_image);
  if (json.count("transparentcolor")) {
    layer.m_transparentColor =
        Color{json.at("transparentcolor").get<std::string>()};
  }
}

}  // namespace step
