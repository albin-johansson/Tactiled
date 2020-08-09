#include "step_animation.hpp"

#include "step_frame.hpp"
#include "step_utils.hpp"

namespace step {

animation::animation(const json& json)
    : m_frames{detail::fill<std::vector<Frame>>(json)}
{}

auto animation::frames() const -> const std::vector<Frame>&
{
  return m_frames;
}

auto animation::num_frames() const noexcept -> int
{
  return static_cast<int>(m_frames.size());
}

}  // namespace step
