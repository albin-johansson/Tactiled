#include "tactiled_utils.h"

#include <doctest.h>

#include "tactiled_exception.h"

using namespace tactiled;
using namespace detail;

TEST_SUITE("parse_json(CZString)")
{
  TEST_CASE("Bad args")
  {
    CHECK_THROWS_AS(parse_json(nullptr), TactiledException);
    CHECK_THROWS_AS(parse_json("abc"), TactiledException);
  }
  TEST_CASE("Valid JSON")
  {
    CHECK_NOTHROW(parse_json("resource/property/int_property_valid.json"));
  }
}