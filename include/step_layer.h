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

#ifndef STEP_LAYER_HEADER
#define STEP_LAYER_HEADER

#include <string>
#include <variant>
#include <vector>

#include "step_api.h"
#include "step_data.h"
#include "step_property.h"
#include "step_types.h"

namespace step {

/**
 * The Layer class represents the tile layers that reside in the tile maps.
 *
 * @since 0.1.0
 */
class Layer final {
 public:
  using Data = std::vector<unsigned int>;

  STEP_API friend void from_json(const JSON&, Layer&);

  /**
   * The Type enum class provides identifiers for all of the different
   * possible layer types.
   *
   * @since 0.1.0
   */
  enum class Type { TileLayer, ObjectGroup, ImageLayer, Group };

  /**
   * The Compression enum class provides values for the different kinds of
   * compression used by layers.
   *
   * @since 0.1.0
   */
  enum class Compression { ZLib, GZip, None };

  /**
   * The DrawOrder enum class provides hints for how rendering should be
   * performed of layers.
   *
   * @since 0.1.0
   */
  enum class DrawOrder { TopDown, Index };

  /**
   * The Encoding enum class provides identifiers for the different encodings
   * used by layers.
   *
   * @since 0.1.0
   */
  enum class Encoding { CSV, Base64 };

  /**
   * Returns the unique integer ID associated with the layer.
   *
   * @return the unique integer ID associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY int id() const noexcept;

  /**
   * Indicates whether or not the layer is a tile layer.
   *
   * @return true if the layer is a tile layer; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_tile_layer() const noexcept;

  /**
   * Indicates whether or not the layer is an image layer.
   *
   * @return true if the layer is an image layer; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_image_layer() const noexcept;

  /**
   * Indicates whether or not the layer is an object group.
   *
   * @return true if the layer is an object group; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_object_group() const noexcept;

  /**
   * Indicates whether or not the layer is a group.
   *
   * @return true if the layer is a group; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_group() const noexcept;

  /**
   * Returns the type of the layer.
   *
   * @return the type of the layer.
   * @since 0.1.0
   */
  STEP_QUERY Type type() const noexcept;

  /**
   * Returns the amount of columns in the layer.
   *
   * @return the amount of columns in the layer.
   * @since 0.1.0
   */
  STEP_QUERY int width() const noexcept;

  /**
   * Returns the amount of rows in the layer.
   *
   * @return the amount of rows in the layer.
   * @since 0.1.0
   */
  STEP_QUERY int height() const noexcept;

  /**
   * Returns the x-coordinate of where the layer content begins. This is used by
   * infinite maps.
   *
   * @return the x-coordinate of where the layer content begins.
   * @since 0.1.0
   */
  STEP_QUERY int start_x() const noexcept;

  /**
   * Returns the y-coordinate of where the layer content begins. This is used by
   * infinite maps.
   *
   * @return the y-coordinate of where the layer content begins.
   * @since 0.1.0
   */
  STEP_QUERY int start_y() const noexcept;

  /**
   * Indicates whether or not the layer is visible.
   *
   * @return true if the layer is visible; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool visible() const noexcept;

  /**
   * Returns the name associated with the layer.
   *
   * @return the name associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY std::string name() const;

  /**
   * Returns the horizontal offset of the layer. The default value of
   * this property is 0.
   *
   * @return the horizontal offset of the layer, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY double offset_x() const noexcept;

  /**
   * Returns the vertical offset of the layer. The default value of
   * this property is 0.
   *
   * @return the vertical offset of the layer, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY double offset_y() const noexcept;

  /**
   * Returns the opacity of the layer.
   *
   * @return the opacity of the layer, in the range [0, 1].
   * @since 0.1.0
   */
  STEP_QUERY double opacity() const noexcept;

  /**
   * Returns the properties associated with the layer.
   *
   * @return the properties associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<Property>& properties() const noexcept;

  /**
   * Returns the encoding used by the layer. This method is only applicable
   * on tile layers.
   *
   * @return the encoding used by the layer; nothing if the encoding couldn't
   * be determined.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Encoding> encoding() const noexcept;

  /**
   * Returns the compression used by the layer. This method is only
   * applicable on tile layers.
   *
   * @return the compression used by the layer; nothing if the compression
   * couldn't be determined.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Compression> compression() const noexcept;

  /**
   * Returns the tile data associated with the layer. Only applicable
   * on tile layers.
   *
   * @return the tile data associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY const detail::Data& data() const noexcept;

  /**
   * Returns the image used by the layer. This method is only applicable on
   * image layers.
   *
   * @return the image used by the layer; nothing if there is no such image.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<std::string> image() const;

  /**
   * Returns the transparent color used by the layer. This property is
   * optional and only applicable on image layers.
   *
   * @return the transparent color used by the layer; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Color> transparent_color() const noexcept;

  /**
   * Returns the draw order used by the layer. This method is only applicable
   * on object groups.
   *
   * @return the draw order used by the layer; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<DrawOrder> draw_order() const noexcept;

  // TODO layers

 private:
  int m_id = 0;
  Type m_type;

  // TODO std::vector<Chunk> m_chunks;

  Encoding m_encoding = Encoding::CSV;            // TILE LAYER ONLY
  Compression m_compression = Compression::None;  // TILE LAYER ONLY
  detail::Data m_data;                            // TILE LAYER ONLY

  int m_width{0};
  int m_height{0};

  std::string m_image;              // IMAGE LAYER ONLY
  Maybe<Color> m_transparentColor;  // IMAGE LAYER ONLY

  // TODO std::vector<Layer // GROUP ONLY
  std::string m_name;

  // TODO std::vector<Object> m_objects;       // OBJECT GROUP ONLY
  DrawOrder m_drawOrder = DrawOrder::TopDown;  // OBJECT GROUP ONLY

  double m_offsetX = 0;
  double m_offsetY = 0;
  double m_opacity;
  std::vector<Property> m_properties;
  int m_startX = 0;  // for infinite maps
  int m_startY = 0;  // for infinite maps

  bool m_visible;

  void init_common(const JSON& json);

  void init_tile_layer(const JSON& json);

  void init_image_layer(const JSON& json);

  void init_image_group(const JSON& json);

  void init_group(const JSON& json);
};

void from_json(const JSON& json, Layer& layer);

STEP_SERIALIZE_ENUM(Layer::Type,
                    {{Layer::Type::TileLayer, "tilelayer"},
                     {Layer::Type::ImageLayer, "imagelayer"},
                     {Layer::Type::ObjectGroup, "objectgroup"},
                     {Layer::Type::Group, "group"}})

STEP_SERIALIZE_ENUM(Layer::Compression,
                    {{Layer::Compression::None, ""},
                     {Layer::Compression::GZip, "gzip"},
                     {Layer::Compression::ZLib, "zlib"}})

STEP_SERIALIZE_ENUM(Layer::DrawOrder,
                    {{Layer::DrawOrder::Index, "index"},
                     {Layer::DrawOrder::TopDown, "topdown"}})

STEP_SERIALIZE_ENUM(Layer::Encoding,
                    {{Layer::Encoding::CSV, "csv"},
                     {Layer::Encoding::Base64, "base64"}})

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_layer.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_LAYER_HEADER
