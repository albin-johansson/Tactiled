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

#ifndef STEP_TILESET_HEADER
#define STEP_TILESET_HEADER

#include <memory>

#include "step_api.h"
#include "step_color.h"
#include "step_property.h"
#include "step_tile.h"
#include "step_types.h"

namespace step {

class Tileset final {
 public:
  STEP_API explicit Tileset(const JSON& json);

  STEP_QUERY static std::unique_ptr<Tileset> unique(const JSON& json);

  /**
   * Returns the GID (Global ID) of the first tile in the tileset.
   *
   * @return the GID (Global ID) of the first tile in the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] int first_gid() const noexcept { return m_firstGID; }

  /**
   * Returns the maximum width of tiles in the tileset.
   *
   * @return the maximum width of tiles in the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] int tile_width() const noexcept { return m_tileWidth; }

  /**
   * Returns the maximum height of tiles in the tileset.
   *
   * @return the maximum height of tiles in the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] int tile_height() const noexcept { return m_tileHeight; }

  /**
   * Returns the number of tiles in the tileset.
   *
   * @return the number of tiles in the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] int tile_count() const noexcept { return m_tileCount; }

  /**
   * Returns the number of columns in the tileset.
   *
   * @return the number of columns in the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] int columns() const noexcept { return m_nColumns; }

  /**
   * Returns the width of the source image in pixels.
   *
   * @return the width of the source image in pixels.
   * @since 0.1.0
   */
  [[nodiscard]] int image_width() const noexcept { return m_imageWidth; }

  /**
   * Returns the height of the source image in pixels.
   *
   * @return the height of the source image in pixels.
   * @since 0.1.0
   */
  [[nodiscard]] int image_height() const noexcept { return m_imageHeight; }

  /**
   * Returns the buffer amount between the image edge and the first tile, in
   * pixels.
   *
   * @return the buffer amount between the image edge and the first tile, in
   * pixels.
   * @since 0.1.0
   */
  [[nodiscard]] int margin() const noexcept { return m_margin; }

  /**
   * Returns the amount of spacing between adjacent tiles in the tileset, in
   * pixels.
   *
   * @return the amount of spacing between adjacent tiles in the tileset, in
   * pixels.
   * @since 0.1.0
   */
  [[nodiscard]] int spacing() const noexcept { return m_spacing; }

  /**
   * Returns the path to the external
   *
   * @return
   */
  [[nodiscard]] std::string source() const noexcept { return m_source; }

  [[nodiscard]] std::string image() const noexcept { return m_image; }

  // TODO way to obtain properties

  [[nodiscard]] std::string name() const noexcept { return m_name; }

  [[nodiscard]] std::optional<Color> background_color() const noexcept
  {
    return m_backgroundColor;
  }

  [[nodiscard]] std::optional<Color> transparent_color() const noexcept
  {
    return m_transparentColor;
  }

  [[nodiscard]] std::string tiled_version() const noexcept
  {
    return m_tiledVersion;
  }

  [[nodiscard]] std::string json_version() const noexcept
  {
    return m_jsonVersion;
  }

 private:
  int m_firstGID;
  int m_tileWidth;
  int m_tileHeight;
  int m_tileCount;
  int m_nColumns;
  int m_imageWidth;
  int m_imageHeight;
  int m_margin;
  int m_spacing;
  std::vector<Tile> m_tiles;
  std::vector<Property> m_properties;

  std::string m_image;
  std::string m_source;  // source of the tileset data
  std::string m_name;
  std::optional<Color> m_backgroundColor;   // OPTIONAL
  std::optional<Color> m_transparentColor;  // OPTIONAL
  std::string m_tiledVersion;
  std::string m_jsonVersion;

  // TODO Grid  // OPTIONAL
  // TODO std::vector<Terrain> m_terrains; // OPTIONAL
  // TODO TileOffset m_tileOffset; // OPTIONAL
  // TODO type which is always tileset?
  // TODO std::vector<WangSet> m_wangSets;

  void load_from(const JSON& json);
};

}  // namespace step

#endif  // STEP_TILESET_HEADER
