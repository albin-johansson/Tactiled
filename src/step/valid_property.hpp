#ifndef STEP_VALID_PROPERTY_HEADER
#define STEP_VALID_PROPERTY_HEADER

#include <string>       // string
#include <type_traits>  // is_same_v, is_convertible_v

#include "color.hpp"

namespace step::detail {

template <typename T>
[[nodiscard]] constexpr auto valid_property_type() noexcept -> bool
{
  return std::is_same_v<T, bool> || std::is_same_v<T, int> ||
         std::is_same_v<T, float> || std::is_same_v<T, color> ||
         std::is_same_v<T, file> || std::is_same_v<T, object_ref> ||
         std::is_convertible_v<T, std::string>;
}

}  // namespace step::detail

#endif  // STEP_VALID_PROPERTY_HEADER
