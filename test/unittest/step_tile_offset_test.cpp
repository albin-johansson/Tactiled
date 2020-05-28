#include "step_tile_offset.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

namespace {

TileOffset mk_tile_offset(std::string_view path)
{
  using namespace std::string_literals;
  const std::string actualPath = "resource/tileoffset/"s + path.data();
  const auto json = detail::parse_json(actualPath.c_str());
  return json.get<TileOffset>();
}

}  // namespace

TEST_SUITE("TileOffset")
{
  TEST_CASE("Valid tile offset")
  {
    const auto offset = mk_tile_offset("tile_offset.json");
    CHECK(offset.x() == 123);
    CHECK(offset.y() == 829);
  }
}
