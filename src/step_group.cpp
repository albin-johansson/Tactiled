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

#ifndef STEP_GROUP_SOURCE
#define STEP_GROUP_SOURCE

#include "step_group.h"

#include "step_layer.h"

namespace step {

STEP_DEF
const Layer& Group::at(int index) const
{
  return *m_layers.at(static_cast<std::size_t>(index));
}

STEP_DEF
int Group::layers() const noexcept
{
  return static_cast<int>(m_layers.size());
}

STEP_DEF
void from_json(const JSON& json, Group& group)  // FIXME
{
  for (const auto& [key, value] : json.at("layers").items()) {
    group.m_layers.push_back(std::make_unique<Layer>(value));
  }
}

}  // namespace step

#endif  // STEP_GROUP_SOURCE
