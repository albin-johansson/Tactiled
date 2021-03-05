#include <doctest.h>

#include "animation.hpp"
#include "step_detail.hpp"

using namespace step;

TEST_SUITE("Animation")
{
  TEST_CASE("Parsing valid animation")
  {
    const animation animation{
        detail::parse_json("resource/animation/animation_valid.json")};

    CHECK(animation.frames.size() == 3);

    const auto first = animation.frames.at(0);
    CHECK(first.tile == 77_lid);
    CHECK(first.duration == 321);

    const auto second = animation.frames.at(1);
    CHECK(second.tile == 485_lid);
    CHECK(second.duration == 8375);

    const auto third = animation.frames.at(2);
    CHECK(third.tile == 346_lid);
    CHECK(third.duration == 31);
  }
}