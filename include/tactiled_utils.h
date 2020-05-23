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

#ifndef TACTILED_UTILS_HEADER
#define TACTILED_UTILS_HEADER

#include "tactiled_api.h"
#include "tactiled_types.h"

namespace step::detail {

/**
 * Parses the specified JSON file and returns the data associated with the
 * file as a JSON object.
 *
 * @param file the the JSON file that will be parsed.
 * @return a JSON object that contains the data from the parsed file.
 * @throws TactiledException if the file cannot be parsed.
 * @since 0.1.0
 */
[[nodiscard]] STEP_API JSON parse_json(CZString file);

}  // namespace step::detail

#ifdef STEP_HEADER_ONLY
#include "tactiled_utils.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // TACTILED_UTILS_HEADER
