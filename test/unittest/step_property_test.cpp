#include "step_property.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/property/";

TEST_SUITE("General Property stuff")
{
  TEST_CASE("Bad name")
  {
    CHECK_THROWS_AS(test::make<Property>(prefix, "property_bad_name.json"),
                    TypeError);
  }
}

TEST_SUITE("String property")
{
  TEST_CASE("Valid")
  {
    const auto property =
        test::make<Property>(prefix, "string_property_valid.json");
    CHECK(property.name() == "String property name");
    CHECK(property.type() == Property::Type::String);
    CHECK(property.is_string());
    CHECK(property.as_string());
    CHECK(*property.as_string() == "This is a string value");

    SUBCASE("Property::get")
    {
      CHECK(property.get<std::string>() == "This is a string value");
      CHECK_THROWS(property.get<int>());
      CHECK_THROWS(property.get<float>());
      CHECK_THROWS(property.get<bool>());
      CHECK_THROWS(property.get<Color>());
    }

    SUBCASE("Property::get_or")
    {
      CHECK(property.get_or<std::string>("foo") == "This is a string value");
      CHECK(property.get_or(7) == 7);
      CHECK(property.get_or(42.5f) == 42.5f);
      CHECK(property.get_or(true));
      CHECK(property.get_or(Color{"#AABBCCDD"}) == Color{"#AABBCCDD"});
    }

    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }

  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(
        test::make<Property>(prefix, "string_property_bad_value.json"),
        TypeError);
  }
}

TEST_SUITE("Int property")
{
  TEST_CASE("Valid")
  {
    const auto property =
        test::make<Property>(prefix, "int_property_valid.json");
    CHECK(property.name() == "Sauron");
    CHECK(property.type() == Property::Type::Int);
    CHECK(property.is_int());
    CHECK(property.as_int());
    CHECK(*property.as_int() == 1337);

    SUBCASE("Property::get")
    {
      CHECK(property.get<int>() == 1337);
      CHECK_THROWS(property.get<float>());
      CHECK_THROWS(property.get<bool>());
      CHECK_THROWS(property.get<Color>());
      CHECK_THROWS(property.get<std::string>());
    }

    SUBCASE("Property::get_or")
    {
      CHECK(property.get_or(7) == 1337);
      CHECK(property.get_or<std::string>("foo") == "foo");
      CHECK(property.get_or(42.5f) == 42.5f);
      CHECK(property.get_or(true));
      CHECK(property.get_or(Color{"#AABBCCDD"}) == Color{"#AABBCCDD"});
    }

    CHECK(!property.as_string());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(test::make<Property>(prefix, "int_property_bad_value.json"),
                    TypeError);
  }
}

TEST_SUITE("Float property")
{
  TEST_CASE("Valid")
  {
    const auto property =
        test::make<Property>(prefix, "float_property_valid.json");
    CHECK(property.name() == "Erebor");
    CHECK(property.type() == Property::Type::Float);
    CHECK(property.is_float());
    CHECK(property.as_float());
    CHECK(*property.as_float() == 89.2f);

    SUBCASE("Property::get")
    {
      CHECK(property.get<float>() == 89.2f);
      CHECK_THROWS(property.get<int>());
      CHECK_THROWS(property.get<bool>());
      CHECK_THROWS(property.get<Color>());
      CHECK_THROWS(property.get<std::string>());
    }

    SUBCASE("Property::get_or")
    {
      CHECK(property.get_or(42.5f) == 89.2f);
      CHECK(property.get_or(7) == 7);
      CHECK(property.get_or<std::string>("foo") == "foo");
      CHECK(property.get_or(true));
      CHECK(property.get_or(Color{"#AABBCCDD"}) == Color{"#AABBCCDD"});
    }

    CHECK(!property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(
        test::make<Property>(prefix, "float_property_bad_value.json"),
        TypeError);
  }
}

TEST_SUITE("Bool property")
{
  TEST_CASE("Valid")
  {
    const auto property =
        test::make<Property>(prefix, "bool_property_valid.json");
    CHECK(property.name() == "Blue mountains");
    CHECK(property.type() == Property::Type::Bool);
    CHECK(property.is_bool());
    CHECK(property.as_bool());
    CHECK(!*property.as_bool());

    SUBCASE("Property::get")
    {
      CHECK(!property.get<bool>());
      CHECK_THROWS(property.get<int>());
      CHECK_THROWS(property.get<float>());
      CHECK_THROWS(property.get<Color>());
      CHECK_THROWS(property.get<std::string>());
    }

    SUBCASE("Property::get_or")
    {
      CHECK(!property.get_or(true));
      CHECK(property.get_or(42.5f) == 42.5f);
      CHECK(property.get_or(7) == 7);
      CHECK(property.get_or<std::string>("foo") == "foo");
      CHECK(property.get_or(Color{"#AABBCCDD"}) == Color{"#AABBCCDD"});
    }

    CHECK(!property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(
        test::make<Property>(prefix, "bool_property_bad_value.json"),
        TypeError);
  }
}

TEST_SUITE("Color property")
{
  TEST_CASE("Valid")
  {
    const auto property =
        test::make<Property>(prefix, "color_property_valid.json");
    CHECK(property.name() == "Rohan");
    CHECK(property.type() == Property::Type::Color);
    CHECK(property.is_color());
    CHECK(property.as_color());
    CHECK(*property.as_color() == Color{"#AA22BB33"});

    SUBCASE("Property::get")
    {
      CHECK(property.get<Color>() == Color{"#AA22BB33"});
      CHECK_THROWS(property.get<int>());
      CHECK_THROWS(property.get<float>());
      CHECK_THROWS(property.get<bool>());
      CHECK_THROWS(property.get<std::string>());
    }

    SUBCASE("Property::get_or")
    {
      CHECK(property.get_or(Color{"#AABBCCDD"}) == Color{"#AA22BB33"});
      CHECK(property.get_or(true));
      CHECK(property.get_or(42.5f) == 42.5f);
      CHECK(property.get_or(7) == 7);
      CHECK(property.get_or<std::string>("foo") == "foo");
    }

    CHECK(!property.as_string());
    CHECK(!property.as_int());Property p;
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(
        test::make<Property>(prefix, "color_property_bad_value.json"),
        TypeError);
  }
}

TEST_SUITE("File property")
{
  TEST_CASE("Valid")
  {
    const auto property =
        test::make<Property>(prefix, "file_property_valid.json");
    CHECK(property.name() == "Mirkwood");
    CHECK(property.type() == Property::Type::File);
    CHECK(property.is_file());
    CHECK(property.as_string());
    CHECK(*property.as_string() == "path/to/something/nice");

    SUBCASE("Property::get")
    {
      CHECK(property.get<std::string>() == "path/to/something/nice");
      CHECK_THROWS(property.get<int>());
      CHECK_THROWS(property.get<float>());
      CHECK_THROWS(property.get<bool>());
      CHECK_THROWS(property.get<Color>());
    }

    SUBCASE("Property::get_or")
    {
      CHECK(property.get_or<std::string>("foo") == "path/to/something/nice");
      CHECK(property.get_or(Color{"#AABBCCDD"}) == Color{"#AABBCCDD"});
      CHECK(property.get_or(true));
      CHECK(property.get_or(42.5f) == 42.5f);
      CHECK(property.get_or(7) == 7);
    }

    CHECK(property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
    CHECK(!property.as_color());
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(
        test::make<Property>(prefix, "file_property_bad_value.json"),
        TypeError);
  }
}
