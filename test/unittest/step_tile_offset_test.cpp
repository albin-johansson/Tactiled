#include "step_tile_offset.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("TileOffset")
{
  TEST_CASE("Valid tile offset")
  {
    const TileOffset offset{
        detail::parse_json("resource/tileoffset/tile_offset.json")};
    CHECK(offset.x() == 123);
    CHECK(offset.y() == 829);
  }
}
