#include "step_tileset.hpp"

#include <doctest.h>

#include <string_view>

#include "step_exception.hpp"
#include "step_test_utils.h"

using namespace step;

inline static constexpr std::string_view prefix = "resource/tileset/";

TEST_SUITE("Tileset")
{
  TEST_CASE("Parsing external tileset")
  {
    const auto tileset = Tileset::external(
        prefix, 4_gid, "tileset_data_for_external_tileset.json");

    CHECK(tileset->columns() == 32);
    CHECK(tileset->first_gid() == 4_gid);
    CHECK(tileset->source() == "tileset_data_for_external_tileset.json");
    CHECK(tileset->image() == "../terrain.png");
    CHECK(tileset->image_width() == 1024);
    CHECK(tileset->image_height() == 768);
    CHECK(tileset->margin() == 18);
    CHECK(tileset->name() == "external_tileset");
    CHECK(tileset->spacing() == 7);
    CHECK(tileset->tile_count() == 1024);
    CHECK(tileset->tile_width() == 64);
    CHECK(tileset->tile_height() == 32);
    CHECK(tileset->json_version() == 1.2);
    CHECK(tileset->tiled_version() == "1.3.4");
    CHECK(!tileset->get_grid());
    CHECK(!tileset->get_tile_offset());
  }

  TEST_CASE("Parsing embedded tileset")
  {
    const auto tileset = Tileset::embedded(
        detail::parse_json("resource/tileset/embedded_tileset.json"));

    CHECK(tileset->first_gid() == 7_gid);
    CHECK(tileset->columns() == 48);
    CHECK(tileset->source() == "");
    CHECK(tileset->image() == "sam/is/the/hero.png");
    CHECK(tileset->image_width() == 1270);
    CHECK(tileset->image_height() == 960);
    CHECK(tileset->margin() == 77);
    CHECK(tileset->name() == "embedded_tileset");
    CHECK(tileset->tile_count() == 63);
    CHECK(tileset->spacing() == 82);
    CHECK(tileset->tile_width() == 55);
    CHECK(tileset->tile_height() == 27);
    CHECK(tileset->background_color() == color{"#12345678"});
    CHECK(tileset->transparent_color() == color{"#CCDDEEFF"});
    CHECK(tileset->json_version() == 1.2);
    CHECK(tileset->tiled_version() == "1.3.4");

    SUBCASE("Parsing grid")
    {
      const auto grid = tileset->get_grid();
      REQUIRE(grid);
      CHECK(grid->get_orientation() == grid::orientation::isometric);
      CHECK(grid->width() == 48);
      CHECK(grid->height() == 64);
    }

    SUBCASE("Parsing tile offset")
    {
      const auto tileOffset = tileset->get_tile_offset();
      REQUIRE(tileOffset);
      CHECK(tileOffset->x() == 1574);
      CHECK(tileOffset->y() == 753);
    }

    SUBCASE("Parsing terrains")
    {
      const auto& terrains = tileset->terrains();
      REQUIRE(terrains.size() == 3);

      const auto& firstTerrain = terrains.at(0);
      CHECK(firstTerrain.name() == "ground");
      CHECK(firstTerrain.tile() == 4_lid);

      {
        REQUIRE(firstTerrain.get_properties()->amount() != 0);
        const auto property = firstTerrain.get_properties()->get("foo");
        CHECK(property.name() == "foo");
        REQUIRE(property.get_type() == property::type::boolean);
        CHECK(property.get<bool>());
      }

      const auto& secondTerrain = terrains.at(1);
      CHECK(secondTerrain.name() == "chasm");
      CHECK(secondTerrain.tile() == 12_lid);

      const auto& thirdTerrain = terrains.at(2);
      CHECK(thirdTerrain.name() == "cliff");
      CHECK(thirdTerrain.tile() == 36_lid);
    }
  }

  TEST_CASE("Tileset with properties")
  {
    const auto tileset = Tileset::embedded(
        detail::parse_json("resource/tileset/with_properties.json"));
    const auto* properties = tileset->get_properties();

    REQUIRE(properties);
    REQUIRE(properties->amount() == 2);

    const auto& firstProperty = properties->get("aFloat");
    CHECK(firstProperty.name() == "aFloat");
    CHECK(firstProperty.get_type() == property::type::floating);
    CHECK(firstProperty.get<float>() == 7.5f);

    const auto& secondProperty = properties->get("aString");
    CHECK(secondProperty.name() == "aString");
    CHECK(secondProperty.get_type() == property::type::string);
    CHECK(secondProperty.get<std::string>() == "Hello");
  }

  TEST_CASE("Tileset with tiles")
  {
    SUBCASE("Check first tile")
    {
      const auto tileset = Tileset::embedded(
          detail::parse_json("resource/tileset/with_tiles.json"));
      const auto& tiles = tileset->tiles();

      REQUIRE(tiles.size() == 2);
      const auto& tile = tiles.at(0);

      CHECK(tile.id() == 187_lid);

      SUBCASE("Animation")
      {
        const auto animation = tile.get_animation();
        REQUIRE(animation);
        CHECK(animation->num_frames() == 3);

        const auto& frames = animation->frames();
        for (int i = 0; i < 3; ++i) {
          CHECK(frames.at(i).duration() == 900);
          CHECK(frames.at(i).tile_id() == 187_lid + local_id{i});
        }
      }

      SUBCASE("Properties")
      {
        const auto* properties = tile.get_properties();
        REQUIRE(properties);
        REQUIRE(properties->amount() == 1);

        const auto& property = properties->get("name");
        CHECK(property.name() == "name");
        CHECK(property.get_type() == property::type::string);
        CHECK(property.get<std::string>() == "waterTile");
      }
    }

    SUBCASE("Check second tile")
    {
      const auto tileset = Tileset::embedded(
          detail::parse_json("resource/tileset/with_tiles.json"));
      auto& tiles = tileset->tiles();

      REQUIRE(tiles.size() == 2);
      const auto& tile = tiles.at(1);

      CHECK(tile.id() == 370_lid);

      SUBCASE("Properties")
      {
        const auto properties = tile.get_properties();
        REQUIRE(properties->amount() == 2);

        const auto& firstProperty = properties->get("coolness");
        CHECK(firstProperty.name() == "coolness");
        REQUIRE(firstProperty.get_type() == property::type::integer);
        CHECK(firstProperty.get<int>() == 9000);

        const auto& secondProperty = properties->get("frodo");
        CHECK(secondProperty.name() == "frodo");
        REQUIRE(secondProperty.get_type() == property::type::string);
        CHECK(secondProperty.get<std::string>() == "sandTile");
      }
    }
  }

  TEST_CASE("Embedded tileset without explicit first GID")
  {
    const auto tileset = Tileset::embedded(
        detail::parse_json("resource/tileset/embedded_tileset_no_gid.json"));
    CHECK(tileset->first_gid() == 1_gid);
  }

  TEST_CASE("Tileset missing type attribute")
  {
    CHECK_THROWS_WITH_AS(Tileset::embedded(detail::parse_json(
                             "resource/tileset/tileset_wrong_type.json")),
                         "Tileset \"type\" must be \"tileset\"!",
                         step_exception);
  }
}
