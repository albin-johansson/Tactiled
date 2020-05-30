#include "step_terrain.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/terrain/";

TEST_SUITE("Terrain")
{
  TEST_CASE("Parsing complete terrain")
  {
    const auto terrain = test::make<Terrain>(prefix, "complete.json");
    CHECK(terrain.tile() == 64);
    CHECK(terrain.name() == "water");
    REQUIRE(!terrain.properties().empty());

    const auto property = terrain.properties().get("health");
    CHECK(property.name() == "health");
    REQUIRE(property.type() == Property::Type::Int);
    CHECK(*property.as_int() == 87);
  }

  TEST_CASE("Parsing terrain with no properties")
  {
    const auto terrain = test::make<Terrain>(prefix, "no_properties.json");
    CHECK(terrain.tile() == 77);
    CHECK(terrain.name() == "lava");
    CHECK(terrain.properties().empty());
  }
}
