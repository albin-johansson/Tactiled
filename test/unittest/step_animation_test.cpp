#include "step_animation.hpp"

#include <doctest.h>

#include "step_utils.hpp"

using namespace step;

TEST_SUITE("Animation")
{
  TEST_CASE("Parsing valid animation")
  {
    const animation animation{
        detail::parse_json("resource/animation/animation_valid.json")};

    CHECK(animation.num_frames() == 3);

    const auto first = animation.frames().at(0);
    CHECK(first.tile_id() == 77_lid);
    CHECK(first.duration() == 321);

    const auto second = animation.frames().at(1);
    CHECK(second.tile_id() == 485_lid);
    CHECK(second.duration() == 8375);

    const auto third = animation.frames().at(2);
    CHECK(third.tile_id() == 346_lid);
    CHECK(third.duration() == 31);
  }
}