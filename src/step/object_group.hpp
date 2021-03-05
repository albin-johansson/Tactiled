#ifndef STEP_OBJECT_GROUP_HEADER
#define STEP_OBJECT_GROUP_HEADER

#include <vector>

#include "common.hpp"
#include "object.hpp"
#include "step_api.hpp"

namespace step {

/**
 * \class object_group
 *
 * \brief Represents the API for layers that represent "object groups", that
 * hold data about various objects in a tile map.
 *
 * \todo begin, end, remove objects-getter
 *
 * \since 0.1.0
 *
 * \headerfile step_object_group.hpp
 */
class object_group final
{
 public:
  /**
   * \enum object_group::draw_order
   *
   * \brief Provides hints for how rendering should be performed of layers.
   *
   * \since 0.1.0
   */
  enum class draw_order
  {
    top_down,
    index
  };

  explicit object_group(const json& json) : m_drawOrder{json.at("draworder")}
  {
    m_objects.reserve(json.size());
    for (const auto& [key, value] : json.at("objects").items()) {
      m_objects.emplace_back(value);
    }
  }

  /**
   * \brief Returns the draw order used by the object group.
   *
   * \details The default value of this property is `top_down`.
   *
   * \return the draw order used by the object group.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_draw_order() const noexcept -> draw_order
  {
    return m_drawOrder;
  }

  /**
   * \brief Returns the objects contained in the object group.
   *
   * \return the objects contained in the object group.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto objects() const -> const std::vector<object>&
  {
    return m_objects;
  }

 private:
  draw_order m_drawOrder{draw_order::top_down};
  std::vector<object> m_objects;
};

NLOHMANN_JSON_SERIALIZE_ENUM(object_group::draw_order,
                             {{object_group::draw_order::index, "index"},
                              {object_group::draw_order::top_down, "topdown"}})

}  // namespace step

#endif  // STEP_OBJECT_GROUP_HEADER
