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

#ifndef STEP_PROPERTIES_SOURCE
#define STEP_PROPERTIES_SOURCE

#include "step_properties.h"

#include "step_exception.h"

namespace step {

STEP_DEF
bool Properties::has(const std::string& name) const
{
  return m_properties.count(name);
}

STEP_DEF
const Property& Properties::get(const std::string& name) const
{
  try {
    return m_properties.at(name);
  } catch (...) {
    throw StepException{"Properties > Couldn't lookup property: " + name};
  }
}

STEP_DEF
int Properties::amount() const noexcept
{
  return static_cast<int>(m_properties.size());
}

STEP_DEF
bool Properties::empty() const noexcept
{
  return m_properties.empty();
}

STEP_DEF
void from_json(const JSON& json, Properties& props)
{
  for (const auto& [key, value] : json.items()) {
    const auto property = value.get<Property>();
    props.m_properties.emplace(property.name(), property);
  }
}

}  // namespace step

#endif  // STEP_PROPERTIES_SOURCE
