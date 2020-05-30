#include "step_tile_offset.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/tileoffset/";

TEST_SUITE("TileOffset")
{
  TEST_CASE("Valid tile offset")
  {
    const auto offset = test::make<TileOffset>(prefix, "tile_offset.json");
    CHECK(offset.x() == 123);
    CHECK(offset.y() == 829);
  }
}
