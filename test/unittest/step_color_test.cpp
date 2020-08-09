#include "step_color.hpp"

#include <doctest.h>

#include "step_exception.hpp"

using namespace step;

TEST_SUITE("Color")
{
  TEST_CASE("From ARGB string")
  {
    const Color color{"#AABBCCDD"};
    CHECK(color.red() == 0xAA);
    CHECK(color.green() == 0xBB);
    CHECK(color.blue() == 0xCC);
    CHECK(color.alpha() == 0xDD);
  }

  TEST_CASE("From RGB string")
  {
    const Color color{"#AABBCC"};
    CHECK(color.red() == 0xAA);
    CHECK(color.green() == 0xBB);
    CHECK(color.blue() == 0xCC);

    CHECK(color.alpha() == 0xFF);
  }

  TEST_CASE("Suffix _color")
  {
    const auto color = "#1177CC"_color;
    CHECK(color.red() == 0x11);
    CHECK(color.green() == 0x77);
    CHECK(color.blue() == 0xCC);
    CHECK(color.alpha() == 0xFF);
  }

  TEST_CASE("Invalid string")
  {
    CHECK_THROWS_AS(Color{""}, StepException);

    CHECK_THROWS_WITH_AS("#AABBCCDDD"_color,
                         "Color > Input string has incorrect length: 10",
                         StepException);

    CHECK_THROWS_WITH_AS("1112233"_color,
                         "Color > Input string must begin with #",
                         StepException);

    CHECK_THROWS_WITH_AS("#GGBBCCDD"_color,
                         "Color > Failed to parse hex string: GG",
                         StepException);
  }
}