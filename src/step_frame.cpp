#include "step_frame.h"

namespace step {

Frame::Frame(const json& json)
    : m_tileID{json.at("tileid").get<int>()},
      m_duration{json.at("duration").get<int>()}
{}

local_id Frame::tile_id() const noexcept
{
  return m_tileID;
}

int Frame::duration() const noexcept
{
  return m_duration;
}

}  // namespace step
