#include "step_point.h"

#include <doctest.h>

#include "step_exception.h"
#include "step_utils.h"

using namespace step;

TEST_SUITE("Point")
{
  TEST_CASE("Parsing valid point")
  {
    JSON json = detail::parse_json("resource/point_valid.json");
    Point point{json};

    CHECK(point.x() == 42.6);
    CHECK(point.y() == 184.3);
  }

  TEST_CASE("Parsing invalid point")
  {
    JSON json = detail::parse_json("resource/point_invalid.json");
    CHECK_THROWS_AS(Point{json}, StepException);
  }
}
