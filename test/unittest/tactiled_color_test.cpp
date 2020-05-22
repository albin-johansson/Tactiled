#include "tactiled_color.h"

#include <doctest.h>

#include "tactiled_exception.h"

using namespace tactiled;

TEST_SUITE("Color")
{
  TEST_CASE("From ARGB string")
  {
    Color color{"AABBCCDD"};
    CHECK(color.red() == 0xAA);
    CHECK(color.green() == 0xBB);
    CHECK(color.blue() == 0xCC);
    CHECK(color.alpha() == 0xDD);
  }
  TEST_CASE("From RGB string")
  {
    Color color{"AABBCC"};
    CHECK(color.red() == 0xAA);
    CHECK(color.green() == 0xBB);
    CHECK(color.blue() == 0xCC);

    CHECK(color.alpha() == 0xFF);
  }
  TEST_CASE("Invalid string")
  {
    CHECK_THROWS_AS(Color{""}, TactiledException);
    CHECK_THROWS_AS(Color{"AABBCCDDD"}, TactiledException);  // too long
    CHECK_THROWS_AS(Color{"GGBBCCDD"}, TactiledException);   // invalid hex
  }
}