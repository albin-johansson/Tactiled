#include "step_object_group.h"

namespace step {

ObjectGroup::ObjectGroup(const JSON& json)
    : m_drawOrder{json.at("draworder")},
      m_objects{detail::fill_unique_vec<Object>(json, "objects")}
{}

ObjectGroup::DrawOrder ObjectGroup::draw_order() const noexcept
{
  return m_drawOrder;
}

const std::vector<std::unique_ptr<Object>>& ObjectGroup::objects() const
{
  return m_objects;
}

}  // namespace step
