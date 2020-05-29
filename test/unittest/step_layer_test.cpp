#include "step_layer.h"

#include <doctest.h>

#include <string>

#include "step_exception.h"
#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/layer/";

TEST_SUITE("Layer")
{
  TEST_CASE("Parsing tile layer")
  {
    const auto layer = test::make<Layer>(prefix, "tile_layer.json");

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is_tile_layer());
      CHECK(!layer.is_image_layer());
      CHECK(!layer.is_object_group());
      CHECK(!layer.is_group());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as_object_group());
      CHECK_THROWS(layer.as_image_layer());
      CHECK_THROWS(layer.as_group());
    }

    SUBCASE("Tile layer exclusive properties")
    {
      const auto& tileLayer = layer.as_tile_layer();

      CHECK(tileLayer.encoding() == TileLayer::Encoding::CSV);
      CHECK(tileLayer.compression() == TileLayer::Compression::None);
      CHECK(tileLayer.chunks().empty());

      SUBCASE("Check data")
      {
        CHECK_NOTHROW(tileLayer.data().as_gid());
        CHECK(tileLayer.data().as_gid().size() == 1024);
        CHECK_THROWS(tileLayer.data().as_base64());
      }
    }

    CHECK(layer.id() == 1);
    CHECK(layer.width() == 32);
    CHECK(layer.height() == 28);
    CHECK(layer.name() == "tile_layer");
    CHECK(layer.opacity() == 0.7);
    CHECK(layer.type() == Layer::Type::TileLayer);
    CHECK(layer.visible());
    CHECK(layer.start_x() == 0);
    CHECK(layer.start_y() == 0);
    CHECK(layer.offset_x() == 0);
    CHECK(layer.offset_y() == 0);

    SUBCASE("General properties test")
    {
      REQUIRE(layer.properties().size() == 2);

      const auto first = layer.properties().at(0);
      CHECK(first.name() == "foo");
      CHECK(first.is_int());
      CHECK(*first.as_int() == 79);

      const auto second = layer.properties().at(1);
      CHECK(second.name() == "bar");
      CHECK(second.as_bool());
      CHECK(!*second.as_bool());
    }
  }

  TEST_CASE("Parse tile layer chunks")
  {
    const auto layer = test::make<Layer>(prefix, "chunks.json");
    const auto& chunks = layer.as_tile_layer().chunks();
    CHECK(chunks.size() == 4);
  }

  TEST_CASE("Parsing minimum object group")
  {
    const auto layer = test::make<Layer>(prefix, "object_group_min.json");

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is_object_group());
      CHECK(!layer.is_image_layer());
      CHECK(!layer.is_tile_layer());
      CHECK(!layer.is_group());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as_tile_layer());
      CHECK_THROWS(layer.as_image_layer());
      CHECK_THROWS(layer.as_group());
    }

    SUBCASE("Object group exclusive properties")
    {
      // TODO test objects as well
      const auto& objectGroup = layer.as_object_group();
      CHECK(objectGroup.draw_order() == ObjectGroup::DrawOrder::TopDown);
    }

    CHECK(layer.id() == 3);
    CHECK(layer.name() == "object_layer");
    CHECK(layer.opacity() == 0.4);
    CHECK(layer.type() == Layer::Type::ObjectGroup);
    CHECK(!layer.visible());
    CHECK(layer.start_x() == 0);
    CHECK(layer.start_y() == 0);
    CHECK(layer.offset_x() == 65);
    CHECK(layer.offset_y() == 173);
  }

  TEST_CASE("Parsing minimum image layer")
  {
    const auto layer = test::make<Layer>(prefix, "image_layer_min.json");

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is_image_layer());
      CHECK(!layer.is_object_group());
      CHECK(!layer.is_tile_layer());
      CHECK(!layer.is_group());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as_tile_layer());
      CHECK_THROWS(layer.as_object_group());
      CHECK_THROWS(layer.as_group());
    }

    SUBCASE("Image layer exclusive properties")
    {
      const auto& imageLayer = layer.as_image_layer();
      CHECK(imageLayer.image() == "balrog.png");
      CHECK(!imageLayer.transparent_color());  // Optional property
    }

    CHECK(layer.id() == 2);
    CHECK(layer.name() == "image_layer");
    CHECK(layer.opacity() == 1);
    CHECK(layer.type() == Layer::Type::ImageLayer);
    CHECK(layer.visible());
    CHECK(layer.start_x() == 82);
    CHECK(layer.start_y() == 37);
    CHECK(layer.offset_x() == 0);
    CHECK(layer.offset_y() == 0);
  }

  TEST_CASE("Parsing minimum group")
  {
    const auto layer = test::make<Layer>(prefix, "group_min.json");

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is_group());
      CHECK(!layer.is_image_layer());
      CHECK(!layer.is_object_group());
      CHECK(!layer.is_tile_layer());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as_tile_layer());
      CHECK_THROWS(layer.as_image_layer());
      CHECK_THROWS(layer.as_object_group());
    }

    SUBCASE("Group exclusive properties")
    {
      // TODO test layers here
    }

    CHECK(layer.id() == 7);
    CHECK(layer.name() == "group_layer");
    CHECK(layer.opacity() == 0.9);
    CHECK(layer.type() == Layer::Type::Group);
    CHECK(layer.visible());
  }
}