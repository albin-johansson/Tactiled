#include "step_frame.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("Frame")
{
  TEST_CASE("Defaults")
  {
    Frame frame;
    CHECK(frame.tile_id() == 0);
    CHECK(frame.duration() == 0);
  }

  TEST_CASE("Parsing valid frame object")
  {
    const auto json = detail::parse_json("resource/frame/frame_complete.json");
    const auto frame = json.get<Frame>();

    CHECK(frame.tile_id() == 6227);
    CHECK(frame.duration() == 598);
  }
}