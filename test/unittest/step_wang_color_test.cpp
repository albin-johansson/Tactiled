#include <doctest.h>

#include "step_detail.hpp"
#include "wang_color.hpp"

using namespace step;

TEST_SUITE("WangColor")
{
  TEST_CASE("Valid Wang color")
  {
    const auto json = detail::parse_json("resource/wangcolor/valid.json");
    const wang_color wangColor{json};
    CHECK(wangColor.get_color() == color{"#d31313"});
    CHECK(wangColor.name() == "Rails");
    CHECK(wangColor.probability() == 0.75);
    CHECK(wangColor.tile() == 18_lid);
  }
}