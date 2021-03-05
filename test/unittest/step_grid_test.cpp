#include <doctest.h>

#include "grid.hpp"
#include "step_detail.hpp"

TEST_SUITE("grid")
{
  TEST_CASE("Load valid isometric grid")
  {
    const step::grid grid =
        step::detail::parse_json("resource/grid/isometric.json");

    CHECK(grid.orientation == step::grid_orientation::isometric);
    CHECK(grid.width == 18);
    CHECK(grid.height == 24);
  }

  TEST_CASE("Load valid orthogonal grid")
  {
    const step::grid grid =
        step::detail::parse_json("resource/grid/orthogonal.json");
    CHECK(grid.orientation == step::grid_orientation::orthogonal);
    CHECK(grid.width == 54);
    CHECK(grid.height == 28);
  }
}