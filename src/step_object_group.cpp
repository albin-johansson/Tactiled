#include "step_object_group.hpp"

namespace step {

ObjectGroup::ObjectGroup(const json& json)
    : m_drawOrder{json.at("draworder")},
      m_objects{detail::fill_unique_vec<object>(json, "objects")}
{}

ObjectGroup::DrawOrder ObjectGroup::draw_order() const noexcept
{
  return m_drawOrder;
}

const std::vector<std::unique_ptr<object>>& ObjectGroup::objects() const
{
  return m_objects;
}

}  // namespace step
