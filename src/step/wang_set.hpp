#ifndef STEP_WANG_SET_HEADER
#define STEP_WANG_SET_HEADER

#include <string>
#include <string_view>
#include <vector>

#include "properties.hpp"
#include "step_api.hpp"
#include "utils.hpp"
#include "wang_color.hpp"
#include "wang_tile.hpp"

namespace step {

class wang_set final
{
  using colors = std::vector<wang_color>;
  using tiles = std::vector<WangTile>;

 public:
  /**
   * \param json the JSON object that holds the data for a Wang set.
   *
   * \since 0.1.0
   */
  explicit wang_set(const json& json)
      : m_tile{json.at("tile").get<int>()}
      , m_cornerColors{detail::fill<colors>(json, "cornercolors")}
      , m_edgeColors{detail::fill<colors>(json, "edgecolors")}
      , m_wangTiles{detail::fill<tiles>(json, "wangtiles")}
      , m_properties{json.at("properties")}
      , m_name{json.at("name").get<std::string>()}
  {}

  /**
   * \brief Returns all of the corner colors associated with the Wang set.
   *
   * \return all of the corner colors associated with the Wang set.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto corner_colors() const -> const colors&
  {
    return m_cornerColors;
  }

  /**
   * \brief Returns all of the edge colors associated with the Wang set.
   *
   * \return all of the edge colors associated with the Wang set.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto edge_colors() const -> const colors&
  {
    return m_edgeColors;
  }

  /**
   * \brief Returns all of the Wang tiles associated with the Wang set.
   *
   * \return all of the Wang tiles associated with the Wang set.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto wang_tiles() const -> const tiles&
  {
    return m_wangTiles;
  }

  /**
   * \brief Returns the properties associated with the Wang set.
   *
   * \return the properties associated with the Wang set.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_properties() const -> const properties&
  {
    return m_properties;
  }

  /**
   * \brief Returns the name associated with the Wang set.
   *
   * \return the name associated with the Wang set.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * \brief Returns the local ID of the tile that represents the Wang set.
   *
   * \return the local ID of the tile that represents the Wang set.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tile;
  }

 private:
  local_id m_tile{0};
  std::vector<wang_color> m_cornerColors;
  std::vector<wang_color> m_edgeColors;
  std::vector<WangTile> m_wangTiles;
  properties m_properties;
  std::string m_name;
};

}  // namespace step

#endif  // STEP_WANG_SET_HEADER
