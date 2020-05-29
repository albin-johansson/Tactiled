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
const TileLayer& Layer::as_tile_layer() const
{
  if (std::holds_alternative<TileLayer>(m_layerData)) {
    return std::get<TileLayer>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't a tile layer!"};
  }
}

STEP_DEF
const ImageLayer& Layer::as_image_layer() const
{
  if (std::holds_alternative<ImageLayer>(m_layerData)) {
    return std::get<ImageLayer>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't an image layer!"};
  }
}

STEP_DEF
const ObjectGroup& Layer::as_object_group() const
{
  if (std::holds_alternative<ObjectGroup>(m_layerData)) {
    return std::get<ObjectGroup>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't an object group!"};
  }
}

STEP_DEF
const Group& Layer::as_group() const
{
  if (std::holds_alternative<Group>(m_layerData)) {
    return std::get<Group>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't a group!"};
  }
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
void Layer::init_common(const JSON& json)
{
  json.at("type").get_to(m_type);

  detail::safe_bind(json, "name", m_name);
  detail::safe_bind(json, "opacity", m_opacity);
  detail::safe_bind(json, "visible", m_visible);
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
void from_json(const JSON& json, Layer& layer)
{
  layer.init_common(json);
  switch (layer.type()) {
    case Layer::Type::TileLayer: {
      layer.m_layerData.emplace<TileLayer>(json.get<TileLayer>());
      break;
    }
    case Layer::Type::ObjectGroup: {
      layer.m_layerData.emplace<ObjectGroup>(json.get<ObjectGroup>());
      break;
    }
    case Layer::Type::ImageLayer: {
      layer.m_layerData.emplace<ImageLayer>(json.get<ImageLayer>());
      break;
    }
    case Layer::Type::Group: {
      layer.m_layerData.emplace<Group>(json.get<Group>());
      break;
    }
    default: {
      const auto type = std::to_string(static_cast<int>(layer.type()));
      throw StepException{"Layer > Unknown layer type: " + type};
    }
  }
}

}  // namespace step

#endif  // STEP_LAYER_SOURCE
