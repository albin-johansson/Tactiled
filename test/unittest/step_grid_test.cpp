#include "step_grid.h"

#include <doctest.h>

#include <string_view>

#include "step_utils.h"

using namespace step;

namespace {

[[nodiscard]] Grid mk_grid(std::string_view file)
{
  using namespace std::string_literals;
  const auto path = "resource/grid/"s + file.data();
  const auto json = detail::parse_json(path);
  return json.get<Grid>();
}

}  // namespace

TEST_SUITE("Grid")
{
  TEST_CASE("Load valid isometric grid")
  {
    const auto grid = mk_grid("isometric.json");
    CHECK(grid.orientation() == Grid::Orientation::Isometric);
    CHECK(grid.width() == 18);
    CHECK(grid.height() == 24);
  }

  TEST_CASE("Load valid orthogonal grid")
  {
    const auto grid = mk_grid("orthogonal.json");
    CHECK(grid.orientation() == Grid::Orientation::Orthogonal);
    CHECK(grid.width() == 54);
    CHECK(grid.height() == 28);
  }
}