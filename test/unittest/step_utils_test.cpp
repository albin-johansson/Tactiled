#include "step_utils.hpp"

#include <doctest.h>

using namespace step;
using namespace detail;

TEST_SUITE("parse_json(CZString)")
{
  TEST_CASE("Bad args")
  {
    std::string_view bad;
    CHECK_THROWS_AS(parse_json(bad), StepException);
    CHECK_THROWS_AS(parse_json("abc"), StepException);
  }

  TEST_CASE("Valid JSON")
  {
    CHECK_NOTHROW(parse_json("resource/property/int_property_valid.json"));
  }

  TEST_SUITE("convert(std::string_view)")
  {
    TEST_CASE("Bad args")
    {
      std::string_view bad;
      CHECK_THROWS_AS(convert<int>(bad), StepException);
      CHECK_THROWS_AS(convert<int>("abc"), StepException);
    }

    TEST_CASE("Valid args")
    {
      CHECK(convert<int>("314") == 314);
      CHECK(convert<int>("AB", 16) == 0xAB);
    }
  }
}