#include "step_point.h"

#include <doctest.h>

#include "step_test_utils.h"

TEST_SUITE("point")
{
  TEST_CASE("Parsing valid point")
  {
    const step::point point{
        step::detail::parse_json("resource/point/point_valid.json")};

    CHECK(point.x() == 42.6);
    CHECK(point.y() == 184.3);
  }

  TEST_CASE("Parsing invalid point")
  {
    CHECK_THROWS(step::point{
        step::detail::parse_json("resource/point/point_invalid.json")});
  }
}
