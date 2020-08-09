#include "step_object.h"

#include "step_utils.h"

namespace step {

Object::Object(const json& json)
    : m_id{json.at("id").get<int>()},
      m_x{json.at("x").get<double>()},
      m_y{json.at("y").get<double>()},
      m_width{json.at("width").get<double>()},
      m_height{json.at("height").get<double>()},
      m_rotation{json.at("rotation").get<double>()},
      m_name{json.at("name").get<std::string>()},
      m_type{json.at("type").get<std::string>()},
      m_properties{detail::safe_bind_unique<Properties>(json, "properties")},
      m_ellipse{detail::safe_get<bool>(json, "ellipse", false)},
      m_point{detail::safe_get<bool>(json, "point", false)},
      m_visible{json.at("visible").get<bool>()}
{
  if (json.contains("gid")) {
    m_specificData.emplace<global_id>(json.at("gid").get<unsigned>());

  } else if (json.contains("text")) {
    m_specificData.emplace<text>(json.at("text"));

  } else if (json.contains("polygon")) {
    auto& polygon = m_specificData.emplace<Polygon>();

    for (const auto& [key, value] : json.at("polygon").items()) {
      polygon.points.emplace_back(point{value});
    }

  } else if (json.contains("polyline")) {
    auto& polyline = m_specificData.emplace<Polyline>();

    for (const auto& [key, value] : json.at("polyline").items()) {
      polyline.points.emplace_back(point{value});
    }

  } else if (json.contains("template")) {
    auto& templ = m_specificData.emplace<Template>();
    json.at("template").get_to(templ.templateFile);
  }
}

int Object::id() const noexcept
{
  return m_id;
}

double Object::x() const noexcept
{
  return m_x;
}

double Object::y() const noexcept
{
  return m_y;
}

double Object::width() const noexcept
{
  return m_width;
}

double Object::height() const noexcept
{
  return m_height;
}

double Object::rotation() const noexcept
{
  return m_rotation;
}

std::string Object::name() const
{
  return m_name;
}

std::string Object::type() const
{
  return m_type;
}

const Properties* Object::properties() const noexcept
{
  return m_properties.get();
}

std::optional<Polygon> Object::polygon() const noexcept
{
  if (std::holds_alternative<Polygon>(m_specificData)) {
    return std::get<Polygon>(m_specificData);
  } else {
    return std::nullopt;
  }
}

std::optional<Polyline> Object::polyline() const noexcept
{
  if (std::holds_alternative<Polyline>(m_specificData)) {
    return std::get<Polyline>(m_specificData);
  } else {
    return std::nullopt;
  }
}

std::optional<global_id> Object::tile_gid() const noexcept
{
  if (std::holds_alternative<global_id>(m_specificData)) {
    return std::get<global_id>(m_specificData);
  } else {
    return std::nullopt;
  }
}

std::optional<Template> Object::template_data() const
{
  if (std::holds_alternative<Template>(m_specificData)) {
    return std::get<Template>(m_specificData);
  } else {
    return std::nullopt;
  }
}

std::optional<text> Object::get_text() const
{
  if (std::holds_alternative<text>(m_specificData)) {
    return std::get<text>(m_specificData);
  } else {
    return std::nullopt;
  }
}

bool Object::visible() const noexcept
{
  return m_visible;
}

bool Object::is_ellipse() const noexcept
{
  return m_ellipse;
}

bool Object::is_point() const noexcept
{
  return m_point;
}

bool Object::is_polygon() const noexcept
{
  return std::holds_alternative<Polygon>(m_specificData);
}

bool Object::is_polyline() const noexcept
{
  return std::holds_alternative<Polyline>(m_specificData);
}

bool Object::is_text() const noexcept
{
  return std::holds_alternative<text>(m_specificData);
}

bool Object::is_template() const noexcept
{
  return std::holds_alternative<Template>(m_specificData);
}

bool Object::is_tile() const noexcept
{
  return std::holds_alternative<global_id>(m_specificData);
}

}  // namespace step
