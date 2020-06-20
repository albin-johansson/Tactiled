#include "step_grid.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/grid/";

TEST_SUITE("Grid")
{
  TEST_CASE("Load valid isometric grid")
  {
    const auto grid = test::make<Grid>(prefix, "isometric.json");
    CHECK(grid.orientation() == Grid::Orientation::Isometric);
    CHECK(grid.width() == 18);
    CHECK(grid.height() == 24);
  }

  TEST_CASE("Load valid orthogonal grid")
  {
    const auto grid = test::make<Grid>(prefix, "orthogonal.json");
    CHECK(grid.orientation() == Grid::Orientation::Orthogonal);
    CHECK(grid.width() == 54);
    CHECK(grid.height() == 28);
  }
}