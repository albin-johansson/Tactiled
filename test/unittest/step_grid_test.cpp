#include "step_grid.hpp"

#include <doctest.h>

#include "step_test_utils.h"

inline static const std::string prefix = "resource/grid/";

TEST_SUITE("grid")
{
  TEST_CASE("Load valid isometric grid")
  {
    const auto grid = step::test::make<step::grid>(prefix, "isometric.json");
    CHECK(grid.get_orientation() == step::grid::orientation::isometric);
    CHECK(grid.width() == 18);
    CHECK(grid.height() == 24);
  }

  TEST_CASE("Load valid orthogonal grid")
  {
    const auto grid = step::test::make<step::grid>(prefix, "orthogonal.json");
    CHECK(grid.get_orientation() == step::grid::orientation::orthogonal);
    CHECK(grid.width() == 54);
    CHECK(grid.height() == 28);
  }
}