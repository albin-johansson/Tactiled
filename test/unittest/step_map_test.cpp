#include <doctest.h>

#include "map.hpp"
#include "step_exception.hpp"
#include "step_test_utils.h"

TEST_SUITE("map")
{
  TEST_CASE("Parsing map")
  {
    const step::map map{"resource/map/basic_map.json"};

    CHECK(map.width() == 88);
    CHECK(map.height() == 94);
    CHECK(map.tile_width() == 28);
    CHECK(map.tile_height() == 32);
    CHECK(map.json_version() == 1.2);
    CHECK(map.next_layer_id() == 2);
    CHECK(map.next_object_id() == 1);
    CHECK(map.orientation() == step::map_orientation::orthogonal);
    CHECK(map.render_order() == step::map_render_order::right_down);
    CHECK(map.tiled_version() == "1.3.4");
    CHECK(!map.get_properties());
    CHECK(!map.infinite());

    SUBCASE("Test layers")
    {
      const auto& layers = map.layers();
      REQUIRE(layers.size() == 1);

      const auto& layer = layers.front();
      CHECK(layer.id() == 1);
      CHECK(!layer.as<step::tile_layer>().data()->as_gid().empty());
      CHECK(layer.width() == 45);
      CHECK(layer.height() == 125);
      CHECK(layer.opacity() == 1);
      CHECK(layer.name() == "herbert");
      CHECK(layer.get_type() == step::layer::type::tile_layer);
      CHECK(layer.visible());
    }
  }

  TEST_CASE("No type attribute")
  {
    CHECK_THROWS_WITH_AS(step::map("resource/map/no_type.json"),
                         "Map \"type\" attribute must be \"map\"!",
                         step::step_exception);
  }
}
