#include "property.hpp"

#include <gtest/gtest.h>

#include "detail.hpp"

template <typename T>
auto from_json(const std::string_view path) -> T
{
  const auto json = step::detail::parse_json(path);

  T object;
  json.get_to(object);

  return object;
}

TEST(Property, StringProperty)
{
  const auto property =
      from_json<step::property>("resource/property/string.json");

  EXPECT_EQ("String property name", property.name);
  EXPECT_EQ(step::property_type::string, property.type);

  ASSERT_TRUE(step::is_string(property));
  EXPECT_EQ("This is a string value", step::as_string(property));

  EXPECT_FALSE(step::is_int(property));
  EXPECT_FALSE(step::is_double(property));
  EXPECT_FALSE(step::is_bool(property));
  EXPECT_FALSE(step::is_color(property));
  EXPECT_FALSE(step::is_file_path(property));
  EXPECT_FALSE(step::is_object_id(property));
}

TEST(Property, IntProperty)
{
  const auto property = from_json<step::property>("resource/property/int.json");

  EXPECT_EQ("Sauron", property.name);
  EXPECT_EQ(step::property_type::integer, property.type);

  ASSERT_TRUE(step::is_int(property));
  EXPECT_EQ(1'337, step::as_int(property));

  EXPECT_FALSE(step::is_string(property));
  EXPECT_FALSE(step::is_double(property));
  EXPECT_FALSE(step::is_bool(property));
  EXPECT_FALSE(step::is_color(property));
  EXPECT_FALSE(step::is_file_path(property));
  EXPECT_FALSE(step::is_object_id(property));
}

TEST(Property, FloatProperty)
{
  const auto property =
      from_json<step::property>("resource/property/double.json");

  EXPECT_EQ("Erebor", property.name);
  EXPECT_EQ(step::property_type::floating, property.type);

  ASSERT_TRUE(step::is_double(property));
  EXPECT_FLOAT_EQ(89.2, step::as_double(property));

  EXPECT_FALSE(step::is_string(property));
  EXPECT_FALSE(step::is_int(property));
  EXPECT_FALSE(step::is_bool(property));
  EXPECT_FALSE(step::is_color(property));
  EXPECT_FALSE(step::is_file_path(property));
  EXPECT_FALSE(step::is_object_id(property));
}

TEST(Property, BoolProperty)
{
  const auto property =
      from_json<step::property>("resource/property/bool.json");

  EXPECT_EQ("Blue mountains", property.name);
  EXPECT_EQ(step::property_type::boolean, property.type);

  ASSERT_TRUE(step::is_bool(property));
  EXPECT_EQ(false, step::as_bool(property));

  EXPECT_FALSE(step::is_string(property));
  EXPECT_FALSE(step::is_int(property));
  EXPECT_FALSE(step::is_double(property));
  EXPECT_FALSE(step::is_color(property));
  EXPECT_FALSE(step::is_file_path(property));
  EXPECT_FALSE(step::is_object_id(property));
}

TEST(Property, ColorProperty)
{
  const auto property =
      from_json<step::property>("resource/property/color.json");

  EXPECT_EQ("Rohan", property.name);
  EXPECT_EQ(step::property_type::color, property.type);

  ASSERT_TRUE(step::is_color(property));

  const auto& color = step::as_color(property);
  EXPECT_EQ(0xAA, color.alpha);
  EXPECT_EQ(0x22, color.red);
  EXPECT_EQ(0xBB, color.green);
  EXPECT_EQ(0x33, color.blue);

  EXPECT_FALSE(step::is_string(property));
  EXPECT_FALSE(step::is_int(property));
  EXPECT_FALSE(step::is_double(property));
  EXPECT_FALSE(step::is_bool(property));
  EXPECT_FALSE(step::is_file_path(property));
  EXPECT_FALSE(step::is_object_id(property));
}

TEST(Property, FileProperty)
{
  const auto property =
      from_json<step::property>("resource/property/file.json");

  EXPECT_EQ("Mirkwood", property.name);
  EXPECT_EQ(step::property_type::file, property.type);

  ASSERT_TRUE(step::is_file_path(property));
  EXPECT_EQ("path/to/file.txt", step::as_file_path(property).value);

  EXPECT_FALSE(step::is_string(property));
  EXPECT_FALSE(step::is_int(property));
  EXPECT_FALSE(step::is_double(property));
  EXPECT_FALSE(step::is_bool(property));
  EXPECT_FALSE(step::is_color(property));
  EXPECT_FALSE(step::is_object_id(property));
}

TEST(Property, ObjectProperty)
{
  const auto property =
      from_json<step::property>("resource/property/object.json");

  EXPECT_EQ("target", property.name);
  EXPECT_EQ(step::property_type::object, property.type);

  ASSERT_TRUE(step::is_object_id(property));
  EXPECT_EQ(1, step::as_object_id(property).value);

  EXPECT_FALSE(step::is_string(property));
  EXPECT_FALSE(step::is_int(property));
  EXPECT_FALSE(step::is_double(property));
  EXPECT_FALSE(step::is_bool(property));
  EXPECT_FALSE(step::is_color(property));
  EXPECT_FALSE(step::is_file_path(property));
}
