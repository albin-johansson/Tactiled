#include "step_map.h"

#include <doctest.h>

using namespace step;

TEST_SUITE("TiledMap")
{
  TEST_CASE("TiledMap::value")
  {
    TiledMap map;
    CHECK(map.value() == 1);
  }
}
