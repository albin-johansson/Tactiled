#ifndef STEP_GRID_HEADER
#define STEP_GRID_HEADER

#include "step_api.hpp"
#include "types.hpp"

namespace step {

/**
 * @class grid
 *
 * @brief Provides information about the grid of tiles in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_grid.hpp
 */
class grid final
{
 public:
  /**
   * @enum grid::orientation
   *
   * @brief Provides values for the different possible  orientations of a
   * grid in a tileset.
   *
   * @since 0.1.0
   */
  enum class orientation
  {
    orthogonal,
    isometric
  };

  friend void from_json(const json&, grid&);

  /**
   * @brief Returns the orientation of the grid.
   *
   * @details The default value of this property is `Orthogonal`.
   *
   * @return the orientation of the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_orientation() const noexcept -> orientation
  {
    return m_orientation;
  }

  /**
   * @brief Returns the width of the cells in the grid.
   *
   * @return the width of the cells in the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the cells in the grid.
   *
   * @return the height of the cells in the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

 private:
  orientation m_orientation{orientation::orthogonal};
  int m_width{};
  int m_height{};
};

inline void from_json(const json& json, grid& grid)
{
  json.at("width").get_to(grid.m_width);
  json.at("height").get_to(grid.m_height);
  json.at("orientation").get_to(grid.m_orientation);
}

NLOHMANN_JSON_SERIALIZE_ENUM(grid::orientation,
                             {{grid::orientation::orthogonal, "orthogonal"},
                              {grid::orientation::isometric, "isometric"}})

}  // namespace step

#endif  // STEP_GRID_HEADER
