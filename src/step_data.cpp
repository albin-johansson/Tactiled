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

#ifndef STEP_DATA_SOURCE
#define STEP_DATA_SOURCE

#include "step_data.h"

#include "step_exception.h"

namespace step::detail {

STEP_DEF
const Data::GIDData& Data::as_gid() const
{
  if (std::holds_alternative<GIDData>(m_data)) {
    return std::get<GIDData>(m_data);
  } else {
    throw StepException{"Data > Couldn't obtain GID data!"};
  }
}

STEP_DEF
const Data::Base64Data& Data::as_base64() const
{
  if (std::holds_alternative<Base64Data>(m_data)) {
    return std::get<Base64Data>(m_data);
  } else {
    throw StepException{"Data > Couldn't obtain Base64 data!"};
  }
}

STEP_DEF
void from_json(const JSON& json, Data& data)
{
  if (json.is_array()) {
    auto& gidData = data.m_data.emplace<Data::GIDData>();
    for (const auto& [key, value] : json.items()) {
      gidData.emplace_back(value.get<unsigned>());
    }
  } else if (json.is_string()) {
    data.m_data.emplace<Data::Base64Data>(json.get<Data::Base64Data>());
  } else {
    throw StepException{"Data > Failed to determine the kind of data!"};
  }
}

}  // namespace step::detail

#endif  // STEP_DATA_SOURCE
