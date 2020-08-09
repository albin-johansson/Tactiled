#include "step_properties.hpp"

#include <doctest.h>

#include "step_exception.hpp"
#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/properties/";

TEST_SUITE("Properties")
{
  TEST_CASE("Parse properties")
  {
    const properties props{
        detail::parse_json("resource/properties/properties.json")};

    SUBCASE("Checking if property exists")
    {
      CHECK(props.has("a"));
      CHECK(props.has("b"));
      CHECK(props.has("c"));
      CHECK(!props.has("x"));
    }

    SUBCASE("Getting property")
    {
      CHECK_THROWS_WITH_AS(props.get("x"),
                           "Properties > Couldn't lookup property!",
                           step_exception);

      REQUIRE_NOTHROW(props.get("a"));

      const auto& property = props.get("a");
      CHECK(property.name() == "a");
      REQUIRE(property.is<int>());
      CHECK(property.get<int>() == 67);
    }

    SUBCASE("Testing the is-method")
    {
      CHECK(!props.is("x", 812));  // doesn't exist

      CHECK(props.is("a", 67));
      CHECK(props.is("b", 24));
      CHECK(props.is("c", 31));
      CHECK(props.is("d", 42.0f));
      CHECK(props.is("e", true));
      CHECK(props.is("f", Color{"#ABBAFEFF"}));
      CHECK(props.is("g", "dawkins"));
      CHECK(props.is("h", "path/to/file.png"_file));

      CHECK(!props.is("a", false));
      CHECK(!props.is("b", "hello"));
      CHECK(!props.is("c", 2.91f));
      CHECK(!props.is("d", Color{"#AABBCCDD"}));
      CHECK(!props.is("f", 1234));
      CHECK(!props.is("g", true));
    }

    CHECK(props.amount() == 8);
    CHECK(!props.empty());

    int i = 0;
    props.each([&i](const std::pair<std::string, property>& pair) { ++i; });
    CHECK(i == 8);
  }
}