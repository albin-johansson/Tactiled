#ifndef STEP_TEST_UTILS_HEADER
#define STEP_TEST_UTILS_HEADER

#include <string>
#include <string_view>

#include "step_utils.h"

namespace step::test {

template <typename T>
T make(const std::string& prefix,
       std::string_view file)  // TODO prefix string_view
{
  const auto json = detail::parse_json(prefix + file.data());
  return json.get<T>();
}

}  // namespace step::test

#endif  // STEP_TEST_UTILS_HEADER
