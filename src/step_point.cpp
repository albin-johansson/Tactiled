#include "step_point.h"

namespace step {

void from_json(const JSON& json, Point& point)  // FIXME
{
  json.at("x").get_to(point.m_x);
  json.at("y").get_to(point.m_y);
}

}  // namespace step
