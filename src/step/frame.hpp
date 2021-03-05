#ifndef STEP_FRAME_HEADER
#define STEP_FRAME_HEADER

#include "step_api.hpp"
#include "types.hpp"

namespace step {

/**
 * The Frame class represents a frame in an animation.
 *
 * \since 0.1.0
 */
class frame final
{
 public:
  explicit frame(const json& json)
      : m_tileID{json.at("tileid").get<int>()}
      , m_duration{json.at("duration").get<int>()}
  {}

  /**
   * Returns the local tile ID that is associated with the frame.
   *
   * \return the local tile ID that is associated with the frame.
   * \since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tileID;
  }

  /**
   * Returns the duration of this frame, in milliseconds.
   *
   * \return the duration of this frame, in milliseconds.
   * \since 0.1.0
   */
  [[nodiscard]] auto duration() const noexcept -> int
  {
    return m_duration;
  }

 private:
  local_id m_tileID{0};
  int m_duration{0};
};

}  // namespace step

#endif  // STEP_FRAME_HEADER