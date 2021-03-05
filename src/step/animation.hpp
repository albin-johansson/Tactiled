#ifndef STEP_ANIMATION_HEADER
#define STEP_ANIMATION_HEADER

#include <vector>

#include "frame.hpp"
#include "step_api.hpp"
#include "types.hpp"
#include "utils.hpp"

namespace step {

/**
 * @class animation
 *
 * @brief Represents a collection of frames, used to animate tiles.
 *
 * @since 0.1.0
 *
 * @todo Add begin() and end(), maybe even at() & operator[].
 *
 * @headerfile step_animation.hpp
 */
class animation final
{
 public:
  explicit animation(const json& json)
      : m_frames{detail::fill<std::vector<Frame>>(json)}
  {}

  /**
   * @brief Returns the frames associated with the animation.
   *
   * @return the frames associated with the animation.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto frames() const -> const std::vector<Frame>&
  {
    return m_frames;
  }

  /**
   * @brief Returns the amount of frames that constitute the animation.
   *
   * @return the amount of frames that constitute the animation.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto num_frames() const noexcept -> int
  {
    return static_cast<int>(m_frames.size());
  }

 private:
  std::vector<Frame> m_frames;
};

}  // namespace step

#endif  // STEP_ANIMATION_HEADER
