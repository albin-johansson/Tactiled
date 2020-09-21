#include "step.hpp"

#include <doctest.h>

#include <iostream>

#include "step_types.hpp"

using namespace step;

TEST_SUITE("Test of realistic usage of step")
{
  TEST_CASE("Parsing map with two tilesets")
  {
    auto map = parse("resource/real/map.json");

    CHECK(map->width() == 50);
    CHECK(map->height() == 50);
    CHECK(map->next_object_id() == 1);
    CHECK(map->next_layer_id() == 4);
    CHECK(map->orientation() == Map::Orientation::Orthogonal);
    CHECK(map->render_order() == Map::RenderOrder::RightDown);
    CHECK(map->tile_width() == 32);
    CHECK(map->tile_height() == 32);
    CHECK(map->json_version() == 1.2);
    CHECK(map->tiled_version() == "1.3.0");
    CHECK(!map->infinite());

    SUBCASE("Layers")
    {
      const auto& layers = map->layers();
      REQUIRE(layers.size() == 3);

      CHECK(layers.at(0).id() == 1);
      CHECK(layers.at(0).name() == "ground1");
      CHECK(layers.at(0).is<step::tile_layer>());

      CHECK(layers.at(1).id() == 2);
      CHECK(layers.at(1).name() == "ground2");
      CHECK(layers.at(1).is<step::tile_layer>());

      CHECK(layers.at(2).id() == 3);
      CHECK(layers.at(2).name() == "detail");
      CHECK(layers.at(2).is<step::tile_layer>());
    }

    SUBCASE("Tilesets")
    {
      const auto& tilesets = map->tilesets();
      REQUIRE(tilesets.size() == 2);

      CHECK(tilesets.at(0).first_gid() == 1_gid);
      CHECK(tilesets.at(0).source() == "terrain.json");

      CHECK(tilesets.at(1).first_gid() == 1025_gid);
      CHECK(tilesets.at(1).source() == "outside.json");
    }
  }
}
