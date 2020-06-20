#include "step_map.h"

#include <doctest.h>

#include "step_exception.h"
#include "step_test_utils.h"

using namespace step;

inline const std::string prefix = "resource/map/";

TEST_SUITE("Map")
{
  TEST_CASE("Parsing map")
  {
    const Map map{prefix, "basic_map.json"};

    CHECK(map.width() == 88);
    CHECK(map.height() == 94);
    CHECK(map.tile_width() == 28);
    CHECK(map.tile_height() == 32);
    CHECK(map.json_version() == 1.2);
    CHECK(map.next_layer_id() == 2);
    CHECK(map.next_object_id() == 1);
    CHECK(map.orientation() == Map::Orientation::Orthogonal);
    CHECK(map.render_order() == Map::RenderOrder::RightDown);
    CHECK(map.tiled_version() == "1.3.4");
    CHECK(!map.properties());
    CHECK(!map.infinite());

    SUBCASE("Test layers")
    {
      const auto& layers = map.layers();
      REQUIRE(layers.size() == 1);

      const auto& layer = layers.front();
      CHECK(layer.id() == 1);
      CHECK(!layer.as_tile_layer().data()->as_gid().empty());
      CHECK(layer.width() == 45);
      CHECK(layer.height() == 125);
      CHECK(layer.opacity() == 1);
      CHECK(layer.name() == "herbert");
      CHECK(layer.type() == Layer::Type::TileLayer);
      CHECK(layer.visible());
    }
  }

  TEST_CASE("No type attribute")
  {
    CHECK_THROWS_WITH_AS(Map(prefix, "no_type.json"),
                         "Map > \"type\" attribute must be \"map\"!",
                         StepException);
  }
}
