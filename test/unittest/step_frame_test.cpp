#include <doctest.h>

#include "frame.hpp"
#include "utils.hpp"

using step::operator""_lid;

TEST_SUITE("Frame")
{
  TEST_CASE("Parsing valid frame object")
  {
    const step::frame frame{
        step::detail::parse_json("resource/frame/frame_complete.json")};
    CHECK(frame.tile_id() == 6227_lid);
    CHECK(frame.duration() == 598);
  }
}