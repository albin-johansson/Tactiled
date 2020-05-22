#include "tactiled_point.h"

#include <doctest.h>

#include "tactiled_exception.h"
#include "tactiled_utils.h"

using namespace tactiled;

TEST_SUITE("Point")
{
  TEST_CASE("Parsing valid point")
  {
    JSON json = detail::parse_json("resources/point_valid.json");
    Point point{json};

    CHECK(point.x() == 42.6);
    CHECK(point.y() == 184.3);
  }

  TEST_CASE("Parsing invalid point")
  {
    JSON json = detail::parse_json("resources/point_invalid.json");
    CHECK_THROWS_AS(Point{json}, TactiledException);
  }
}
