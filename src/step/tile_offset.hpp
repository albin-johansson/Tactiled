#ifndef STEP_TILE_OFFSET_HEADER
#define STEP_TILE_OFFSET_HEADER

#include "step_api.hpp"
#include "types.hpp"

namespace step {

/**
 * @class tile_offset
 *
 * @brief Provides offsets in pixels that are to be applied when rendering a
 * tile from a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tile_offset.hpp
 */
class tile_offset final
{
 public:
  explicit tile_offset(const json& json)
      : m_x{json.at("x").get<int>()}
      , m_y{json.at("y").get<int>()}
  {}

  /**
   * @brief Returns the offset in the x-axis associated with the tile offset
   * instance.
   *
   * @return the offset in the x-axis.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    return m_x;
  }

  /**
   * @brief Returns the offset in the y-axis associated with the tile offset
   * instance.
   *
   * @return the offset in the y-axis.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    return m_y;
  }

 private:
  int m_x;
  int m_y;
};

}  // namespace step

#endif  // STEP_TILE_OFFSET_HEADER
