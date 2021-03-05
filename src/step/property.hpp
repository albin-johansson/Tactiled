#ifndef STEP_PROPERTY_HEADER
#define STEP_PROPERTY_HEADER

#include <json.hpp>  // json
#include <string>    // string
#include <variant>   // variant, holds_alternative, get

#include "color.hpp"
#include "common.hpp"
#include "error.hpp"

namespace step {

using property_data =
    std::variant<std::string, file_path, object_id, color, int, double, bool>;

enum class property_type
{
  string,    ///< For string values, such as `"foo"`.
  integer,   ///< For integer values, e.g. `27`.
  floating,  ///< For floating-point values, e.g. `182.4`.
  boolean,   ///< For the boolean values `true`/`false`.
  color,     ///< For ARGB/RGB colors, e.g. `"AARRGGBB"` and `"RRGGBB"`.
  file,      ///< For file paths, e.g. `"some/path/abc.png"`.
  object     ///< For referencing other objects. Really just an integer ID.
};

struct property final
{
  property_type type;
  std::string name;
  property_data value;
};

[[nodiscard]] auto is_string(const property& property) noexcept -> bool
{
  return std::holds_alternative<std::string>(property.value);
}

[[nodiscard]] auto is_int(const property& property) noexcept -> bool
{
  return std::holds_alternative<int>(property.value);
}

[[nodiscard]] auto is_double(const property& property) noexcept -> bool
{
  return std::holds_alternative<double>(property.value);
}

[[nodiscard]] auto is_bool(const property& property) noexcept -> bool
{
  return std::holds_alternative<bool>(property.value);
}

[[nodiscard]] auto is_color(const property& property) noexcept -> bool
{
  return std::holds_alternative<color>(property.value);
}

[[nodiscard]] auto is_file_path(const property& property) noexcept -> bool
{
  return std::holds_alternative<file_path>(property.value);
}

[[nodiscard]] auto is_object_id(const property& property) noexcept -> bool
{
  return std::holds_alternative<object_id>(property.value);
}

[[nodiscard]] auto as_string(const property& property) -> const std::string&
{
  return std::get<std::string>(property.value);
}

[[nodiscard]] auto as_int(const property& property) -> int
{
  return std::get<int>(property.value);
}

[[nodiscard]] auto as_double(const property& property) -> double
{
  return std::get<double>(property.value);
}

[[nodiscard]] auto as_bool(const property& property) -> bool
{
  return std::get<bool>(property.value);
}

[[nodiscard]] auto as_color(const property& property) -> const color&
{
  return std::get<color>(property.value);
}

[[nodiscard]] auto as_file_path(const property& property) -> const file_path&
{
  return std::get<file_path>(property.value);
}

[[nodiscard]] auto as_object_id(const property& property) -> object_id
{
  return std::get<object_id>(property.value);
}

inline void from_json(const nlohmann::json& json, property& property)
{
  json.at("name").get_to(property.name);
  json.at("type").get_to(property.type);

  switch (property.type) {
    case property_type::integer:
    {
      property.value.emplace<int>(json.at("value").get<int>());
      break;
    }
    case property_type::floating:
    {
      property.value.emplace<double>(json.at("value").get<float>());
      break;
    }
    case property_type::boolean:
    {
      property.value.emplace<bool>(json.at("value").get<bool>());
      break;
    }
    case property_type::color:
    {
      property.value.emplace<color>(
          from_string(json.at("value").get<std::string>()));
      break;
    }
    case property_type::file:
    {
      property.value.emplace<file_path>(json.at("value").get<std::string>());
      break;
    }
    case property_type::object:
    {
      property.value.emplace<object_id>(json.at("value").get<int>());
      break;
    }
    case property_type::string:
    {
      property.value.emplace<std::string>(json.at("value").get<std::string>());
      break;
    }
    default:
      throw step_error{"Unknown property type!"};
  }
}

NLOHMANN_JSON_SERIALIZE_ENUM(property_type,
                             {{property_type::string, "string"},
                              {property_type::integer, "int"},
                              {property_type::floating, "float"},
                              {property_type::boolean, "bool"},
                              {property_type::color, "color"},
                              {property_type::object, "object"},
                              {property_type::file, "file"}})

}  // namespace step

#endif  // STEP_PROPERTY_HEADER
