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

#ifndef TACTILED_API_HEADER
#define TACTILED_API_HEADER

#include "tactiled_cfg.h"

// Define TACTILED_API for any platform
// https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
#if defined(_WIN32) && !defined(TACTILED_API)
#ifdef WIN_EXPORT
#define TACTILED_API __declspec(dllexport)
#else
#define TACTILED_API __declspec(dllimport)
#endif  // WIN_EXPORT
#else
#define TACTILED_API
#endif  // defined(_WIN32) && !defined(TACTILED_API)

// When header-only mode is enabled, definitions are specified as inline
#if !defined(TACTILED_DEF) && defined(TACTILED_HEADER_ONLY)
#define TACTILED_DEF inline
#else
#define TACTILED_DEF
#endif

// Used for getters that aren't inlined
#define TACTILED_QUERY [[nodiscard]] TACTILED_API

#endif  // TACTILED_API_HEADER