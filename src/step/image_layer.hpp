#ifndef STEP_IMAGE_LAYER_HEADER
#define STEP_IMAGE_LAYER_HEADER

#include <string>

#include "color.hpp"
#include "step_api.hpp"
#include "types.hpp"

namespace step {

/**
 * @class image_layer
 *
 * @brief Represents the API for layers that represent "image layers", layers
 * that are represented by an image.
 *
 * @since 0.1.0
 *
 * @headerfile step_image_layer.hpp
 */
class image_layer final
{
 public:
  friend void from_json(const json&, image_layer&);

  /**
   * @brief Returns the image used by the image layer.
   *
   * @return the image associated with the image layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image() const -> const std::string&
  {
    return m_image;
  }

  /**
   * @brief Returns the transparent color used by the image layer.
   *
   * @details This property is optional.
   *
   * @return the transparent color used by the image layer; `std::nullopt` if
   * there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto transparent_color() const noexcept
      -> const std::optional<color>&
  {
    return m_transparentColor;
  }

 private:
  std::string m_image;
  std::optional<color> m_transparentColor;
};

inline void from_json(const json& json, image_layer& layer)
{
  json.at("image").get_to(layer.m_image);
  if (json.count("transparentcolor")) {
    layer.m_transparentColor =
        color{json.at("transparentcolor").get<std::string>()};
  }
}

}  // namespace step

#endif  // STEP_IMAGE_LAYER_HEADER
