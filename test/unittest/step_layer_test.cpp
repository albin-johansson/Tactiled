#include <doctest.h>

#include <string>

#include "layer.hpp"
#include "step_detail.hpp"

using namespace step;

TEST_SUITE("layer")
{
  TEST_CASE("Parsing tile layer")
  {
    const layer layer{detail::parse_json("resource/layer/tile_layer.json")};

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is<step::tile_layer>());
      CHECK(!layer.is<step::image_layer>());
      CHECK(!layer.is<step::object_group>());
      CHECK(!layer.is<step::group>());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as<step::object_group>());  // NOLINT
      CHECK_THROWS(layer.as<step::image_layer>());   // NOLINT
      CHECK_THROWS(layer.as<step::group>());         // NOLINT

      CHECK(layer.try_as<step::tile_layer>());          // NOLINT
      CHECK_FALSE(layer.try_as<step::object_group>());  // NOLINT
      CHECK_FALSE(layer.try_as<step::image_layer>());   // NOLINT
      CHECK_FALSE(layer.try_as<step::group>());         // NOLINT
    }

    SUBCASE("Tile layer exclusive properties")
    {
      const auto& tileLayer = layer.as<step::tile_layer>();

      CHECK(tileLayer.get_encoding() == tile_layer::encoding::csv);
      CHECK(tileLayer.get_compression() == tile_layer::compression::none);
      CHECK(tileLayer.chunks().empty());

      SUBCASE("Check data")
      {
        CHECK(tileLayer.data());
        CHECK_NOTHROW(tileLayer.data()->as_gid());  // NOLINT
        CHECK(tileLayer.data()->as_gid().size() == 1024);
        CHECK_THROWS(tileLayer.data()->as_base64());  // NOLINT
      }
    }

    CHECK(layer.id() == 1);
    CHECK(layer.width() == 32);
    CHECK(layer.height() == 28);
    CHECK(layer.name() == "tile_layer");
    CHECK(layer.opacity() == 0.7);
    CHECK(layer.get_type() == layer::type::tile_layer);
    CHECK(layer.visible());
    CHECK(layer.start_x() == 0);
    CHECK(layer.start_y() == 0);
    CHECK(layer.offset_x() == 0);
    CHECK(layer.offset_y() == 0);

    SUBCASE("General properties test")
    {
      const auto* properties = layer.get_properties();
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
    const layer layer{json};
    const auto& chunks = layer.as<step::tile_layer>().chunks();
    CHECK(chunks.size() == 4);
  }

  TEST_CASE("Parsing object group")
  {
    const step::layer layer{
        detail::parse_json("resource/layer/object_group.json")};

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is<step::object_group>());
      CHECK(!layer.is<step::image_layer>());
      CHECK(!layer.is<step::tile_layer>());
      CHECK(!layer.is<step::group>());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as<step::tile_layer>());   // NOLINT
      CHECK_THROWS(layer.as<step::image_layer>());  // NOLINT
      CHECK_THROWS(layer.as<step::group>());        // NOLINT
    }

    CHECK(layer.try_as<step::object_group>());       // NOLINT
    CHECK_FALSE(layer.try_as<step::tile_layer>());   // NOLINT
    CHECK_FALSE(layer.try_as<step::image_layer>());  // NOLINT
    CHECK_FALSE(layer.try_as<step::group>());        // NOLINT

    SUBCASE("Object group exclusive properties")
    {
      const auto& objectGroup = layer.as<step::object_group>();
      CHECK(objectGroup.get_draw_order() == object_group::draw_order::top_down);

      const auto& objects = objectGroup.objects();
      REQUIRE(objects.size() == 1);

      const auto& object = objects.at(0);
      CHECK(object.id() == 36);
      CHECK(object.x() == 234);
      CHECK(object.y() == 584);
      CHECK(object.width() == 118);
      CHECK(object.height() == 77);
      CHECK(object.rotation() == 3);
      CHECK(object.visible());
      CHECK(object.name() == "legolas");
      CHECK(object.type() == "boss");
    }

    CHECK(layer.id() == 3);
    CHECK(layer.name() == "object_layer");
    CHECK(layer.opacity() == 0.4);
    CHECK(layer.get_type() == step::layer::type::object_group);
    CHECK(!layer.visible());
    CHECK(layer.start_x() == 0);
    CHECK(layer.start_y() == 0);
    CHECK(layer.offset_x() == 65);
    CHECK(layer.offset_y() == 173);
  }

  TEST_CASE("Parsing image layer")
  {
    const layer layer{detail::parse_json("resource/layer/image_layer.json")};

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is<step::image_layer>());
      CHECK(!layer.is<step::object_group>());
      CHECK(!layer.is<step::tile_layer>());
      CHECK(!layer.is<step::group>());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as<step::tile_layer>());    // NOLINT
      CHECK_THROWS(layer.as<step::object_group>());  // NOLINT
      CHECK_THROWS(layer.as<step::group>());         // NOLINT
    }

    CHECK(layer.try_as<step::image_layer>());         // NOLINT
    CHECK_FALSE(layer.try_as<step::tile_layer>());    // NOLINT
    CHECK_FALSE(layer.try_as<step::object_group>());  // NOLINT
    CHECK_FALSE(layer.try_as<step::group>());         // NOLINT

    SUBCASE("Image layer exclusive properties")
    {
      const auto& imageLayer = layer.as<step::image_layer>();
      CHECK(imageLayer.image == "balrog.png");
      CHECK(*imageLayer.color == step::color{"#214365"});
    }

    CHECK(layer.id() == 2);
    CHECK(layer.name() == "image_layer");
    CHECK(layer.opacity() == 1);
    CHECK(layer.get_type() == layer::type::image_layer);
    CHECK(layer.visible());
    CHECK(layer.start_x() == 82);
    CHECK(layer.start_y() == 37);
    CHECK(layer.offset_x() == 0);
    CHECK(layer.offset_y() == 0);
  }

  TEST_CASE("Parsing group")
  {
    const layer layer{detail::parse_json("resource/layer/group.json")};

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is<step::group>());
      CHECK(!layer.is<step::image_layer>());
      CHECK(!layer.is<step::object_group>());
      CHECK(!layer.is<step::tile_layer>());
    }

    SUBCASE("Conversions")
    {
      CHECK_THROWS(layer.as<step::tile_layer>());    // NOLINT
      CHECK_THROWS(layer.as<step::image_layer>());   // NOLINT
      CHECK_THROWS(layer.as<step::object_group>());  // NOLINT
    }

    CHECK(layer.try_as<step::group>());               // NOLINT
    CHECK_FALSE(layer.try_as<step::tile_layer>());    // NOLINT
    CHECK_FALSE(layer.try_as<step::object_group>());  // NOLINT
    CHECK_FALSE(layer.try_as<step::image_layer>());   // NOLINT

    SUBCASE("Group exclusive properties")
    {
      const auto& group = layer.as<step::group>();
      REQUIRE(group.num_layers() == 1);

      group.each(
          [](const step::layer& layer) { CHECK(layer.name() == "dawkins"); });

      CHECK(group.at(0).name() == "dawkins");
    }

    CHECK(layer.id() == 7);
    CHECK(layer.name() == "group_layer");
    CHECK(layer.opacity() == 0.9);
    CHECK(layer.get_type() == layer::type::group);
    CHECK(layer.visible());
  }
}
