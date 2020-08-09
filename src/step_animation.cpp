#include "step_animation.h"

#include "step_frame.h"
#include "step_utils.h"

namespace step {

Animation::Animation(const json& json)
    : m_frames{detail::fill<std::vector<Frame>>(json)}
{}

const std::vector<Frame>& Animation::frames() const
{
  return m_frames;
}

int Animation::length() const noexcept
{
  return static_cast<int>(m_frames.size());
}

}  // namespace step
