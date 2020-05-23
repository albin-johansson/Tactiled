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

#ifndef TACTILED_PROPERTY_SOURCE
#define TACTILED_PROPERTY_SOURCE

#include "step_property.h"

#include <iostream>

#include "step_exception.h"

namespace step {

STEP_DEF
Property::Property(const JSONValue& json)
{
  m_name = json.at("name").get<std::string>();
  m_type = json.at("type").get<Property::Type>();
  switch (m_type) {
    case Type::Int: {
      m_value.emplace<int>(json.at("value").get<int>());
      break;
    }
    case Type::Float: {
      m_value.emplace<float>(json.at("value").get<float>());
      break;
    }
    case Type::Bool: {
      m_value.emplace<bool>(json.at("value").get<bool>());
      break;
    }
    case Type::Color: {
      m_value.emplace<Color>(json.at("value").get<std::string>());
      break;
    }
    case Type::File:
      [[fallthrough]];
    case Type::String: {
      m_value.emplace<std::string>(json.at("value").get<std::string>());
      break;
    }
    default:
      throw TactiledException{"Unknown property type!"};
  }
}

STEP_DEF
std::optional<std::string> Property::as_string() const noexcept
{
  if (std::holds_alternative<std::string>(m_value)) {
    return std::get<std::string>(m_value);
  } else {
    return nothing;
  }
}

STEP_DEF
std::optional<Color> Property::as_color() const noexcept
{
  if (std::holds_alternative<Color>(m_value)) {
    return std::get<Color>(m_value);
  } else {
    return nothing;
  }
}

STEP_DEF
std::optional<int> Property::as_int() const noexcept
{
  if (std::holds_alternative<int>(m_value)) {
    return std::get<int>(m_value);
  } else {
    return nothing;
  }
}

STEP_DEF
std::optional<float> Property::as_float() const noexcept
{
  if (std::holds_alternative<float>(m_value)) {
    return std::get<float>(m_value);
  } else {
    return nothing;
  }
}

STEP_DEF
std::optional<bool> Property::as_bool() const noexcept
{
  if (std::holds_alternative<bool>(m_value)) {
    return std::get<bool>(m_value);
  } else {
    return nothing;
  }
}

}  // namespace step

#endif  // TACTILED_PROPERTY_SOURCE