#include "step_properties.h"

#include <doctest.h>

#include "step_exception.h"
#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/properties/";

TEST_SUITE("Properties")
{
  TEST_CASE("Parse properties")
  {
    const auto props = test::make<Properties>(prefix, "properties.json");

    SUBCASE("Checking if property exists")
    {
      CHECK(props.has("a"));
      CHECK(props.has("b"));
      CHECK(props.has("c"));
      CHECK(!props.has("d"));
    }

    SUBCASE("Getting property")
    {
      CHECK_THROWS_WITH_AS(props.get("d"),
                           "Properties > Couldn't lookup property: d",
                           StepException);

      REQUIRE_NOTHROW(props.get("a"));

      const auto& property = props.get("a");
      CHECK(property.name() == "a");
      REQUIRE(property.is_int());
      CHECK(*property.as_int() == 67);
    }

    CHECK(props.amount() == 3);
    CHECK(!props.empty());

    props.each([](const std::pair<std::string, Property>& pair) {
      CHECK(pair.second.is_int());
    });
  }
}