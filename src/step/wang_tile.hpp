#ifndef STEP_WANG_TILE_HEADER
#define STEP_WANG_TILE_HEADER

#include <array>

#include "common.hpp"
#include "step_api.hpp"
#include "step_detail.hpp"

namespace step {

class WangTile final
{
 public:
  /**
   * \param json the JSON object that holds the data for a Wang tile.
   * \since 0.1.0
   */
  explicit WangTile(const json& json)
      : m_tileID{json.at("tileid").get<int>()}
      , m_wangColorIndices{json.at("wangid").get<std::array<int, 8>>()}
      , m_flippedDiagonally{json.at("dflip").get<bool>()}
      , m_flippedHorizontally{json.at("hflip").get<bool>()}
      , m_flippedVertically{json.at("vflip").get<bool>()}
  {}

  /**
   * \brief Returns the local ID associated with the Wang tile.
   *
   * \return the local ID associated with the Wang tile.
   * \since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tileID;
  }

  /**
   * \brief Returns the Wang color indices associated with the Wang tile.
   *
   * \return the Wang color indices associated with the Wang tile.
   * \since 0.1.0
   */
  [[nodiscard]] auto wang_color_indices() const -> const std::array<int, 8>&
  {
    return m_wangColorIndices;
  }

  /**
   * \brief Indicates whether or not the tile is flipped diagonally.
   *
   * \details The default value of this property is false.
   *
   * \return `true` if the tile is flipped diagonally; `false` otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto flipped_diagonally() const noexcept -> bool
  {
    return m_flippedDiagonally;
  }

  /**
   * \brief Indicates whether or not the tile is flipped horizontally.
   *
   * \details The default value of this property is false.
   *
   * \return `true` if the tile is flipped horizontally; `false` otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto flipped_horizontally() const noexcept -> bool
  {
    return m_flippedHorizontally;
  }

  /**
   * \brief Indicates whether or not the tile is flipped vertically.
   *
   * \details The default value of this property is false.
   *
   * \return `true` if the tile is flipped vertically; `false` otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto flipped_vertically() const noexcept -> bool
  {
    return m_flippedVertically;
  }

 private:
  local_id m_tileID{0};
  std::array<int, 8> m_wangColorIndices{};
  bool m_flippedDiagonally{false};
  bool m_flippedHorizontally{false};
  bool m_flippedVertically{false};
};

}  // namespace step

#endif  // STEP_WANG_TILE_HEADER
