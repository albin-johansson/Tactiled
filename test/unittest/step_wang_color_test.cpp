#include "step_wang_color.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("WangColor")
{
  TEST_CASE("Valid Wang color")
  {
    const auto json = detail::parse_json("resource/wangcolor/valid.json");
    const WangColor wangColor{json};
    CHECK(wangColor.color() == Color{"#d31313"});
    CHECK(wangColor.name() == "Rails");
    CHECK(wangColor.probability() == 0.75);
    CHECK(wangColor.tile() == 18);
  }
}