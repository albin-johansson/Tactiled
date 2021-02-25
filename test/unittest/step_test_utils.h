#ifndef STEP_TEST_UTILS_HEADER
#define STEP_TEST_UTILS_HEADER

#include <string>
#include <string_view>

#include "utils.hpp"

namespace step::test {

template <typename T>
T make(const std::string& prefix, std::string_view file)
{
  const auto json = detail::parse_json(prefix + file.data());
  return json.get<T>();
}

}  // namespace step::test

#endif  // STEP_TEST_UTILS_HEADER
