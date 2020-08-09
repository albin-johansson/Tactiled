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

#include <memory>
#include <vector>

#include "step_animation.hpp"
#include "step_api.hpp"
#include "step_properties.hpp"
#include "step_types.hpp"

namespace step {

class Layer;

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

  STEP_API
  explicit Tile(const json& json);

  /**
   * Returns the local ID associated with the tile.
   *
   * @return the local ID associated with the tile.
   * @since 0.1.0
   */
  STEP_QUERY
  local_id id() const noexcept;

  /**
   * Returns the animation associated with the tile.
   *
   * @return the animation associated with the tile; nothing if there is no
   * animation associated with the tile.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<Animation> animation() const noexcept;

  /**
   * Returns the properties associated with the tile.
   *
   * @return the properties associated with the tile; null if there are none.
   * @since 0.1.0
   */
  STEP_QUERY
  const Properties* properties() const;

  /**
   * Returns the object group layer associated with the tile. This property
   * is optional. You'll need to include the <code>step_layer.hpp</code> header
   * if you want to use the returned pointer, since it is forward-declared in
   * the tile header.
   *
   * @return a shared pointer to the object group associated with the tile;
   * null if there is none.
   * @since 0.1.0
   */
  STEP_QUERY
  std::shared_ptr<Layer> object_group() const noexcept;

  /**
   * Returns the type of the tile.
   *
   * @return the type of the tile; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<std::string> type() const;

  /**
   * Returns the image associated with the tile.
   *
   * @return the image associated with the tile; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<std::string> image() const;

  /**
   * Returns the width of the image associated with the tile.
   *
   * @return the width of the image associated with the tile; nothing if
   * there is no image associated with the tile.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<int> image_width() const noexcept;

  /**
   * Returns the height of the image associated with the tile.
   *
   * @return the height of the image associated with the tile; nothing if
   * there is no image associated with the tile.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<int> image_height() const noexcept;

  /**
   * Returns the probability associated with the tile.
   *
   * @return the probability associated with the tile; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<double> probability() const noexcept;

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
  std::optional<int> terrain_at(TerrainPos position) const noexcept;

 private:
  local_id m_id{0};
  std::optional<Animation> m_animation;
  std::unique_ptr<Properties> m_properties;
  std::shared_ptr<Layer> m_objectGroup;
  std::optional<std::array<int, 4>> m_terrain;
  std::optional<std::string> m_type;
  std::optional<std::string> m_image;
  std::optional<int> m_imageWidth;
  std::optional<int> m_imageHeight;
  std::optional<double> m_probability;
};

}  // namespace step

#endif  // STEP_TILE_HEADER