#include "step_frame.hpp"

#include <doctest.h>

#include "step_utils.hpp"

using namespace step;

TEST_SUITE("Frame")
{
  TEST_CASE("Parsing valid frame object")
  {
    const Frame frame{detail::parse_json("resource/frame/frame_complete.json")};
    CHECK(frame.tile_id() == 6227_lid);
    CHECK(frame.duration() == 598);
  }
}