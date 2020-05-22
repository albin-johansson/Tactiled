#include <doctest.h>

#include "tactiled_map.h"

using namespace tactiled;

TEST_SUITE("TiledMap")
{
  TEST_CASE("TiledMap::value")
  {
    TiledMap map;
    CHECK(map.value() == 1);
  }
}
