#include <doctest.h>

#include "frame.hpp"
#include "step_detail.hpp"

TEST_SUITE("Frame")
{
  TEST_CASE("Parsing valid frame object")
  {
    const step::frame frame =
        step::detail::parse_json("resource/frame/frame_complete.json");
    CHECK(frame.tile == 6227);
    CHECK(frame.duration == 598);
  }
}