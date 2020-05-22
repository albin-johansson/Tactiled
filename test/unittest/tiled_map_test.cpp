#include "tiled_map.h"

#include <doctest.h>

using namespace tactiled;

TEST_SUITE("TiledMap")
{
  TEST_CASE("TiledMap::value")
  {
    TiledMap map;
    CHECK(map.value() == 1);
  }
}
