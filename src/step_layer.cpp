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

#ifndef STEP_LAYER_SOURCE
#define STEP_LAYER_SOURCE

#include "step_layer.h"

#include "step_exception.h"
#include "step_utils.h"

namespace step {

STEP_DEF
int Layer::id() const noexcept
{
  return m_id;
}

STEP_DEF
bool Layer::is_tile_layer() const noexcept
{
  return m_type == Type::TileLayer;
}

STEP_DEF
bool Layer::is_image_layer() const noexcept
{
  return m_type == Type::ImageLayer;
}

STEP_DEF
bool Layer::is_object_group() const noexcept
{
  return m_type == Type::ObjectGroup;
}

STEP_DEF
bool Layer::is_group() const noexcept
{
  return m_type == Type::Group;
}

STEP_DEF
Layer::Type Layer::type() const noexcept
{
  return m_type;
}

STEP_DEF
int Layer::width() const noexcept
{
  return m_width;
}

STEP_DEF
int Layer::height() const noexcept
{
  return m_height;
}

STEP_DEF
int Layer::start_x() const noexcept
{
  return m_startX;
}

STEP_DEF
int Layer::start_y() const noexcept
{
  return m_startY;
}

STEP_DEF
bool Layer::visible() const noexcept
{
  return m_visible;
}

STEP_DEF
std::string Layer::name() const
{
  return m_name;
}

STEP_DEF
double Layer::offset_x() const noexcept
{
  return m_offsetX;
}

STEP_DEF
double Layer::offset_y() const noexcept
{
  return m_offsetY;
}

STEP_DEF
double Layer::opacity() const noexcept
{
  return m_opacity;
}

STEP_DEF
const std::vector<Property>& Layer::properties() const noexcept
{
  return m_properties;
}

STEP_DEF
Maybe<Layer::Encoding> Layer::encoding() const noexcept
{
  if (is_tile_layer()) {
    return m_encoding;
  } else {
    return nothing;
  }
}

STEP_DEF
Maybe<Layer::Compression> Layer::compression() const noexcept
{
  if (is_tile_layer()) {
    return m_compression;
  } else {
    return nothing;
  }
}

STEP_DEF
const Layer::Data& Layer::data() const
{
  if (is_tile_layer() && std::holds_alternative<Data>(m_data)) {
    return std::get<Data>(m_data);
  } else {
    throw StepException{"Layer > Failed to obtain GID data!"};
  }
}

STEP_DEF
const std::string& Layer::base64_data() const
{
  if (is_tile_layer() && std::holds_alternative<std::string>(m_data)) {
    return std::get<std::string>(m_data);
  } else {
    throw StepException{"Layer > Failed to obtain Base64 data!"};
  }
}

STEP_DEF
Maybe<std::string> Layer::image() const
{
  if (is_image_layer()) {
    return m_image;
  } else {
    return nothing;
  }
}

STEP_DEF
Maybe<Color> Layer::transparent_color() const noexcept
{
  return m_transparentColor;
}

STEP_DEF
Maybe<Layer::DrawOrder> Layer::draw_order() const noexcept
{
  if (is_object_group()) {
    return m_drawOrder;
  } else {
    return nothing;
  }
}

STEP_DEF
void Layer::init_common(const JSON& json)
{
  json.at("type").get_to(m_type);
  json.at("name").get_to(m_name);
  json.at("opacity").get_to(m_opacity);
  json.at("visible").get_to(m_visible);

  detail::safe_bind(json, "id", m_id);
  detail::safe_bind(json, "width", m_width);
  detail::safe_bind(json, "height", m_height);
  detail::safe_bind(json, "startx", m_startX);
  detail::safe_bind(json, "starty", m_startY);
  detail::safe_bind(json, "offsetx", m_offsetX);
  detail::safe_bind(json, "offsety", m_offsetY);

  if (json.contains("properties")) {
    for (const auto& [key, value] : json.at("properties").items()) {
      m_properties.emplace_back(value);
    }
  }
}

STEP_DEF
void Layer::init_tile_layer(const JSON& json)
{
  detail::safe_bind(json, "compression", m_compression);
  detail::safe_bind(json, "encoding", m_encoding);
  if (json.contains("data")) {
    if (m_encoding == Layer::Encoding::CSV) {
      auto& data = m_data.emplace<Layer::Data>();
      for (const auto& [key, value] : json.at("data").items()) {
        data.emplace_back(value.get<int>());
      }
    } else if (m_encoding == Layer::Encoding::Base64) {
      // FIXME no idea if this works, might just not support Base64
      m_data.emplace<std::string>(json.at("data").get<std::string>());
    }
  }
}

STEP_DEF
void Layer::init_image_layer(const JSON& json)
{
  json.at("image").get_to(m_image);
  if (json.count("transparentcolor")) {
    m_transparentColor = Color{json.at("transparentcolor").get<std::string>()};
  }
}

STEP_DEF
void Layer::init_image_group(const JSON& json)
{
  json.at("draworder").get_to(m_drawOrder);
  // TODO objects
}

STEP_DEF
void Layer::init_group(const JSON& json)
{
  // TODO layers
}

STEP_DEF
void from_json(const JSON& json, Layer& layer)
{
  layer.init_common(json);
  switch (layer.type()) {
    case Layer::Type::TileLayer: {
      layer.init_tile_layer(json);
      break;
    }
    case Layer::Type::ObjectGroup: {
      layer.init_image_group(json);
      break;
    }
    case Layer::Type::ImageLayer: {
      layer.init_image_layer(json);
      break;
    }
    case Layer::Type::Group: {
      layer.init_group(json);
      break;
    }
    default:
      throw StepException{"Layer > Unknown layer type!"};
  }
}

}  // namespace step

#endif  // STEP_LAYER_SOURCE
