#include "step_wang_set.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("WangSet")
{
  TEST_CASE("Parsing valid Wang set")
  {
    const auto json = detail::parse_json("resource/wangset/valid.json");
    const WangSet wangSet{json};

    CHECK(wangSet.name() == "candyAppleRed");
    CHECK(wangSet.tile_id() == 4);

    SUBCASE("Check corner colors")
    {
      REQUIRE(wangSet.corner_colors().size() == 1);

      const auto& color = wangSet.corner_colors().at(0);
      CHECK(color.color() == Color{"#CDEA34"});
      CHECK(color.name() == "CornerColor");
      CHECK(color.probability() == 0.23);
      CHECK(color.tile() == 9);
    }

    SUBCASE("Check edge colors")
    {
      REQUIRE(wangSet.edge_colors().size() == 1);

      const auto& color = wangSet.edge_colors().at(0);
      CHECK(color.color() == Color{"#A5BDCE"});
      CHECK(color.name() == "EdgeColor");
      CHECK(color.probability() == 0.55);
      CHECK(color.tile() == 4);
    }

    SUBCASE("Check Wang tiles")
    {
      REQUIRE(wangSet.wang_tiles().size() == 1);

      const auto& wangTiles = wangSet.wang_tiles();
      REQUIRE(wangTiles.size() == 1);

      const auto& tile = wangTiles.at(0);
      CHECK(tile.tile_id() == 3);
      CHECK(!tile.flipped_diagonally());
      CHECK(!tile.flipped_horizontally());
      CHECK(!tile.flipped_vertically());

      const auto& indices = tile.wang_color_indices();
      CHECK(std::get<0>(indices) == 1);
      CHECK(std::get<1>(indices) == 0);
      CHECK(std::get<2>(indices) == 1);
      CHECK(std::get<3>(indices) == 0);
      CHECK(std::get<4>(indices) == 2);
      CHECK(std::get<5>(indices) == 0);
      CHECK(std::get<6>(indices) == 2);
      CHECK(std::get<7>(indices) == 0);
    }

    SUBCASE("Check properties")
    {
      const auto& properties = wangSet.properties();
      REQUIRE(properties.amount() == 1);

      const auto& prop = properties.get("wangSetProp");
      CHECK(prop.name() == "wangSetProp");
      CHECK(prop.type() == Property::Type::Int);
      CHECK(*prop.as_int() == 993);
    }
  }
}