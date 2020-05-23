#include "step_utils.h"

#include <doctest.h>

#include "step_exception.h"

using namespace step;
using namespace detail;

TEST_SUITE("parse_json(CZString)")
{
  TEST_CASE("Bad args")
  {
    CHECK_THROWS_AS(parse_json(nullptr), StepException);
    CHECK_THROWS_AS(parse_json("abc"), StepException);
  }
  TEST_CASE("Valid JSON")
  {
    CHECK_NOTHROW(parse_json("resource/property/int_property_valid.json"));
  }
}