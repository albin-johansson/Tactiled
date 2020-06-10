#include "step_tile.h"

#include <doctest.h>

#include "step_layer.h"
#include "step_utils.h"

using namespace step;

TEST_SUITE("Tile")
{
  TEST_CASE("Parse tile with all keys")
  {
    const Tile tile{detail::parse_json("resource/tile/tile_complete.json")};

    CHECK(tile.id() == 74);

    CHECK(tile.type());
    CHECK(*tile.type() == "foo");

    CHECK(tile.probability());
    CHECK(*tile.probability() == 0.4);

    CHECK(tile.image());
    CHECK(*tile.image() == "some_image.png");

    CHECK(tile.image_width());
    CHECK(*tile.image_width() == 1024);

    CHECK(tile.image_height());
    CHECK(*tile.image_height() == 768);

    SUBCASE("Testing parsing of animation")
    {
      const auto animation = tile.animation();

      CHECK(animation);
      CHECK(animation->length() == 2);

      const auto firstFrame = animation->frames().at(0);
      CHECK(firstFrame.tile_id() == 23);
      CHECK(firstFrame.duration() == 384);

      const auto secondFrame = animation->frames().at(1);
      CHECK(secondFrame.tile_id() == 174);
      CHECK(secondFrame.duration() == 159);
    }

    SUBCASE("Testing parsing of properties")
    {
      const auto properties = tile.properties();

      const auto first = properties.get("Galadriel");
      CHECK(first.name() == "Galadriel");
      CHECK(first.type() == Property::Type::String);
      CHECK(first.as_string());
      CHECK(*first.as_string() == "Denethor sucks");

      const auto second = properties.get("Gandalf");
      CHECK(second.name() == "Gandalf");
      CHECK(second.type() == Property::Type::Int);
      CHECK(second.as_int());
      CHECK(*second.as_int() == 7);
    }

    SUBCASE("Testing parsing of terrain")
    {
      CHECK(tile.terrain_at(Tile::TerrainPos::TopLeft) == 8);
      CHECK(tile.terrain_at(Tile::TerrainPos::TopRight) == 2);
      CHECK(tile.terrain_at(Tile::TerrainPos::BottomLeft) == 5);
      CHECK(tile.terrain_at(Tile::TerrainPos::BottomRight) == 7);
    }

    SUBCASE("Testing object group")
    {
      const auto objectGroupLayer = tile.object_group();
      REQUIRE(objectGroupLayer);
      REQUIRE(objectGroupLayer->is_object_group());
      CHECK(objectGroupLayer->id() == 2);
      CHECK(objectGroupLayer->name() == "wizard");
      CHECK(objectGroupLayer->opacity() == 1);
      CHECK(objectGroupLayer->visible());

      const auto& objectGroup = objectGroupLayer->as_object_group();
      CHECK(objectGroup.draw_order() == ObjectGroup::DrawOrder::Index);
      CHECK(objectGroup.objects().size() == 1);
    }
  }
}