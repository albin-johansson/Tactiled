#include "step_wang_color.hpp"

namespace step {

WangColor::WangColor(const json& json)
    : m_name{json.at("name").get<std::string>()},
      m_color{json.at("color").get<std::string>()},
      m_tile{json.at("tile").get<int>()},
      m_probability{json.at("probability").get<double>()}
{}

const std::string& WangColor::name() const
{
  return m_name;
}

const Color& WangColor::color() const noexcept
{
  return m_color;
}

local_id WangColor::tile() const noexcept
{
  return m_tile;
}

double WangColor::probability() const noexcept
{
  return m_probability;
}

}  // namespace step
