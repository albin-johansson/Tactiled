#include <doctest.h>

#include "utils.hpp"
#include "wang_tile.hpp"

using namespace step;

TEST_SUITE("WangTile")
{
  TEST_CASE("Parsing valid Wang tile")
  {
    const auto json = detail::parse_json("resource/wangtile/valid.json");
    const WangTile wangTile{json};
    CHECK(wangTile.tile_id() == 7_lid);
    CHECK(!wangTile.flipped_diagonally());
    CHECK(wangTile.flipped_horizontally());
    CHECK(wangTile.flipped_vertically());

    const std::array<int, 8>& indices = wangTile.wang_color_indices();

    CHECK(std::get<0>(indices) == 2);
    CHECK(std::get<1>(indices) == 0);
    CHECK(std::get<2>(indices) == 1);
    CHECK(std::get<3>(indices) == 0);
    CHECK(std::get<4>(indices) == 1);
    CHECK(std::get<5>(indices) == 0);
    CHECK(std::get<6>(indices) == 2);
    CHECK(std::get<7>(indices) == 0);
  }
}
