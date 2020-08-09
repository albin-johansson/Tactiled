#include "step_terrain.hpp"

#include <doctest.h>

#include "step_utils.hpp"

TEST_SUITE("terrain")
{
  using step::operator""_lid;
  TEST_CASE("Parsing complete terrain")
  {
    const step::Terrain terrain{
        step::detail::parse_json("resource/terrain/complete.json")};
    CHECK(terrain.tile() == 64_lid);
    CHECK(terrain.name() == "water");
    REQUIRE(terrain.get_properties());

    const auto& property = terrain.get_properties()->get("health");
    CHECK(property.name() == "health");
    REQUIRE(property.get_type() == step::property::type::integer);
    CHECK(property.get<int>() == 87);
  }

  TEST_CASE("Parsing terrain with no properties")
  {
    const step::Terrain terrain{
        step::detail::parse_json("resource/terrain/no_properties.json")};
    CHECK(terrain.tile() == 77_lid);
    CHECK(terrain.name() == "lava");
    CHECK(!terrain.get_properties());
  }
}
