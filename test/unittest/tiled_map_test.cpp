#include <catch.hpp>

#include "tiled_map.h"

using namespace tactiled;

TEST_CASE("TiledMap::value", "[TiledMap]")
{
  TiledMap map;
  CHECK(map.value() == 1);
}
