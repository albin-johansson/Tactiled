#include "step_text.h"

#include <doctest.h>

#include "step_exception.h"
#include "step_utils.h"

using namespace step;

TEST_SUITE("Text")
{
  TEST_CASE("Text object with all keys")
  {
    const Text text{detail::parse_json("resource/text/text_all_keys.json")};

    CHECK(text.text() == "Elrond");
    CHECK(text.font_family() == "Consolas");
    CHECK(text.color() == Color{"#AA0000"});
    CHECK(text.horizontal_alignment() == Text::HAlign::Center);
    CHECK(text.vertical_alignment() == Text::VAlign::Bottom);
    CHECK(text.pixel_size() == 24);
    CHECK(text.bold());
    CHECK(text.italic());
    CHECK(!text.kerning());
    CHECK(text.strikeout());
    CHECK(text.underline());
    CHECK(text.wrap());
  }

  TEST_CASE("Text object from bare minimum JSON")
  {
    const Text text{detail::parse_json("resource/text/text_minimum.json")};

    CHECK(text.text() == "Smaug");

    SUBCASE("Check defaults")
    {
      CHECK(text.color() == Color{"#000000"});

      CHECK(text.kerning());
      CHECK(!text.bold());
      CHECK(!text.italic());
      CHECK(!text.strikeout());
      CHECK(!text.underline());
      CHECK(!text.wrap());

      CHECK(text.font_family() == "sans-serif");
      CHECK(text.pixel_size() == 16);

      CHECK(text.horizontal_alignment() == Text::HAlign::Left);
      CHECK(text.vertical_alignment() == Text::VAlign::Top);
    }
  }

  TEST_CASE("Text without the \"text\" attribute")
  {
    const auto json =
        detail::parse_json("resource/text/text_missing_text_attribute.json");

    CHECK_THROWS_WITH_AS(
        Text{json}, "Text > Missing \"text\" attribute!", StepException);
  }
}
