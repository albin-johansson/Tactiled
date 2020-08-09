#include "step_layer.hpp"

#include <doctest.h>

#include <string>

#include "step_utils.hpp"

using namespace step;

TEST_SUITE("Layer")
{
  TEST_CASE("Parsing tile layer")
  {
    const Layer layer{detail::parse_json("resource/layer/tile_layer.json")};

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
        CHECK(tileLayer.data());
        CHECK_NOTHROW(tileLayer.data()->as_gid());
        CHECK(tileLayer.data()->as_gid().size() == 1024);
        CHECK_THROWS(tileLayer.data()->as_base64());
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
      const auto* properties = layer.properties();
      REQUIRE(properties);
      REQUIRE(properties->amount() == 2);

      const auto& first = properties->get("foo");
      CHECK(first.name() == "foo");
      CHECK(first.is<int>());
      CHECK(first.get<int>() == 79);

      const auto& second = properties->get("bar");
      CHECK(second.name() == "bar");
      CHECK(!second.get<bool>());
    }
  }

  TEST_CASE("Parse tile layer chunks")
  {
    const auto json = detail::parse_json("resource/layer/chunks.json");
    const Layer layer{json};
    const auto& chunks = layer.as_tile_layer().chunks();
    CHECK(chunks.size() == 4);
  }

  TEST_CASE("Parsing object group")
  {
//    const Layer layer{detail::parse_json("resource/layer/object_group.json")};

//    SUBCASE("Layer type indicators")
//    {
//      REQUIRE(layer.is_object_group());
//      CHECK(!layer.is_image_layer());
//      CHECK(!layer.is_tile_layer());
//      CHECK(!layer.is_group());
//    }
//
//    SUBCASE("Conversions")
//    {
//      CHECK_THROWS(layer.as_tile_layer());
//      CHECK_THROWS(layer.as_image_layer());
//      CHECK_THROWS(layer.as_group());
//    }
//
//    SUBCASE("Object group exclusive properties")
//    {
//      const auto& objectGroup = layer.as_object_group();
//      CHECK(objectGroup.draw_order() == ObjectGroup::DrawOrder::TopDown);
//
//      const auto& objects = objectGroup.objects();
//      REQUIRE(objects.size() == 1);
//
//      const auto& object = objects.at(0);
//      CHECK(object->id() == 36);
//      CHECK(object->x() == 234);
//      CHECK(object->y() == 584);
//      CHECK(object->width() == 118);
//      CHECK(object->height() == 77);
//      CHECK(object->rotation() == 3);
//      CHECK(object->visible());
//      CHECK(object->name() == "legolas");
//      CHECK(object->type() == "boss");
//    }

//    CHECK(layer.id() == 3);
//    CHECK(layer.name() == "object_layer");
//    CHECK(layer.opacity() == 0.4);
//    CHECK(layer.type() == Layer::Type::ObjectGroup);
//    CHECK(!layer.visible());
//    CHECK(layer.start_x() == 0);
//    CHECK(layer.start_y() == 0);
//    CHECK(layer.offset_x() == 65);
//    CHECK(layer.offset_y() == 173);
  }

  TEST_CASE("Parsing image layer")
  {
    const Layer layer{detail::parse_json("resource/layer/image_layer.json")};

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
      CHECK(*imageLayer.transparent_color() == Color{"#214365"});
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

  TEST_CASE("Parsing group")
  {
    const Layer layer{detail::parse_json("resource/layer/group.json")};

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
      const auto& group = layer.as_group();
      REQUIRE(group.layers() == 1);

      group.each([](const Layer& layer) { CHECK(layer.name() == "dawkins"); });

      CHECK(group.at(0).name() == "dawkins");
    }

    CHECK(layer.id() == 7);
    CHECK(layer.name() == "group_layer");
    CHECK(layer.opacity() == 0.9);
    CHECK(layer.type() == Layer::Type::Group);
    CHECK(layer.visible());
  }
}