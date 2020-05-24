#include "step_animation.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("Animation")
{
  TEST_CASE("Parsing valid animation")
  {
    const auto path = "resource/animation/animation_valid.json";
    const auto json = detail::parse_json(path);
    const auto animation = json.at("animation").get<Animation>();

    CHECK(animation.length() == 3);

    const auto first = animation.frames().at(0);
    CHECK(first.tile_id() == 77);
    CHECK(first.duration() == 321);

    const auto second = animation.frames().at(1);
    CHECK(second.tile_id() == 485);
    CHECK(second.duration() == 8375);

    const auto third = animation.frames().at(2);
    CHECK(third.tile_id() == 346);
    CHECK(third.duration() == 31);
  }
}