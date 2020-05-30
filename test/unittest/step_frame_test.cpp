#include "step_frame.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/frame/";

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
    const auto frame = test::make<Frame>(prefix, "frame_complete.json");

    CHECK(frame.tile_id() == 6227);
    CHECK(frame.duration() == 598);
  }
}