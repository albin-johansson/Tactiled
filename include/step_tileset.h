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

#include <vector>

#include "step_api.h"
#include "step_color.h"
#include "step_grid.h"
#include "step_property.h"
#include "step_terrain.h"
#include "step_tile.h"
#include "step_tile_offset.h"
#include "step_types.h"

namespace step {

class Tileset;

/**
 * The Tileset class represents a collection of tiles associated with an
 * image. All tilesets have a global ID (GID) associated with them, that
 * starts at 1 for the first tileset.
 *
 * @since 0.1.0
 */
class Tileset final {
 public:
  friend void from_json(const JSON&, Tileset&);
  friend void load_from(const JSON&, Tileset&);

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
   * Returns the tiles associated with the tileset that have custom
   * properties. This property is optional.
   *
   * @return the tiles associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] const std::vector<Tile>& tiles() const noexcept
  {
    return m_tiles;
  }

  /**
   * Returns the tiles associated with the tileset that have custom
   * properties. This property is optional.
   *
   * @return the tiles associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] std::vector<Tile>& tiles() noexcept { return m_tiles; }

  /**
   * Returns the properties associated with the tileset.
   *
   * @return the properties associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] const std::vector<Property>& properties() const noexcept
  {
    return m_properties;
  }

  /**
   * Returns the properties associated with the tileset.
   *
   * @return the properties associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] std::vector<Property>& properties() noexcept
  {
    return m_properties;
  }

  /**
   * Returns the terrains associated with the tileset. This property is
   * optional.
   *
   * @return the terrains associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] const std::vector<Terrain>& terrains() const noexcept
  {
    return m_terrains;
  }

  /**
   * Returns the terrains associated with the tileset. This property is
   * optional.
   *
   * @return the terrains associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] std::vector<Terrain>& terrains() noexcept { return m_terrains; }

  /**
   * Returns the path to the external file that holds the actual tileset
   * data, if this tileset isn't embedded. This method will return the empty
   * string if the tileset is embedded.
   *
   * @return the path to the external file that holds the tileset data if the
   * the tileset is external; the empty string is returned if the tileset is
   * embedded.
   * @since 0.1.0
   */
  [[nodiscard]] std::string source() const noexcept { return m_source; }

  /**
   * Returns the path to the image associated with the tileset.
   *
   * @return the path to the image associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] std::string image() const noexcept { return m_image; }

  /**
   * Returns the name associated with the tileset.
   *
   * @return the name associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] std::string name() const noexcept { return m_name; }

  /**
   * Returns the background color of the tileset. This property is optional.
   *
   * @return the background color of the tileset; nothing if there is none.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<Color> background_color() const noexcept
  {
    return m_backgroundColor;
  }

  /**
   * Returns the transparent color of the tileset. This property is optional.
   *
   * @return the transparent color of the tileset; nothing if there is none.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<Color> transparent_color() const noexcept
  {
    return m_transparentColor;
  }

  /**
   * Returns the grid associated with the tileset. This property is optional.
   *
   * @return the grid associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<Grid> grid() const noexcept { return m_grid; }

  /**
   * Returns the tile offset associated with the tileset. This property is
   * optional.
   *
   * @return the tile offset associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] Maybe<TileOffset> tile_offset() const noexcept
  {
    return m_tileOffset;
  }

  /**
   * Returns the Tiled version associated with the tileset.
   *
   * @return the Tiled version associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] std::string tiled_version() const noexcept
  {
    return m_tiledVersion;
  }

  /**
   * Returns the JSON format version associated with the tileset.
   *
   * @return the JSON format version associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] double json_version() const noexcept { return m_jsonVersion; }

 private:
  int m_firstGID = 1;
  int m_tileWidth = 0;
  int m_tileHeight = 0;
  int m_tileCount = 0;
  int m_nColumns = 0;
  int m_imageWidth = 0;
  int m_imageHeight = 0;
  int m_margin = 0;
  int m_spacing = 0;
  std::vector<Tile> m_tiles;
  std::vector<Property> m_properties;  // TODO consider changing this
  std::vector<Terrain> m_terrains;

  std::string m_image;
  std::string m_source;
  std::string m_name;
  Maybe<Color> m_backgroundColor;
  Maybe<Color> m_transparentColor;
  Maybe<Grid> m_grid;
  Maybe<TileOffset> m_tileOffset;

  std::string m_tiledVersion;
  double m_jsonVersion = 0;

  // TODO std::vector<WangSet> m_wangSets;
};

STEP_API void from_json(const JSON& json, Tileset& set);

STEP_API void load_from(const JSON& json, Tileset& set);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_tileset.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TILESET_HEADER
