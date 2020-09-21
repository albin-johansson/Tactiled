#include "step_tile.hpp"

#include <doctest.h>

#include "step_layer.hpp"
#include "step_utils.hpp"

using namespace step;

TEST_SUITE("Tile")
{
  TEST_CASE("Parse tile with all keys")
  {
    const auto json = detail::parse_json("resource/tile/tile_complete.json");
    const tile tile{json};

    CHECK(tile.id() == 74_lid);

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
      const auto animation = tile.get_animation();

      CHECK(animation);
      CHECK(animation->num_frames() == 2);

      const auto& firstFrame = animation->frames().at(0);
      CHECK(firstFrame.tile_id() == 23_lid);
      CHECK(firstFrame.duration() == 384);

      const auto& secondFrame = animation->frames().at(1);
      CHECK(secondFrame.tile_id() == 174_lid);
      CHECK(secondFrame.duration() == 159);
    }

    SUBCASE("Testing parsing of properties")
    {
      const auto* properties = tile.get_properties();
      REQUIRE(properties);

      const auto& first = properties->get("Galadriel");
      CHECK(first.name() == "Galadriel");
      CHECK(first.get_type() == property::type::string);
      CHECK(first.get<std::string>() == "Denethor sucks");

      const auto& second = properties->get("Gandalf");
      CHECK(second.name() == "Gandalf");
      CHECK(second.get_type() == property::type::integer);
      CHECK(second.get<int>() == 7);
    }

    SUBCASE("Testing parsing of terrain")
    {
      CHECK(tile.terrain_at(tile::terrain_pos::top_left) == 8);
      CHECK(tile.terrain_at(tile::terrain_pos::top_right) == 2);
      CHECK(tile.terrain_at(tile::terrain_pos::bottom_left) == 5);
      CHECK(tile.terrain_at(tile::terrain_pos::bottom_right) == 7);
    }

    SUBCASE("Testing object group")
    {
      const auto objectGroupLayer = tile.object_group();
      REQUIRE(objectGroupLayer);
      REQUIRE(objectGroupLayer->is<step::ObjectGroup>());
      CHECK(objectGroupLayer->id() == 2);
      CHECK(objectGroupLayer->name() == "wizard");
      CHECK(objectGroupLayer->opacity() == 1);
      CHECK(objectGroupLayer->visible());

      const auto& objectGroup = objectGroupLayer->as<step::ObjectGroup>();
      CHECK(objectGroup.draw_order() == ObjectGroup::DrawOrder::Index);
      CHECK(objectGroup.objects().size() == 1);
    }
  }
}