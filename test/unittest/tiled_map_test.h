#include <doctest.h>

#include "tiled_map.h"

using namespace tactiled;

TEST_CASE("Tiled map")
{
  TiledMap map;
  CHECK(map.value() == 1);
}