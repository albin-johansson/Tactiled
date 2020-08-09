#include "step_object.hpp"

#include "step_utils.hpp"

namespace step {

object::object(const json& json)
    : m_id{json.at("id").get<int>()},
      m_x{json.at("x").get<double>()},
      m_y{json.at("y").get<double>()},
      m_width{json.at("width").get<double>()},
      m_height{json.at("height").get<double>()},
      m_rotation{json.at("rotation").get<double>()},
      m_name{json.at("name").get<std::string>()},
      m_type{json.at("type").get<std::string>()},
      m_properties{detail::safe_bind_unique<properties>(json, "properties")},
      m_ellipse{detail::safe_get<bool>(json, "ellipse", false)},
      m_point{detail::safe_get<bool>(json, "point", false)},
      m_visible{json.at("visible").get<bool>()}
{
  if (json.contains("gid")) {
    m_specificData.emplace<global_id>(json.at("gid").get<unsigned>());

  } else if (json.contains("text")) {
    m_specificData.emplace<text>(json.at("text"));

  } else if (json.contains("polygon")) {
    auto& poly = m_specificData.emplace<polygon>();

    for (const auto& [key, value] : json.at("polygon").items()) {
      poly.points.emplace_back(point{value});
    }

  } else if (json.contains("polyline")) {
    auto& line = m_specificData.emplace<polyline>();

    for (const auto& [key, value] : json.at("polyline").items()) {
      line.points.emplace_back(point{value});
    }

  } else if (json.contains("template")) {
    auto& templ = m_specificData.emplace<template_object>();
    json.at("template").get_to(templ.templateFile);
  }
}

auto object::id() const noexcept -> int
{
  return m_id;
}

auto object::x() const noexcept -> double
{
  return m_x;
}

auto object::y() const noexcept -> double
{
  return m_y;
}

auto object::width() const noexcept -> double
{
  return m_width;
}

auto object::height() const noexcept -> double
{
  return m_height;
}

auto object::rotation() const noexcept -> double
{
  return m_rotation;
}

auto object::name() const -> std::string
{
  return m_name;
}

auto object::type() const -> std::string
{
  return m_type;
}

auto object::get_properties() const noexcept -> const properties*
{
  return m_properties.get();
}

auto object::visible() const noexcept -> bool
{
  return m_visible;
}

auto object::is_ellipse() const noexcept -> bool
{
  return m_ellipse;
}

auto object::is_point() const noexcept -> bool
{
  return m_point;
}

}  // namespace step
