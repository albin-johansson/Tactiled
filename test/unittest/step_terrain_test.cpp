#include "step_terrain.h"

#include <doctest.h>

#include <string_view>

#include "step_utils.h"

using namespace step;

namespace {

[[nodiscard]] Terrain mk_terrain(std::string_view file)
{
  using namespace std::string_literals;
  const auto path = "resource/terrain/"s + file.data();
  const auto json = detail::parse_json(path);
  return json.get<Terrain>();
}

}  // namespace

TEST_SUITE("Terrain")
{
  TEST_CASE("Parsing complete terrain")
  {
    const auto terrain = mk_terrain("complete.json");
    CHECK(terrain.tile() == 64);
    CHECK(terrain.name() == "water");
    REQUIRE(!terrain.properties().empty());

    const auto property = terrain.properties().at(0);
    CHECK(property.name() == "health");
    REQUIRE(property.type() == Property::Type::Int);
    CHECK(*property.as_int() == 87);
  }

  TEST_CASE("Parsing terrain with no properties")
  {
    const auto terrain = mk_terrain("no_properties.json");
    CHECK(terrain.tile() == 77);
    CHECK(terrain.name() == "lava");
    CHECK(terrain.properties().empty());
  }
}
