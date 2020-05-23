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

#ifndef TACTILED_POINT_HEADER
#define TACTILED_POINT_HEADER

#include "step_api.h"
#include "step_types.h"

namespace step {

/**
 * The Point class represents a simple coordinate in the plane.
 *
 * @since 0.1.0
 */
class Point final {
 public:
  /**
   * Creates a point.
   *
   * @param json the JSON object that represents the point that will be parsed.
   * @throws StepException if the point cannot be parsed.
   * @since 0.1.0
   */
  STEP_API explicit Point(const JSONValue& json);

  /**
   * Returns the x-coordinate associated with the point.
   *
   * @return the x-coordinate of the point.
   * @since 0.1.0
   */
  [[nodiscard]] double x() const noexcept { return m_x; }

  /**
   * Returns the y-coordinate associated with the point.
   *
   * @return the y-coordinate of the point.
   * @since 0.1.0
   */
  [[nodiscard]] double y() const noexcept { return m_y; }

 private:
  double m_x = 0;
  double m_y = 0;
};

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "tactiled_point.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // TACTILED_POINT_HEADER