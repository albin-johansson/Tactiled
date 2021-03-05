#ifndef STEP_OBJECT_GROUP_HEADER
#define STEP_OBJECT_GROUP_HEADER

#include <vector>  // vector

#include "common.hpp"
#include "object.hpp"

namespace step {

enum class object_group_draw_order
{
  top_down,
  index
};

struct object_group final
{
  object_group_draw_order order;
  std::vector<object> objects;
};

inline void from_json(const json& json, object_group& group)
{
  json.at("draworder").get_to(group.order);

  group.objects.reserve(json.size());
  for (const auto& [key, value] : json.at("objects").items()) {
    group.objects.emplace_back(value);
  }
}

NLOHMANN_JSON_SERIALIZE_ENUM(object_group_draw_order,
                             {{object_group_draw_order::index, "index"},
                              {object_group_draw_order::top_down, "topdown"}})

}  // namespace step

#endif  // STEP_OBJECT_GROUP_HEADER
