/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_TILE_HEADER
#define STEP_TILE_HEADER

#include <vector>

#include "step_animation.h"
#include "step_api.h"
#include "step_properties.h"
#include "step_types.h"

namespace step {

/**
 * The Tile class provides information about a tile in a tileset.
 *
 * @since 0.1.0
 */
class Tile final {
 public:
  /**
   * The TerrainPos enum class provides values that represent the different
   * positions that could be inhabited by terrain IDs, in relation to the tile.
   *
   * @since 0.1.0
   */
  enum class TerrainPos {
    TopLeft = 0,
    TopRight = 1,
    BottomLeft = 2,
    BottomRight = 3
  };

  /**
   * Returns the ID of the terrain at the specified position, in relation to
   * the tile.
   *
   * @param position the position that will be checked.
   * @return the ID of the terrain at the specified position; nothing
   * if there is none.
   * @since 0.1.0
   */
  STEP_QUERY
  Maybe<int> terrain_at(TerrainPos position) const noexcept;

  STEP_API friend void from_json(const JSON&, Tile&);

  /**
   * Returns the local ID associated with the tile.
   *
   * @return the local ID associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] int id() const noexcept { return m_id; }

  /**
   * Returns the animation associated with the tile.
   *
   * @return the animation associated with the tile; nothing if there is no
   * animation associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<Animation> animation() const noexcept
  {
    return m_animation;
  }

  /**
   * Returns the properties associated with the tile.
   *
   * @return the properties associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] const Properties& properties() const { return m_properties; }

  /**
   * Returns the type of the tile.
   *
   * @return the type of the tile; nothing if there is none.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<std::string> type() const noexcept { return m_type; }

  /**
   * Returns the image associated with the tile.
   *
   * @return the image associated with the tile; nothing if there is none.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<std::string> image() const noexcept { return m_image; }

  /**
   * Returns the width of the image associated with the tile.
   *
   * @return the width of the image associated with the tile; nothing if
   * there is no image associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<int> image_width() const noexcept { return m_imageWidth; }

  /**
   * Returns the height of the image associated with the tile.
   *
   * @return the height of the image associated with the tile; nothing if
   * there is no image associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<int> image_height() const noexcept
  {
    return m_imageHeight;
  }

  /**
   * Returns the probability associated with the tile.
   *
   * @return the probability associated with the tile; nothing if there is none.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<double> probability() const noexcept
  {
    return m_probability;
  }

 private:
  int m_id = 0;
  Maybe<Animation> m_animation;
  Properties m_properties;
  // TODO Maybe<Layer> m_objectGroup;
  Maybe<std::array<int, 4>> m_terrain;
  Maybe<std::string> m_type;
  Maybe<std::string> m_image;
  Maybe<int> m_imageWidth;
  Maybe<int> m_imageHeight;
  Maybe<double> m_probability;
};

STEP_API void from_json(const JSON& json, Tile& tile);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_tile.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TILE_HEADER
