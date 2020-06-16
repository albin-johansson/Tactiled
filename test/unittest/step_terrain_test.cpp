#include "step_terrain.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("Terrain")
{
  TEST_CASE("Parsing complete terrain")
  {
    const Terrain terrain{detail::parse_json("resource/terrain/complete.json")};
    CHECK(terrain.tile() == 64_lid);
    CHECK(terrain.name() == "water");
    REQUIRE(!terrain.properties().empty());

    const auto property = terrain.properties().get("health");
    CHECK(property.name() == "health");
    REQUIRE(property.type() == Property::Type::Int);
    CHECK(property.get<int>() == 87);
  }

  TEST_CASE("Parsing terrain with no properties")
  {
    const Terrain terrain{
        detail::parse_json("resource/terrain/no_properties.json")};
    CHECK(terrain.tile() == 77_lid);
    CHECK(terrain.name() == "lava");
    CHECK(terrain.properties().empty());
  }
}
