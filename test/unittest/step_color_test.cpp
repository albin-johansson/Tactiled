#include <doctest.h>

#include <string_view>

#include "color.hpp"
#include "step_exception.hpp"

TEST_SUITE("color")
{
  TEST_CASE("From ARGB string")
  {
    constexpr step::color color{"#AABBCCDD"};

    static_assert(color.alpha() == 0xAA);
    static_assert(color.red() == 0xBB);
    static_assert(color.green() == 0xCC);
    static_assert(color.blue() == 0xDD);

    CHECK(color.alpha() == 0xAA);
    CHECK(color.red() == 0xBB);
    CHECK(color.green() == 0xCC);
    CHECK(color.blue() == 0xDD);
  }

  TEST_CASE("From RGB string")
  {
    constexpr step::color color{"#aAbBcC"};

    static_assert(color.alpha() == 0xFF);
    static_assert(color.red() == 0xAA);
    static_assert(color.green() == 0xBB);
    static_assert(color.blue() == 0xCC);

    CHECK(color.alpha() == 0xFF);
    CHECK(color.red() == 0xAA);
    CHECK(color.green() == 0xBB);
    CHECK(color.blue() == 0xCC);
  }

  TEST_CASE("Invalid string")
  {
    using namespace std::string_view_literals;

    CHECK_THROWS_WITH_AS(step::color{"#AABBCCDDD"sv},
                         "color > Input string has incorrect length: 10",
                         step::step_exception);

    CHECK_THROWS_WITH_AS(step::color{"1112233"sv},
                         "color > Input string must begin with #",
                         step::step_exception);

    CHECK_THROWS_WITH_AS(step::color{"#GGBBCCDD"sv},
                         "color > Failed to parse hex string: GG",
                         step::step_exception);
  }

  TEST_CASE("Comparing colors")
  {
    SUBCASE("Equal colors")
    {
      constexpr step::color fst{"#AECBDE"};
      constexpr step::color snd{fst};

      static_assert(fst == snd);
      static_assert(snd == fst);
    }

    SUBCASE("Non-equal colors")
    {
      constexpr step::color fst{"#AECBDE"};
      constexpr step::color snd{"#BBE3A3"};

      static_assert(fst != snd);
      static_assert(snd != fst);
    }
  }
}