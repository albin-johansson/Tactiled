#include "step_layer.h"

#include <doctest.h>

#include <string>

#include "step_exception.h"
#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/layer/";

TEST_SUITE("Layer")
{
  TEST_CASE("Parsing minimum tile layer")
  {
    const auto layer = test::make<Layer>(prefix, "tile_layer_min.json");

    SUBCASE("Layer type indicators")
    {
      REQUIRE(layer.is_tile_layer());
      CHECK(!layer.is_image_layer());
      CHECK(!layer.is_object_group());
      CHECK(!layer.is_group());
    }

    SUBCASE("Tile layer exclusive properties")
    {
      SUBCASE("Check default encoding")
      {
        const auto encoding = layer.encoding();
        REQUIRE(encoding);
        CHECK(encoding == Layer::Encoding::CSV);
      }

      SUBCASE("Check default compression")
      {
        const auto compression = layer.compression();
        REQUIRE(compression);
        CHECK(compression == Layer::Compression::None);
      }

      SUBCASE("Check data")
      {
        CHECK_NOTHROW(layer.data());
        CHECK_THROWS(layer.base64_data());
      }
    }

    SUBCASE("Object group exclusive properties")
    {
      // TODO test objects as well
      CHECK(!layer.draw_order());
    }

    SUBCASE("Image layer exclusive properties")
    {
      CHECK(!layer.image());
      CHECK(!layer.transparent_color());
    }

    SUBCASE("Group exclusive properties")
    {
      // TODO test layers here
    }

    CHECK(layer.id() == 1);
    CHECK(layer.width() == 32);
    CHECK(layer.height() == 28);
    CHECK(layer.name() == "tile_layer");
    CHECK(layer.opacity() == 0.7);
    CHECK(layer.type() == Layer::Type::TileLayer);
    CHECK(layer.visible());
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

    SUBCASE("Tile layer exclusive properties")
    {
      CHECK(!layer.encoding());
      CHECK(!layer.compression());

      CHECK_THROWS_WITH_AS(
          layer.data(), "Layer > Failed to obtain GID data!", StepException);

      CHECK_THROWS_WITH_AS(layer.base64_data(),
                           "Layer > Failed to obtain Base64 data!",
                           StepException);
    }

    SUBCASE("Object group exclusive properties")
    {
      // TODO test objects as well
      const auto drawOrder = layer.draw_order();
      REQUIRE(drawOrder);
      CHECK(drawOrder == Layer::DrawOrder::TopDown);
    }

    SUBCASE("Image layer exclusive properties")
    {
      CHECK(!layer.image());
      CHECK(!layer.transparent_color());
    }

    SUBCASE("Group exclusive properties")
    {
      // TODO test layers here
    }

    CHECK(layer.id() == 3);
    CHECK(layer.name() == "object_layer");
    CHECK(layer.opacity() == 0.4);
    CHECK(layer.type() == Layer::Type::ObjectGroup);
    CHECK(!layer.visible());
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

    SUBCASE("Tile layer exclusive properties")
    {
      CHECK(!layer.encoding());
      CHECK(!layer.compression());
      CHECK_THROWS(layer.data());
      CHECK_THROWS(layer.base64_data());
    }

    SUBCASE("Object group exclusive properties")
    {
      // TODO test objects as well
      CHECK(!layer.draw_order());
    }

    SUBCASE("Image layer exclusive properties")
    {
      SUBCASE("Test image")
      {
        const auto image = layer.image();
        REQUIRE(image);
        CHECK(*image == "balrog.png");
      }

      CHECK(!layer.transparent_color());  // Optional property
    }

    SUBCASE("Group exclusive properties")
    {
      // TODO test layers here
    }

    CHECK(layer.id() == 2);
    CHECK(layer.name() == "image_layer");
    CHECK(layer.opacity() == 1);
    CHECK(layer.type() == Layer::Type::ImageLayer);
    CHECK(layer.visible());
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

    SUBCASE("Tile layer exclusive properties")
    {
      CHECK(!layer.encoding());
      CHECK(!layer.compression());
      CHECK_THROWS(layer.data());
      CHECK_THROWS(layer.base64_data());
    }

    SUBCASE("Object group exclusive properties")
    {
      // TODO test objects as well
      CHECK(!layer.draw_order());
    }

    SUBCASE("Image layer exclusive properties")
    {
      CHECK(!layer.image());
      CHECK(!layer.transparent_color());
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