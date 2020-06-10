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

#ifndef STEP_PROPERTY_SOURCE
#define STEP_PROPERTY_SOURCE

#include "step_property.h"

#include <iostream>

#include "step_exception.h"

namespace step {

STEP_DEF
void from_json(const JSON& json, Property& property)
{
  property.m_name = json.at("name").get<std::string>();
  property.m_type = json.at("type").get<Property::Type>();
  switch (property.m_type) {
    case Property::Type::Int: {
      property.m_value.emplace<int>(json.at("value").get<int>());
      break;
    }
    case Property::Type::Float: {
      property.m_value.emplace<float>(json.at("value").get<float>());
      break;
    }
    case Property::Type::Bool: {
      property.m_value.emplace<bool>(json.at("value").get<bool>());
      break;
    }
    case Property::Type::Color: {
      property.m_value.emplace<Color>(json.at("value").get<std::string>());
      break;
    }
    case Property::Type::File:
      [[fallthrough]];
    case Property::Type::String: {
      property.m_value.emplace<std::string>(
          json.at("value").get<std::string>());
      break;
    }
    default:
      throw StepException{"Unknown property type!"};
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

#endif  // STEP_PROPERTY_SOURCE