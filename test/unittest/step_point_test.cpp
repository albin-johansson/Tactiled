#include "step_point.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/point/";

TEST_SUITE("Point")
{
  TEST_CASE("Parsing valid point")
  {
    const auto point = test::make<Point>(prefix, "point_valid.json");

    CHECK(point.x() == 42.6);
    CHECK(point.y() == 184.3);
  }

  TEST_CASE("Parsing invalid point")
  {
    CHECK_THROWS(test::make<Point>(prefix, "point_invalid.json"));
  }
}
