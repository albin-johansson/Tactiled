#ifndef STEP_IMAGE_LAYER_HEADER
#define STEP_IMAGE_LAYER_HEADER

#include <optional>  // optional
#include <string>    // string

#include "color.hpp"
#include "common.hpp"

namespace step {

struct image_layer final
{
  std::string image;
  std::optional<color> color;
};

inline void from_json(const json& json, image_layer& layer)
{
  json.at("image").get_to(layer.image);
  if (json.count("transparentcolor")) {
    layer.color = color{json.at("transparentcolor").get<std::string>()};
  }
}

}  // namespace step

#endif  // STEP_IMAGE_LAYER_HEADER
