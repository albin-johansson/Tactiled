#include "step_property.h"

#include <doctest.h>

#include <string>
#include <string_view>

#include "step_utils.h"

using namespace step;

namespace {

Property mk_property(std::string_view file)
{
  using namespace std::string_literals;
  const auto actualPath = "resource/property/"s + file.data();
  const auto json = detail::parse_json(actualPath);
  return json.get<Property>();
}

}  // namespace

TEST_SUITE("General Property stuff")
{
  TEST_CASE("Bad name")
  {
    CHECK_THROWS_AS(mk_property("property_bad_name.json"), TypeError);
  }
}

TEST_SUITE("String property")
{
  TEST_CASE("Valid")
  {
    const auto property = mk_property("string_property_valid.json");
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
    CHECK_THROWS_AS(mk_property("string_property_bad_value.json"), TypeError);
  }
}

TEST_SUITE("Int property")
{
  TEST_CASE("Valid")
  {
    const auto property = mk_property("int_property_valid.json");
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
    CHECK_THROWS_AS(mk_property("int_property_bad_value.json"), TypeError);
  }
}

TEST_SUITE("Float property")
{
  TEST_CASE("Valid")
  {
    const auto property = mk_property("float_property_valid.json");
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
    CHECK_THROWS_AS(mk_property("float_property_bad_value.json"), TypeError);
  }
}

TEST_SUITE("Bool property")
{
  TEST_CASE("Valid")
  {
    const auto property = mk_property("bool_property_valid.json");
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
    CHECK_THROWS_AS(mk_property("bool_property_bad_value.json"), TypeError);
  }
}

TEST_SUITE("Color property")
{
  TEST_CASE("Valid")
  {
    const auto property = mk_property("color_property_valid.json");
    CHECK(property.name() == "Rohan");
    CHECK(property.type() == Property::Type::Color);
    CHECK(property.is_color());
    CHECK(property.as_color());
    CHECK(*property.as_color() == Color{"#AA22BB33"});

    CHECK(!property.as_string());
    CHECK(!property.as_int());
    CHECK(!property.as_float());
    CHECK(!property.as_bool());
  }
  TEST_CASE("Bad value")
  {
    CHECK_THROWS_AS(mk_property("color_property_bad_value.json"), TypeError);
  }
}

TEST_SUITE("File property")
{
  TEST_CASE("Valid")
  {
    const auto property = mk_property("file_property_valid.json");
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
    CHECK_THROWS_AS(mk_property("file_property_bad_value.json"), TypeError);
  }
}
