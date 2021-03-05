#ifndef STEP_COLOR_HEADER
#define STEP_COLOR_HEADER

#include <cstddef>      // size_t
#include <string_view>  // string_view

#include "common.hpp"
#include "detail.hpp"
#include "error.hpp"

namespace step {

struct color final
{
  uint8 red{};
  uint8 green{};
  uint8 blue{};
  uint8 alpha{0xFF};
};

[[nodiscard]] inline auto from_string(const std::string_view string) -> color
{
  if (string.length() != 7 && string.length() != 9) {
    throw step_error{"Input string has incorrect length!"};
  }

  if (string.front() != '#') {
    throw step_error{"Input string must begin with '#'!"};
  }

  const auto withoutHash = string.substr(1);
  const auto length = withoutHash.length();

  color result;

  if (length == 8) {  // AARRGGBB
    result.alpha = detail::from_hex(withoutHash.substr(0, 2));
    result.red = detail::from_hex(withoutHash.substr(2, 2));
    result.green = detail::from_hex(withoutHash.substr(4, 2));
    result.blue = detail::from_hex(withoutHash.substr(6, 2));
  } else {  // RRGGBB
    result.red = detail::from_hex(withoutHash.substr(0, 2));
    result.green = detail::from_hex(withoutHash.substr(2, 2));
    result.blue = detail::from_hex(withoutHash.substr(4, 2));
  }

  return result;
}

template <std::size_t size>
[[nodiscard]] constexpr auto from_string(const char (&str)[size]) -> color
{
  // The assertion includes the null-terminator
  static_assert(size == 8 || size == 10, "String literal has invalid length!");

  const std::string_view view = str;

  const auto withoutHash = view.substr(1);
  const auto length = withoutHash.length();

  const auto from_hex = [](const std::string_view hex) -> uint8 {
    const auto from_hex_to_decimal = [](const char ch) -> uint8 {
      switch (ch) {
        case '0':
          return 0;
        case '1':
          return 1;
        case '2':
          return 2;
        case '3':
          return 3;
        case '4':
          return 4;
        case '5':
          return 5;
        case '6':
          return 6;
        case '7':
          return 7;
        case '8':
          return 8;
        case '9':
          return 9;
        case 'A':
          [[fallthrough]];
        case 'a':
          return 10;
        case 'B':
          [[fallthrough]];
        case 'b':
          return 11;
        case 'C':
          [[fallthrough]];
        case 'c':
          return 12;
        case 'D':
          [[fallthrough]];
        case 'd':
          return 13;
        case 'E':
          [[fallthrough]];
        case 'e':
          return 14;
        case 'F':
          [[fallthrough]];
        case 'f':
          return 15;
        default:
          throw step_error{"Invalid hex character!"};
      }
    };

    const auto& fst = hex.front();
    const auto& snd = hex.back();

    return (from_hex_to_decimal(fst) * 16) + from_hex_to_decimal(snd);
  };

  color result;

  if (length == 8) {  // ARGB
    result.alpha = from_hex(withoutHash.substr(0, 2));
    result.red = from_hex(withoutHash.substr(2, 2));
    result.green = from_hex(withoutHash.substr(4, 2));
    result.blue = from_hex(withoutHash.substr(6, 2));
  } else {  // RGB
    result.red = from_hex(withoutHash.substr(0, 2));
    result.green = from_hex(withoutHash.substr(2, 2));
    result.blue = from_hex(withoutHash.substr(4, 2));
  }

  return result;
}

}  // namespace step

#endif  // STEP_COLOR_HEADER
