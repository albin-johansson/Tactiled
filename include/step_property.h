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

#ifndef STEP_PROPERTY_HEADER
#define STEP_PROPERTY_HEADER

#include <variant>

#include "step_api.h"
#include "step_color.h"
#include "step_types.h"

namespace step {

/**
 * The Property class represents small objects that have a name, type and
 * value. A property can represent a string, int, float, bool, color or file.
 *
 * @since 0.1.0
 */
class Property final {
 public:
  /**
   * The Type enum class provides different values that represent the various
   * kinds of possible property types.
   *
   * <ul>
   *  <li><code>String</code> is for string values, such as "foo".</li>
   *  <li><code>Int</code> is for integer values, such as 27.</li>
   *  <li><code>Float</code> is for floating-point values, such as 182.4.</li>
   *  <li><code>Bool</code> is for the boolean values true/false.</li>
   *  <li><code>Color</code> is for ARGB and RGB colors, such as "AARRGGBB"
   *  or "RRGGBB".</li>
   *  <li><code>File</code> is for file paths, such as "some/path/abc.png</li>
   * </ul>
   *
   * @since 0.1.0
   */
  enum class Type { String, Int, Float, Bool, Color, File };

  STEP_API friend void from_json(const JSON&, Property&);

  /**
   * Returns the string value associated with the property, if there is one.
   * Note that this method is also used for obtaining the file path
   * associated with a Property instance of the <code>File</code> type.
   *
   * @return the string value associated with the property; nothing if there
   * is no such value.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<std::string> as_string() const noexcept;

  /**
   * Returns the color associated with the property, if there is one.
   *
   * @return the color associated with the property; nothing if there is no
   * such color.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Color> as_color() const noexcept;

  /**
   * Returns the integer value associated with the property, if there is one.
   *
   * @return the integer value associated with the property; nothing if there
   * is no such value.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<int> as_int() const noexcept;

  /**
   * Returns the float value associated with the property, if there is one.
   *
   * @return the float value associated with the property; nothing if there
   * is no such value.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<float> as_float() const noexcept;  // FIXME might
                                                      //  be double

  /**
   * Returns the boolean value associated with the property, if there is one.
   *
   * @return the boolean value associated with the property; nothing if there
   * is no such value.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<bool> as_bool() const noexcept;

  /**
   * Indicates whether or not the property holds a string value.
   *
   * @return true if the property holds a string value; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_string() const noexcept
  {
    return m_type == Type::String;
  }

  /**
   * Indicates whether or not the property holds a color value.
   *
   * @return true if the property holds a color value; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_color() const noexcept { return m_type == Type::Color; }

  /**
   * Indicates whether or not the property holds an int value.
   *
   * @return true if the property holds an int value; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_int() const noexcept { return m_type == Type::Int; }

  /**
   * Indicates whether or not the property holds a float value.
   *
   * @return true if the property holds a float value; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_float() const noexcept { return m_type == Type::Float; }

  /**
   * Indicates whether or not the property holds a boolean value.
   *
   * @return true if the property holds a boolean value; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_bool() const noexcept { return m_type == Type::Bool; }

  /**
   * Indicates whether or not the property contains a file path.
   *
   * @return true if the property contains a file path; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_file() const noexcept { return m_type == Type::File; }

  /**
   * Returns the name associated with the property.
   *
   * @return the name associated with the property.
   * @since 0.1.0
   */
  [[nodiscard]] std::string name() const { return m_name; }

  /**
   * Returns the type associated with the property.
   *
   * @return the type associated with the property.
   * @since 0.1.0
   */
  [[nodiscard]] Type type() const noexcept { return m_type; }

 private:
  std::string m_name;
  std::variant<std::string, Color, int, float, bool> m_value;
  Type m_type = Type::String;
};

STEP_API void from_json(const JSON& json, Property& property);

STEP_SERIALIZE_ENUM(Property::Type,
                    {{Property::Type::String, "string"},
                     {Property::Type::Int, "int"},
                     {Property::Type::Float, "float"},
                     {Property::Type::Bool, "bool"},
                     {Property::Type::Color, "color"},
                     {Property::Type::File, "file"}})

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_property.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_PROPERTY_HEADER
