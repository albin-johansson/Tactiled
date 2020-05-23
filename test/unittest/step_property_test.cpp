#include "step_property.h"

#include <doctest.h>

#include "step_utils.h"

using namespace step;

TEST_SUITE("General Property stuff")
{
  TEST_CASE("Bad name")
  {
    const auto path = "resource/property/property_bad_name.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}

TEST_SUITE("String property")
{
  TEST_CASE("Valid")
  {
    const auto path = "resource/property/string_property_valid.json";
    Property property{detail::parse_json(path)};
    CHECK(property.name() == "String property name");
    CHECK(property.type() == Property::Type::String);
    CHECK(property.is_string());
    CHECK(property.as_string());
    CHECK(*property.as_string() == "This is a string value");

    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }

  TEST_CASE("Bad value")
  {
    const auto path = "resource/property/string_property_bad_value.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}

TEST_SUITE("Int property")
{
  TEST_CASE("Valid")
  {
    const auto path = "resource/property/int_property_valid.json";
    Property property{detail::parse_json(path)};
    CHECK(property.name() == "Sauron");
    CHECK(property.type() == Property::Type::Int);
    CHECK(property.is_int());
    CHECK(property.as_int());
    CHECK(*property.as_int() == 1337);

    CHECK(!property.as_string());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    const auto path = "resource/property/int_property_bad_value.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}

TEST_SUITE("Float property")
{
  TEST_CASE("Valid")
  {
    const auto path = "resource/property/float_property_valid.json";
    Property property{detail::parse_json(path)};
    CHECK(property.name() == "Erebor");
    CHECK(property.type() == Property::Type::Float);
    CHECK(property.is_float());
    CHECK(property.as_float());
    CHECK(*property.as_float() == 89.2f);

    CHECK(!property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    const auto path = "resource/property/float_property_bad_value.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}

TEST_SUITE("Bool property")
{
  TEST_CASE("Valid")
  {
    const auto path = "resource/property/bool_property_valid.json";
    Property property{detail::parse_json(path)};
    CHECK(property.name() == "Blue mountains");
    CHECK(property.type() == Property::Type::Bool);
    CHECK(property.is_bool());
    CHECK(property.as_bool());
    CHECK(!*property.as_bool());

    CHECK(!property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    const auto path = "resource/property/bool_property_bad_value.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}

TEST_SUITE("Color property")
{
  TEST_CASE("Valid")
  {
    const auto path = "resource/property/color_property_valid.json";
    Property property{detail::parse_json(path)};
    CHECK(property.name() == "Rohan");
    CHECK(property.type() == Property::Type::Color);
    CHECK(property.is_color());
    CHECK(property.as_color());
    CHECK(*property.as_color() == Color{"AA22BB33"});

    CHECK(!property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
  }
  TEST_CASE("Bad value")
  {
    const auto path = "resource/property/color_property_bad_value.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}

TEST_SUITE("File property")
{
  TEST_CASE("Valid")
  {
    const auto path = "resource/property/file_property_valid.json";
    Property property{detail::parse_json(path)};
    CHECK(property.name() == "Mirkwood");
    CHECK(property.type() == Property::Type::File);
    CHECK(property.is_file());
    CHECK(property.as_string());
    CHECK(*property.as_string() == "path/to/something/nice");

    CHECK(property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    const auto path = "resource/property/file_property_bad_value.json";
    CHECK_THROWS_AS(Property{detail::parse_json(path)}, TypeError);
  }
}
