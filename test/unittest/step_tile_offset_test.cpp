#include "step_tile_offset.hpp"

#include <doctest.h>

#include "step_utils.hpp"

using namespace step;

TEST_SUITE("TileOffset")
{
  TEST_CASE("Valid tile offset")
  {
    const tile_offset offset{
        detail::parse_json("resource/tileoffset/tile_offset.json")};
    CHECK(offset.x() == 123);
    CHECK(offset.y() == 829);
  }
}
