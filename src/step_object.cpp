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

#ifndef STEP_OBJECT_SOURCE
#define STEP_OBJECT_SOURCE

#include "step_object.h"

#include "step_utils.h"

namespace step {

STEP_DEF
int Object::id() const noexcept
{
  return m_id;
}

STEP_DEF
double Object::x() const noexcept
{
  return m_x;
}

STEP_DEF
double Object::y() const noexcept
{
  return m_y;
}

STEP_DEF
double Object::width() const noexcept
{
  return m_width;
}

STEP_DEF
double Object::height() const noexcept
{
  return m_height;
}

STEP_DEF
double Object::rotation() const noexcept
{
  return m_rotation;
}

STEP_DEF
std::string Object::name() const
{
  return m_name;
}

STEP_DEF
std::string Object::type() const
{
  return m_type;
}

STEP_DEF
const Properties& Object::properties() const noexcept
{
  return m_properties;
}

STEP_DEF
std::optional<Polygon> Object::polygon() const noexcept
{
  if (std::holds_alternative<Polygon>(m_specificData)) {
    return std::get<Polygon>(m_specificData);
  } else {
    return std::nullopt;
  }
}

STEP_DEF
std::optional<Polyline> Object::polyline() const noexcept
{
  if (std::holds_alternative<Polyline>(m_specificData)) {
    return std::get<Polyline>(m_specificData);
  } else {
    return std::nullopt;
  }
}

STEP_DEF
std::optional<GlobalID> Object::tile_gid() const noexcept
{
  if (std::holds_alternative<GlobalID>(m_specificData)) {
    return std::get<GlobalID>(m_specificData);
  } else {
    return std::nullopt;
  }
}

STEP_DEF
std::optional<Template> Object::template_data() const
{
  if (std::holds_alternative<Template>(m_specificData)) {
    return std::get<Template>(m_specificData);
  } else {
    return std::nullopt;
  }
}

STEP_DEF
std::optional<Text> Object::text() const
{
  if (std::holds_alternative<Text>(m_specificData)) {
    return std::get<Text>(m_specificData);
  } else {
    return std::nullopt;
  }
}

STEP_DEF
bool Object::visible() const noexcept
{
  return m_visible;
}

STEP_DEF
bool Object::is_ellipse() const noexcept
{
  return m_ellipse;
}

STEP_DEF
bool Object::is_point() const noexcept
{
  return m_point;
}

STEP_DEF
bool Object::is_polygon() const noexcept
{
  return std::holds_alternative<Polygon>(m_specificData);
}

STEP_DEF
bool Object::is_polyline() const noexcept
{
  return std::holds_alternative<Polyline>(m_specificData);
}

STEP_DEF
bool Object::is_text() const noexcept
{
  return std::holds_alternative<Text>(m_specificData);
}

STEP_DEF
bool Object::is_template() const noexcept
{
  return std::holds_alternative<Template>(m_specificData);
}

STEP_DEF
bool Object::is_tile() const noexcept
{
  return std::holds_alternative<GlobalID>(m_specificData);
}

STEP_DEF
void from_json(const JSON& json, Object& object)
{
  json.at("id").get_to(object.m_id);
  json.at("x").get_to(object.m_x);
  json.at("y").get_to(object.m_y);
  json.at("width").get_to(object.m_width);
  json.at("height").get_to(object.m_height);
  json.at("rotation").get_to(object.m_rotation);
  json.at("visible").get_to(object.m_visible);
  json.at("name").get_to(object.m_name);
  json.at("type").get_to(object.m_type);

  if (json.contains("gid")) {
    object.m_specificData.emplace<GlobalID>(json.at("gid").get<unsigned>());
  } else if (json.contains("text")) {
    object.m_specificData.emplace<Text>(json.at("text").get<Text>());
  } else if (json.contains("polygon")) {
    auto& polygon = object.m_specificData.emplace<Polygon>();
    json.at("polygon").get_to(polygon.points);
  } else if (json.contains("polyline")) {
    auto& polyline = object.m_specificData.emplace<Polyline>();
    json.at("polyline").get_to(polyline.points);
  } else if (json.contains("template")) {
    auto& templ = object.m_specificData.emplace<Template>();
    json.at("template").get_to(templ.templateFile);
  }

  detail::safe_bind(json, "properties", object.m_properties);
  detail::safe_bind(json, "ellipse", object.m_ellipse);
  detail::safe_bind(json, "point", object.m_point);
}

}  // namespace step

#endif  // STEP_OBJECT_SOURCE
