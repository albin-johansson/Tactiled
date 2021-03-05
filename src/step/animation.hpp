#ifndef STEP_ANIMATION_HEADER
#define STEP_ANIMATION_HEADER

#include <vector>  // vector

#include "common.hpp"
#include "frame.hpp"
#include "step_detail.hpp"

namespace step {

struct animation final
{
  std::vector<frame> frames;
};

inline void from_json(const json& json, animation& animation)
{
  animation.frames = detail::fill<std::vector<frame>>(json);
}

}  // namespace step

#endif  // STEP_ANIMATION_HEADER
