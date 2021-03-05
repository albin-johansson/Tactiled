#ifndef STEP_DETAIL_HEADER
#define STEP_DETAIL_HEADER

#include <charconv>      // from_chars
#include <fstream>       // ifstream
#include <string_view>   // string_view
#include <system_error>  // errc

#include "common.hpp"
#include "error.hpp"

namespace step::detail {

template <typename T>
[[nodiscard]] auto from_string(const std::string_view str, const int base = 10)
    -> T
{
  T result{};

  const auto [ptr, error] =
      std::from_chars(str.data(), str.data() + str.size(), result, base);

  if (error == std::errc{}) {
    return result;

  } else {
    throw step_error{"Failed to from_string string to integral!"};
  }
}

inline auto from_hex(const std::string_view view) -> uint8
{
  try {
    return from_string<uint8>(view, 16);
  } catch (...) {
    throw step_error{"Failed to parse hex string!"};
  }
}

[[nodiscard]] inline auto parse_json(const std::string_view file)
    -> nlohmann::json
{
  if (!file.data()) {
    throw step_error{"Cannot parse JSON from null file!"};
  }

  nlohmann::json json;

  std::ifstream stream{file.data()};
  stream >> json;

  return json;
}

}  // namespace step::detail

#endif  // STEP_DETAIL_HEADER