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

#ifndef STEP_COLOR_SOURCE
#define STEP_COLOR_SOURCE

#include "step_color.h"

#include <charconv>
#include <iostream>
#include <string>

#include "step_exception.h"

namespace step {
namespace {

/**
 * Converts the supplied string that is in hex format to the corresponding
 * value.
 *
 * @param view the string that will be converted, e.g "E7".
 * @return the value of the supplied string.
 * @throws StepException if the conversion is unsuccessful.
 * @since 0.1.0
 */
uint8_t from_hex(std::string_view view)
{
  uint8_t result{};
  if (const auto [ptr, error] =
          std::from_chars(view.data(), view.data() + view.size(), result, 16);
      error != std::errc::invalid_argument &&
      error != std::errc::result_out_of_range) {
    return result;
  } else {
    using namespace std::string_literals;
    throw StepException{"Color > Failed to parse hex string: "s.append(view)};
  }
}

}  // namespace

STEP_DEF
Color::Color(std::string_view value)
{
  if (value.length() != 7 && value.length() != 9) {
    const auto badLen = std::to_string(value.length());
    throw StepException{"Color > Input string has incorrect length: " + badLen};
  }

  if (value.at(0) != '#') {
    throw StepException{"Color > Input string must begin with #"};
  }

  const auto withoutHash = value.substr(1);
  const auto len = withoutHash.length();

  try {
    m_red = from_hex(withoutHash.substr(0, 2));
    m_green = from_hex(withoutHash.substr(2, 2));
    m_blue = from_hex(withoutHash.substr(4, 2));
    if (len == 8) {
      m_alpha = from_hex(withoutHash.substr(6, 2));
    }
  } catch (const StepException& e) {
    throw;
  } catch (...) {
    throw StepException{"Couldn't create Color!"};
  }
}

}  // namespace step

#endif  // STEP_COLOR_SOURCE
