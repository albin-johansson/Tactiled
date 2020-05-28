#include "step_tileset.h"

#include <doctest.h>

#include "step_exception.h"
#include "step_utils.h"

using namespace step;

namespace {

Tileset mk_tileset(std::string_view path)
{
  using namespace std::string_literals;
  const std::string actualPath = "resource/tileset/"s + path.data();
  const auto json = detail::parse_json(actualPath.c_str());
  return json.get<Tileset>();
}

}  // namespace

TEST_SUITE("Tileset")
{
  TEST_CASE("Parsing external tileset")
  {
    const auto tileset = mk_tileset("external_tileset.json");

    CHECK(tileset.columns() == 32);
    CHECK(tileset.first_gid() == 4);
    CHECK(tileset.source() ==
          "resource/tileset/tileset_data_for_external_tileset.json");
    CHECK(tileset.image() == "../terrain.png");
    CHECK(tileset.image_width() == 1024);
    CHECK(tileset.image_height() == 768);
    CHECK(tileset.margin() == 18);
    CHECK(tileset.name() == "external_tileset");
    CHECK(tileset.spacing() == 7);
    CHECK(tileset.tile_count() == 1024);
    CHECK(tileset.tile_width() == 64);
    CHECK(tileset.tile_height() == 32);
    CHECK(tileset.json_version() == 1.2);
    CHECK(tileset.tiled_version() == "1.3.4");
  }

  TEST_CASE("Parsing embedded tileset")
  {
    const auto tileset = mk_tileset("embedded_tileset.json");

    CHECK(tileset.first_gid() == 7);
    CHECK(tileset.columns() == 48);
    CHECK(tileset.source() == "");
    CHECK(tileset.image() == "sam/is/the/hero.png");
    CHECK(tileset.image_width() == 1270);
    CHECK(tileset.image_height() == 960);
    CHECK(tileset.margin() == 77);
    CHECK(tileset.name() == "embedded_tileset");
    CHECK(tileset.tile_count() == 63);
    CHECK(tileset.spacing() == 82);
    CHECK(tileset.tile_width() == 55);
    CHECK(tileset.tile_height() == 27);
    CHECK(tileset.json_version() == 1.2);
    CHECK(tileset.tiled_version() == "1.3.4");
  }

  TEST_CASE("Tileset with properties")
  {
    SUBCASE("Const properties")
    {
      const auto tileset = mk_tileset("with_properties.json");
      const auto& properties = tileset.properties();

      REQUIRE(properties.size() == 2);

      const auto firstProperty = properties.at(0);
      CHECK(firstProperty.name() == "aFloat");
      CHECK(firstProperty.type() == Property::Type::Float);
      REQUIRE(firstProperty.as_float());
      CHECK(firstProperty.as_float() == 7.5f);
    }

    SUBCASE("Non-const properties")
    {
      auto tileset = mk_tileset("with_properties.json");
      auto& properties = tileset.properties();

      const auto secondProperty = properties.at(1);

      CHECK(secondProperty.name() == "aString");
      CHECK(secondProperty.type() == Property::Type::String);
      REQUIRE(secondProperty.as_string());
      CHECK(secondProperty.as_string() == "Hello");
    }
  }

  TEST_CASE("Embedded tileset without explicit first GID")
  {
    const auto tileset = mk_tileset("embedded_tileset_no_gid.json");
    CHECK(tileset.first_gid() == 1);
  }

  TEST_CASE("Tileset missing type attribute")
  {
    CHECK_THROWS_WITH_AS(mk_tileset("tileset_wrong_type.json"),
                         "Tileset > \"type\" must be \"tileset\"!",
                         StepException);
  }
}
