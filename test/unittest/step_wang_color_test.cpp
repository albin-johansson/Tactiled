#include "step_wang_color.hpp"

#include <doctest.h>

#include "step_utils.hpp"

using namespace step;

TEST_SUITE("WangColor")
{
  TEST_CASE("Valid Wang color")
  {
    const auto json = detail::parse_json("resource/wangcolor/valid.json");
    const WangColor wangColor{json};
    CHECK(wangColor.get_color() == color{"#d31313"});
    CHECK(wangColor.name() == "Rails");
    CHECK(wangColor.probability() == 0.75);
    CHECK(wangColor.tile() == 18_lid);
  }
}