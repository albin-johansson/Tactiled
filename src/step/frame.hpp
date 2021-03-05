#ifndef STEP_FRAME_HEADER
#define STEP_FRAME_HEADER

#include "common.hpp"

namespace step {

struct frame final
{
  local_id tile;
  int duration;
};

inline void from_json(const json& json, frame& frame)
{
  frame.tile = json.at("tileid").get<int>();
  frame.duration = json.at("duration").get<int>();
}

}  // namespace step

#endif  // STEP_FRAME_HEADER