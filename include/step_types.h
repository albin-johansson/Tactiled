/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_TYPES_HEADER
#define STEP_TYPES_HEADER

#include <json.hpp>
#include <named_type.hpp>
#include <optional>

#include "step_api.h"

namespace step {

using JSON = nlohmann::json;

using File = fluent::NamedType<std::string,
                               struct FileTag,
                               fluent::Comparable,
                               fluent::Printable>;

/**
 * The type used for global IDs (GIDs).
 *
 * @since 0.1.0
 */
using GID = unsigned int;

using LocalID = fluent::NamedType<int,
                                  struct LocalIDTag,
                                  fluent::Comparable,
                                  fluent::Addable,
                                  fluent::Subtractable,
                                  fluent::Printable>;

// using GlobalID = fluent::NamedType<unsigned,
//                                   struct GlobalIDTag,
//                                   fluent::Comparable,
//                                   fluent::Addable,
//                                   fluent::Subtractable,
//                                   fluent::Printable>;

using CZString = const char*;

template <typename T>
using Maybe = std::optional<T>;

inline constexpr std::nullopt_t nothing = std::nullopt;

[[nodiscard]] inline LocalID operator"" _lid(std::size_t value) noexcept
{
  return LocalID{static_cast<int>(value)};
}

/**
 * Constructs a File instance from a string literal.
 *
 * @param str the string that will be converted to a File instance.
 * @return a File instance.
 * @since 0.1.0
 */
[[nodiscard]] inline File operator"" _file(const char* str, std::size_t)
{
  return File{str};
}

}  // namespace step

#endif  // STEP_TYPES_HEADER
