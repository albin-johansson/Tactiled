#include "step_property.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/property/";

TEST_SUITE("General Property stuff")
{
  TEST_CASE("Bad name")
  {
    CHECK_THROWS(Property{"resource/property/property_bad_name.json"});
  }
}

TEST_SUITE("String property")
{
  TEST_CASE("Valid")
  {
    const Property property{
        detail::parse_json("resource/property/string_property_valid.json")};

    CHECK(property.name() == "String property name");
    CHECK(property.type() == Property::Type::String);
    CHECK(property.is<std::string>());
    CHECK(property.get<std::string>() == "This is a string value");

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
  }

  TEST_CASE("Bad value")
  {
    CHECK_THROWS(Property{"resource/property/string_property_bad_value.json"});
  }
}

TEST_SUITE("Int property")
{
  TEST_CASE("Valid")
  {
    const Property property{
        detail::parse_json("resource/property/int_property_valid.json")};

    CHECK(property.name() == "Sauron");
    CHECK(property.type() == Property::Type::Int);
    CHECK(property.is<int>());
    CHECK(property.get<int>() == 1337);

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
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS(Property{"resource/property/int_property_bad_value.json"});
  }
}

TEST_SUITE("Float property")
{
  TEST_CASE("Valid")
  {
    const Property property{
        detail::parse_json("resource/property/float_property_valid.json")};

    CHECK(property.name() == "Erebor");
    CHECK(property.type() == Property::Type::Float);
    CHECK(property.is<float>());
    CHECK(property.get<float>() == 89.2f);

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
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS(Property{"resource/property/float_property_bad_value.json"});
  }
}

TEST_SUITE("Bool property")
{
  TEST_CASE("Valid")
  {
    const Property property{
        detail::parse_json("resource/property/bool_property_valid.json")};
    CHECK(property.name() == "Blue mountains");
    CHECK(property.type() == Property::Type::Bool);
    CHECK(property.is<bool>());
    CHECK(!property.get<bool>());

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
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS(Property{"resource/property/bool_property_bad_value.json"});
  }
}

TEST_SUITE("Color property")
{
  TEST_CASE("Valid")
  {
    const Property property{
        detail::parse_json("resource/property/color_property_valid.json")};
    CHECK(property.name() == "Rohan");
    CHECK(property.type() == Property::Type::Color);
    CHECK(property.is<Color>());
    CHECK(property.get<Color>() == Color{"#AA22BB33"});

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
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS(Property{"resource/property/color_property_bad_value.json"});
  }
}

TEST_SUITE("File property")
{
  TEST_CASE("Valid")
  {
    const Property property{
        detail::parse_json("resource/property/file_property_valid.json")};
    CHECK(property.name() == "Mirkwood");
    CHECK(property.type() == Property::Type::File);
    CHECK(property.is<File>());

    SUBCASE("Property::get")
    {
      CHECK(property.get<File>() == "path/to/file.txt"_file);
      CHECK_THROWS(property.get<int>());
      CHECK_THROWS(property.get<float>());
      CHECK_THROWS(property.get<bool>());
      CHECK_THROWS(property.get<Color>());
      CHECK_THROWS(property.get<std::string>());
    }

    SUBCASE("Property::get_or")
    {
      const bool result =
          property.get_or("foo"_file) == "path/to/file.txt"_file;
      CHECK(result);
      CHECK(property.get_or("#AABBCCDD"_color) == "#AABBCCDD"_color);
      CHECK(property.get_or(true));
      CHECK(property.get_or(42.5f) == 42.5f);
      CHECK(property.get_or(7) == 7);

      using namespace std::string_literals;
      CHECK(property.get_or("foo"s) == "foo"s);
    }
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS(Property{"resource/property/file_property_bad_value.json"});
  }
}
