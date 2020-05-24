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

#ifndef STEP_ANIMATION_HEADER
#define STEP_ANIMATION_HEADER

#include <vector>

#include "step_api.h"
#include "step_frame.h"
#include "step_types.h"

namespace step {

class Animation final {
 public:
  friend void from_json(const JSON&, Animation&);

  [[nodiscard]] const std::vector<Frame>& frames() const { return m_frames; }

  [[nodiscard]] int length() const noexcept
  {
    return static_cast<int>(m_frames.size());
  }

 private:
  std::vector<Frame> m_frames;
};

#ifdef STEP_HEADER_ONLY
#include "step_animation.cpp"
#endif  // STEP_HEADER_ONLY

STEP_API void from_json(const JSON& json, Animation& animation);

}  // namespace step

#endif  // STEP_ANIMATION_HEADER
