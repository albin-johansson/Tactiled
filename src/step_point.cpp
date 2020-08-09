#include "step_point.h"

namespace step {

point::point(const json& json)
    : m_x{json.at("x").get<double>()}, m_y{json.at("y").get<double>()}
{}

auto point::x() const noexcept -> double
{
  return m_x;
}

auto point::y() const noexcept -> double
{
  return m_y;
}

}  // namespace step
