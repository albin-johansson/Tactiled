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

#ifndef STEP_OBJECT_HEADER
#define STEP_OBJECT_HEADER

#include <string>
#include <variant>
#include <vector>

#include "step_api.h"
#include "step_point.h"
#include "step_properties.h"
#include "step_text.h"
#include "step_types.h"

namespace step {

struct Polygon {
  std::vector<Point> points;
};

struct Polyline {
  std::vector<Point> points;
};

struct Template {
  std::string templateFile;
};

class Object final {
 public:
  STEP_API friend void from_json(const JSON&, Object&);

  STEP_QUERY int id() const noexcept;

  STEP_QUERY double x() const noexcept;

  STEP_QUERY double y() const noexcept;

  STEP_QUERY double width() const noexcept;

  STEP_QUERY double height() const noexcept;

  STEP_QUERY double rotation() const noexcept;

  STEP_QUERY std::string name() const;

  STEP_QUERY std::string type() const;

  STEP_QUERY const Properties& properties() const noexcept;

  STEP_QUERY Maybe<Polygon> polygon() const noexcept;

  STEP_QUERY Maybe<Polyline> polyline() const noexcept;

  STEP_QUERY Maybe<GID> tile_gid() const noexcept;

  STEP_QUERY Maybe<Template> template_data() const;

  STEP_QUERY Maybe<Text> text() const;

  STEP_QUERY bool is_ellipse() const noexcept;

  STEP_QUERY bool is_point() const noexcept;

  STEP_QUERY bool visible() const noexcept;

  // TODO is_polygon, is_polyline, is_text, is_template, is_tile

 private:
  int m_id{0};  // incremental id
  double m_x{0};
  double m_y{0};
  double m_width{0};
  double m_height{0};
  double m_rotation{0};
  std::string m_name;
  std::string m_type;
  Properties m_properties;
  std::variant<Polygon, Polyline, Text, Template, GID> m_typeData;
  bool m_ellipse{false};
  bool m_point{false};
  bool m_visible{true};
};

STEP_API void from_json(const JSON& json, Object& object);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_object.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_OBJECT_HEADER
