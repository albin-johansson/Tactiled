/**
 * MIT License
 *
 * Copyright (c) 2020-2021 Albin Johansson
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

// #include "animation.hpp"
#ifndef STEP_ANIMATION_HEADER
#define STEP_ANIMATION_HEADER

#include <vector>

// #include "frame.hpp"
#ifndef STEP_FRAME_HEADER
#define STEP_FRAME_HEADER

// #include "step_api.hpp"
#ifndef STEP_API_HEADER
#define STEP_API_HEADER

// Define STEP_API for any platform
// https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
#if defined(_WIN32) && !defined(STEP_API)
#ifdef WIN_EXPORT
#define STEP_API __declspec(dllexport)
#else
#define STEP_API __declspec(dllimport)
#endif  // WIN_EXPORT
#else
#define STEP_API
#endif  // defined(_WIN32) && !defined(STEP_API)

// Used for getters that aren't inlined
#define STEP_QUERY [[nodiscard]] STEP_API

#endif  // STEP_API_HEADER
// #include "types.hpp"
#ifndef STEP_TYPES_HEADER
#define STEP_TYPES_HEADER

#include <cstdint>
#include <filesystem>
#include <json.hpp>
#include <named_type.hpp>
#include <optional>

// #include "step_api.hpp"


namespace step {

namespace fs = std::filesystem;

using nlohmann::json;
using czstring = const char*;

/**
 * The type used for properties that represent a file path.
 *
 * @since 0.1.0
 */
using file = fluent::NamedType<std::string,
                               struct file_t,
                               fluent::Comparable,
                               fluent::Printable>;

/**
 * The type used for global IDs (GIDs).
 *
 * @since 0.1.0
 */
using global_id = fluent::NamedType<unsigned,
                                    struct global_id_t,
                                    fluent::Comparable,
                                    fluent::Addable,
                                    fluent::Subtractable,
                                    fluent::Printable>;

/**
 * The type used for local IDs (LIDs).
 *
 * @since 0.1.0
 */
using local_id = fluent::NamedType<int,
                                   struct local_id_t,
                                   fluent::Comparable,
                                   fluent::Addable,
                                   fluent::Subtractable,
                                   fluent::Printable>;

/**
 * The type used for object references.
 *
 * @since 0.2.0
 */
using object_ref = fluent::NamedType<int,
                                     struct object_ref_t,
                                     fluent::Comparable,
                                     fluent::Addable,
                                     fluent::Subtractable,
                                     fluent::Printable>;

/**
 * Constructs a global ID from an integer literal.
 *
 * @param value the literal that will be converted.
 * @return a global ID value.
 * @since 0.1.0
 */
[[nodiscard]] inline auto operator"" _gid(unsigned long long int value) noexcept
    -> global_id
{
  return global_id{static_cast<unsigned>(value)};
}

/**
 * Constructs a local ID from an integer literal.
 *
 * @param value the literal that will be converted.
 * @return a local ID value.
 * @since 0.1.0
 */
[[nodiscard]] inline auto operator"" _lid(unsigned long long int value) noexcept
    -> local_id
{
  return local_id{static_cast<int>(value)};
}

/**
 * Constructs a File instance from a string literal.
 *
 * @param str the string that will be converted to a File instance.
 * @return a File instance.
 * @since 0.1.0
 */
[[nodiscard]] inline auto operator"" _file(const char* str, std::size_t) -> file
{
  return file{str};
}

}  // namespace step

#endif  // STEP_TYPES_HEADER


namespace step {

/**
 * The Frame class represents a frame in an animation.
 *
 * @since 0.1.0
 */
class Frame final
{
 public:
  explicit Frame(const json& json)
      : m_tileID{json.at("tileid").get<int>()}
      , m_duration{json.at("duration").get<int>()}
  {}

  /**
   * Returns the local tile ID that is associated with the frame.
   *
   * @return the local tile ID that is associated with the frame.
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tileID;
  }

  /**
   * Returns the duration of this frame, in milliseconds.
   *
   * @return the duration of this frame, in milliseconds.
   * @since 0.1.0
   */
  [[nodiscard]] auto duration() const noexcept -> int
  {
    return m_duration;
  }

 private:
  local_id m_tileID{0};
  int m_duration{0};
};

}  // namespace step

#endif  // STEP_FRAME_HEADER
// #include "step_api.hpp"

// #include "types.hpp"

// #include "utils.hpp"
#ifndef STEP_UTILS_HEADER
#define STEP_UTILS_HEADER

#include <charconv>
#include <fstream>
#include <memory>
#include <named_type.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// #include "step_api.hpp"

// #include "step_exception.hpp"
#ifndef STEP_EXCEPTION_HEADER
#define STEP_EXCEPTION_HEADER

#include <exception>
#include <utility>

// #include "types.hpp"


namespace step {

class step_exception final : public std::exception
{
 public:
  step_exception() noexcept = default;

  explicit step_exception(std::string what) : m_what{std::move(what)}
  {}

  ~step_exception() noexcept override = default;

  czstring what() const noexcept override
  {
    return m_what.c_str();
  }

 private:
  std::string m_what;
};

}  // namespace step

#endif  // STEP_EXCEPTION_HEADER

// #include "types.hpp"


namespace step::detail {

/**
 * Parses the specified JSON file and returns the data associated with the
 * file as a JSON object.
 *
 * @param file the the JSON file that will be parsed.
 * @return a JSON object that contains the data from the parsed file.
 * @throws step_exception if the file cannot be parsed.
 * @since 0.1.0
 */
[[nodiscard]] inline auto parse_json(std::string_view file) -> json
{
  if (!file.data()) {
    throw step_exception{"Cannot parse JSON from null file!"};
  }

  try {
    json json;
    std::ifstream stream{file.data()};
    stream >> json;
    return json;
  } catch (const std::exception& e) {
    using namespace std::string_literals;
    throw step_exception{e.what() ? e.what() : "Failed to parse JSON!"s};
  }
}

template <typename T>
void bind_opt(const json& json,
              std::string_view key,
              std::optional<T>& attribute)
{
  if (json.contains(key)) {
    attribute = json.at(key.data()).get<T>();
  }
}

template <typename T>
void emplace_opt(const json& json,
                 const std::string& key,
                 std::optional<T>& attribute)
{
  if (json.contains(key)) {
    attribute.emplace(json.at(key));
  }
}

template <typename T>
void safe_bind(const json& json, std::string_view key, T& value)
{
  if (json.contains(key)) {
    json.at(key.data()).get_to(value);
  }
}

template <typename T>
auto safe_get(const json& json, const std::string& key, T defaultValue = {})
    -> T
{
  static_assert(
      std::is_default_constructible_v<T>,
      "The type must be default constructible in order to use safe_bind!");
  if (json.contains(key)) {
    return json.at(key).get<T>();
  } else {
    return defaultValue;
  }
}

template <typename T>
[[nodiscard]] auto safe_bind_unique(const json& json, const std::string& key)
    -> std::unique_ptr<T>
{
  if (json.contains(key)) {
    return std::make_unique<T>(json.at(key));
  } else {
    return nullptr;
  }
}

template <typename T>
void emplace(const json& json, const std::string& key, T& value)
{
  if (json.contains(key)) {
    value = json.at(key);
  }
}

template <typename Container>
[[nodiscard]] auto fill(const json& json, const std::string& key) -> Container
{
  Container container;
  for (const auto& [key, value] : json.at(key).items()) {
    container.emplace_back(value);
  }
  return container;
}

template <typename Container>
[[nodiscard]] auto fill(const json& json) -> Container
{
  Container container;
  for (const auto& [key, value] : json.items()) {
    container.emplace_back(value);
  }
  return container;
}

/**
 * Attempts to convert a string to an integral value.
 *
 * @tparam T the integral type that will be used.
 * @param str the string that represents the integer.
 * @param base the base that will be used, defaults to 10.
 * @return the integral value.
 * @throws step_exception if the string cannot be converted.
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] auto from_string(const std::string_view str, const int base = 10) -> T
{
  T result{};
  if (const auto [ptr, error] =
          std::from_chars(str.data(), str.data() + str.size(), result, base);
      error != std::errc::invalid_argument &&
      error != std::errc::result_out_of_range) {
    return result;
  } else {
    throw step_exception{"Failed to convert string to integral!"};
  }
}

}  // namespace step::detail

#endif  // STEP_UTILS_HEADER


namespace step {

/**
 * @class animation
 *
 * @brief Represents a collection of frames, used to animate tiles.
 *
 * @since 0.1.0
 *
 * @todo Add begin() and end(), maybe even at() & operator[].
 *
 * @headerfile step_animation.hpp
 */
class animation final
{
 public:
  explicit animation(const json& json)
      : m_frames{detail::fill<std::vector<Frame>>(json)}
  {}

  /**
   * @brief Returns the frames associated with the animation.
   *
   * @return the frames associated with the animation.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto frames() const -> const std::vector<Frame>&
  {
    return m_frames;
  }

  /**
   * @brief Returns the amount of frames that constitute the animation.
   *
   * @return the amount of frames that constitute the animation.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto num_frames() const noexcept -> int
  {
    return static_cast<int>(m_frames.size());
  }

 private:
  std::vector<Frame> m_frames;
};

}  // namespace step

#endif  // STEP_ANIMATION_HEADER

// #include "chunk.hpp"
#ifndef STEP_CHUNK_HEADER
#define STEP_CHUNK_HEADER

// #include "data.hpp"
#ifndef STEP_DATA_HEADER
#define STEP_DATA_HEADER

#include <string>
#include <variant>
#include <vector>

// #include "step_api.hpp"

// #include "step_exception.hpp"

// #include "types.hpp"


namespace step::detail {

/**
 * @class data
 *
 * @brief A helper class that represents either GID or Base64 tile data.
 *
 * @since 0.1.0
 *
 * @headerfile step_data.hpp
 */
class data final
{
 public:
  using gid_data = std::vector<global_id>;
  using base64_data = std::string;

  explicit data(const json& json)
  {
    if (json.is_array()) {
      auto& gidData = m_data.emplace<gid_data>();
      for (const auto& [key, value] : json.items()) {
        gidData.emplace_back(value.get<unsigned>());
      }
    } else if (json.is_string()) {
      m_data.emplace<data::base64_data>(json.get<data::base64_data>());
    } else {
      throw step_exception{"Failed to determine the kind of data!"};
    }
  }

  /**
   * @brief Returns the GID data associated with the Data instance.
   *
   * @details This method throws if the internal data isn't actually GID data.
   *
   * @return the GID data associated with the Data instance.
   *
   * @throws step_exception if the data cannot be obtained.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto as_gid() const -> const gid_data&
  {
    if (std::holds_alternative<gid_data>(m_data)) {
      return std::get<gid_data>(m_data);
    } else {
      throw step_exception{"Couldn't obtain GID data!"};
    }
  }

  /**
   * @brief Returns the Base64 data associated with the Data instance.
   *
   * @note This function throws if the internal data isn't actually Base64
   * data.
   *
   * @return the Base64 data associated with the data instance.
   *
   * @throws step_exception if the data cannot be obtained.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto as_base64() const -> const base64_data&
  {
    if (std::holds_alternative<base64_data>(m_data)) {
      return std::get<base64_data>(m_data);
    } else {
      throw step_exception{"Couldn't obtain Base64 data!"};
    }
  }

 private:
  std::variant<gid_data, base64_data> m_data;
};

}  // namespace step::detail

#endif  // STEP_DATA_HEADER

// #include "step_api.hpp"

// #include "types.hpp"


namespace step {

/**
 * @class chunk
 *
 * @brief Represents "chunks", that store the tile layer data for
 * infinite maps.
 *
 * @since 0.1.0
 *
 * @headerfile step_chunk.hpp
 */
class chunk final
{
 public:
  explicit chunk(const json& json)
      : m_x{json.at("x").get<int>()}
      , m_y{json.at("y").get<int>()}
      , m_width{json.at("width").get<int>()}
      , m_height{json.at("height").get<int>()}
      , m_data{json.at("data")}
  {}

  /**
   * @brief Returns the x-coordinate of the chunk.
   *
   * @return the x-coordinate of the chunk.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    return m_x;
  }

  /**
   * @brief Returns the y-coordinate of the chunk.
   *
   * @return the y-coordinate of the chunk.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    return m_y;
  }

  /**
   * @brief Returns the width of the chunk.
   *
   * @return the width of the chunk.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the chunk.
   *
   * @return the height of the chunk.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

  /**
   * @brief Returns the data associated with the chunk.
   *
   * @return the data associated with the chunk.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto data() const noexcept -> const detail::data&
  {
    return m_data;
  }

 private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  detail::data m_data;
};

}  // namespace step

#endif  // STEP_CHUNK_HEADER

// #include "color.hpp"
#ifndef STEP_COLOR_HEADER
#define STEP_COLOR_HEADER

#include <charconv>
#include <cstdint>
#include <string>
#include <string_view>

// #include "step_api.hpp"

// #include "step_exception.hpp"

// #include "types.hpp"

// #include "utils.hpp"


namespace step {
namespace detail {

/**
 * @brief Converts the supplied string that is in hex format to the
 * corresponding value.
 *
 * @param view the string that will be converted, e.g "E7".
 *
 * @return the value of the supplied string.
 *
 * @throws step_exception if the conversion is unsuccessful.
 *
 * @since 0.1.0
 */
inline auto from_hex(std::string_view view) -> uint8_t
{
  try {
    return convert<uint8_t>(view, 16);
  } catch (...) {
    using namespace std::string_literals;
    throw step_exception{"color > Failed to parse hex string: "s.append(view)};
  }
}

}  // namespace detail

/**
 * @class color
 *
 * @brief Represents a color with 8-bit components.
 *
 * @details Instances of this class can be created from either ARGB or RGB
 * format strings, e.g. `"#AABBCCDD"` or `"#AABBCC"`.
 *
 * @details It's even possible to create `color` instances from string-literals
 * at compile-time! The follow code snippet compiles.
 * @code{.cpp}
 *  constexpr step::color aarrggbb{"#AABBCCDD"};
 *  static_assert(aarrggbb.alpha() == 0xAA);
 *  static_assert(aarrggbb.red() == 0xBB);
 *  static_assert(aarrggbb.green() == 0xCC);
 *  static_assert(aarrggbb.blue() == 0xDD);
 *
 *  constexpr step::color rrggbb{"#AABBCC"};
 *  static_assert(rrggbb.alpha() == 0xFF);
 *  static_assert(rrggbb.red() == 0xAA);
 *  static_assert(rrggbb.green() == 0xBB);
 *  static_assert(rrggbb.blue() == 0xCC);
 * @endcode
 *
 * @since 0.1.0
 */
class color final
{
 public:
  /**
   * @brief Creates a color equivalent to `"#FF000000`.
   *
   * @since 0.1.0
   */
  color() noexcept = default;

  /**
   * @brief Creates a color from the supplied string that is in either ARGB or
   * RGB format.
   *
   * @note If the supplied string is using the RGB format, then the alpha
   * value used is 255.
   *
   * @param value the string that contains the color information, in ARGB or
   * RGB format.
   *
   * @throws step_exception if the color cannot be created.
   *
   * @since 0.1.0
   */
  explicit color(std::string_view value)
  {
    if (value.length() != 7 && value.length() != 9) {
      const auto badLen = std::to_string(value.length());
      throw step_exception{"color > Input string has incorrect length: " +
                           badLen};
    }

    if (value.at(0) != '#') {
      throw step_exception{"color > Input string must begin with #"};
    }

    const auto withoutHash = value.substr(1);
    const auto len = withoutHash.length();

    try {
      if (len == 8) {  // AARRGGBB
        m_alpha = detail::from_hex(withoutHash.substr(0, 2));
        m_red = detail::from_hex(withoutHash.substr(2, 2));
        m_green = detail::from_hex(withoutHash.substr(4, 2));
        m_blue = detail::from_hex(withoutHash.substr(6, 2));
      } else {  // RRGGBB
        m_red = detail::from_hex(withoutHash.substr(0, 2));
        m_green = detail::from_hex(withoutHash.substr(2, 2));
        m_blue = detail::from_hex(withoutHash.substr(4, 2));
      }

    } catch (const step_exception&) {
      throw;
    } catch (...) {
      throw step_exception{"Couldn't create color!"};
    }
  }

  /**
   * @brief Creates a color from the supplied string that is in either ARGB or
   * RGB format.
   *
   * @details This constructor constructs a color from a string literal at
   * compile-time! It doesn't get much more efficient than that.
   *
   * @note If the supplied string is using the RGB format, then the alpha
   * value used is 255.
   *
   * @tparam size the length of the string, including the null-terminator.
   *
   * @param s the compile-time string literal in ARGB or RGB format.
   *
   * @since 0.2.0
   */
  template <std::size_t size>
  constexpr explicit color(const char (&s)[size])
  {
    // the assertion includes the null-terminator
    static_assert(size == 8 || size == 10,
                  "String literal has invalid length!");

    const std::string_view str = s;

    const auto withoutHash = str.substr(1);
    const auto len = withoutHash.length();

    constexpr auto from_hex = [](std::string_view hex) -> std::uint8_t {
      constexpr auto from_hex_to_decimal = [](const char ch) -> std::uint8_t {
        switch (ch) {
          case '0':
            return 0;
          case '1':
            return 1;
          case '2':
            return 2;
          case '3':
            return 3;
          case '4':
            return 4;
          case '5':
            return 5;
          case '6':
            return 6;
          case '7':
            return 7;
          case '8':
            return 8;
          case '9':
            return 9;
          case 'A':
            [[fallthrough]];
          case 'a':
            return 10;
          case 'B':
            [[fallthrough]];
          case 'b':
            return 11;
          case 'C':
            [[fallthrough]];
          case 'c':
            return 12;
          case 'D':
            [[fallthrough]];
          case 'd':
            return 13;
          case 'E':
            [[fallthrough]];
          case 'e':
            return 14;
          case 'F':
            [[fallthrough]];
          case 'f':
            return 15;
          default:
            throw step_exception{"Invalid hex character!"};
        }
      };

      const auto& fst = hex.front();
      const auto& snd = hex.back();

      return (from_hex_to_decimal(fst) * 16) + from_hex_to_decimal(snd);
    };

    if (len == 8) {  // ARGB
      m_alpha = from_hex(withoutHash.substr(0, 2));
      m_red = from_hex(withoutHash.substr(2, 2));
      m_green = from_hex(withoutHash.substr(4, 2));
      m_blue = from_hex(withoutHash.substr(6, 2));
    } else {  // RGB
      m_red = from_hex(withoutHash.substr(0, 2));
      m_green = from_hex(withoutHash.substr(2, 2));
      m_blue = from_hex(withoutHash.substr(4, 2));
    }
  }

  /**
   * @brief Returns the value of the red component of the color.
   *
   * @return the value of the red component of the color, in the range [0, 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto red() const noexcept -> std::uint8_t
  {
    return m_red;
  }

  /**
   * @brief Returns the value of the green component of the color.
   *
   * @return the value of the green component of the color, in the range [0,
   * 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto green() const noexcept -> std::uint8_t
  {
    return m_green;
  }

  /**
   * @brief Returns the value of the blue component of the color.
   *
   * @return the value of the blue component of the color, in the range [0,
   * 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto blue() const noexcept -> std::uint8_t
  {
    return m_blue;
  }

  /**
   * @brief Returns the value of the alpha component of the color.
   *
   * @return the value of the alpha component of the color, in the range [0,
   * 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto alpha() const noexcept -> std::uint8_t
  {
    return m_alpha;
  }

 private:
  std::uint8_t m_red{};
  std::uint8_t m_green{};
  std::uint8_t m_blue{};
  std::uint8_t m_alpha{0xFF};
};

/**
 * @brief Indicates whether or not two colors are the same.
 *
 * @details Two colors are considered to be equal if all of their respective
 * color components are exactly the same.
 *
 * @param lhs the left-hand side color.
 * @param rhs the right-hand side color.
 *
 * @return `true` if the colors are the same; `false` otherwise.
 *
 * @since 0.1.0
 */
[[nodiscard]] inline constexpr auto operator==(const color& lhs,
                                               const color& rhs) noexcept
    -> bool
{
  return lhs.red() == rhs.red() && lhs.green() == rhs.green() &&
         lhs.blue() == rhs.blue() && lhs.alpha() == rhs.alpha();
}

/**
 * @brief Indicates whether or not two colors aren't the same.
 *
 * @param lhs the left-hand side color.
 * @param rhs the right-hand side color.
 *
 * @return `true` if the colors aren't the same; `false` otherwise.
 *
 * @since 0.1.0
 */
[[nodiscard]] inline constexpr auto operator!=(const color& lhs,
                                               const color& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace step

#endif  // STEP_COLOR_HEADER

// #include "data.hpp"

// #include "frame.hpp"

// #include "grid.hpp"
#ifndef STEP_GRID_HEADER
#define STEP_GRID_HEADER

// #include "step_api.hpp"

// #include "types.hpp"


namespace step {

/**
 * @class grid
 *
 * @brief Provides information about the grid of tiles in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_grid.hpp
 */
class grid final
{
 public:
  /**
   * @enum grid::orientation
   *
   * @brief Provides values for the different possible  orientations of a
   * grid in a tileset.
   *
   * @since 0.1.0
   */
  enum class orientation
  {
    orthogonal,
    isometric
  };

  friend void from_json(const json&, grid&);

  /**
   * @brief Returns the orientation of the grid.
   *
   * @details The default value of this property is `Orthogonal`.
   *
   * @return the orientation of the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_orientation() const noexcept -> orientation
  {
    return m_orientation;
  }

  /**
   * @brief Returns the width of the cells in the grid.
   *
   * @return the width of the cells in the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the cells in the grid.
   *
   * @return the height of the cells in the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

 private:
  orientation m_orientation{orientation::orthogonal};
  int m_width{};
  int m_height{};
};

inline void from_json(const json& json, grid& grid)
{
  json.at("width").get_to(grid.m_width);
  json.at("height").get_to(grid.m_height);
  json.at("orientation").get_to(grid.m_orientation);
}

NLOHMANN_JSON_SERIALIZE_ENUM(grid::orientation,
                             {{grid::orientation::orthogonal, "orthogonal"},
                              {grid::orientation::isometric, "isometric"}})

}  // namespace step

#endif  // STEP_GRID_HEADER

// #include "image_layer.hpp"
#ifndef STEP_IMAGE_LAYER_HEADER
#define STEP_IMAGE_LAYER_HEADER

#include <string>

// #include "color.hpp"

// #include "step_api.hpp"

// #include "types.hpp"


namespace step {

/**
 * @class image_layer
 *
 * @brief Represents the API for layers that represent "image layers", layers
 * that are represented by an image.
 *
 * @since 0.1.0
 *
 * @headerfile step_image_layer.hpp
 */
class image_layer final
{
 public:
  friend void from_json(const json&, image_layer&);

  /**
   * @brief Returns the image used by the image layer.
   *
   * @return the image associated with the image layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image() const -> const std::string&
  {
    return m_image;
  }

  /**
   * @brief Returns the transparent color used by the image layer.
   *
   * @details This property is optional.
   *
   * @return the transparent color used by the image layer; `std::nullopt` if
   * there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto transparent_color() const noexcept
      -> const std::optional<color>&
  {
    return m_transparentColor;
  }

 private:
  std::string m_image;
  std::optional<color> m_transparentColor;
};

inline void from_json(const json& json, image_layer& layer)
{
  json.at("image").get_to(layer.m_image);
  if (json.count("transparentcolor")) {
    layer.m_transparentColor =
        color{json.at("transparentcolor").get<std::string>()};
  }
}

}  // namespace step

#endif  // STEP_IMAGE_LAYER_HEADER

// #include "layer.hpp"
#ifndef STEP_LAYER_HEADER
#define STEP_LAYER_HEADER

#include <memory>
#include <string>
#include <variant>
#include <vector>

// #include "image_layer.hpp"

// #include "object_group.hpp"
#ifndef STEP_OBJECT_GROUP_HEADER
#define STEP_OBJECT_GROUP_HEADER

#include <vector>

// #include "object.hpp"
#ifndef STEP_OBJECT_HEADER
#define STEP_OBJECT_HEADER

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

// #include "point.hpp"
#ifndef STEP_POINT_HEADER
#define STEP_POINT_HEADER

// #include "step_api.hpp"

// #include "types.hpp"


namespace step {

/**
 * @class point
 *
 * @brief Represents a simple 2D-coordinate in the plane.
 *
 * @since 0.1.0
 *
 * @headerfile step_point.hpp
 */
class point final
{
 public:
  point() noexcept = default;

  /**
   * @brief Parses a point from a JSON object.
   *
   * @param json the JSON object that represents the point.
   *
   * @since 0.2.0
   */
  explicit point(const json& json)
      : m_x{json.at("x").get<double>()}
      , m_y{json.at("y").get<double>()}
  {}

  /**
   * @brief Returns the x-coordinate associated with the point.
   *
   * @return the x-coordinate of the point.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> double
  {
    return m_x;
  }

  /**
   * @brief Returns the y-coordinate associated with the point.
   *
   * @return the y-coordinate of the point.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> double
  {
    return m_y;
  }

 private:
  double m_x{};
  double m_y{};
};

}  // namespace step

#endif  // STEP_POINT_HEADER
// #include "properties.hpp"
#ifndef STEP_PROPERTIES_HEADER
#define STEP_PROPERTIES_HEADER

#include <algorithm>    // for_each
#include <functional>   // less
#include <map>          // map
#include <string>       // string
#include <string_view>  // string_view

// #include "color.hpp"

// #include "property.hpp"
#ifndef STEP_PROPERTY_HEADER
#define STEP_PROPERTY_HEADER

#include <string>
#include <type_traits>
#include <variant>

// #include "color.hpp"

// #include "step_api.hpp"

// #include "types.hpp"

// #include "utils.hpp"

// #include "valid_property.hpp"
#ifndef STEP_VALID_PROPERTY_HEADER
#define STEP_VALID_PROPERTY_HEADER

#include <string>       // string
#include <type_traits>  // is_same_v, is_convertible_v

// #include "color.hpp"


namespace step::detail {

template <typename T>
[[nodiscard]] constexpr auto valid_property_type() noexcept -> bool
{
  return std::is_same_v<T, bool> || std::is_same_v<T, int> ||
         std::is_same_v<T, float> || std::is_same_v<T, color> ||
         std::is_same_v<T, file> || std::is_same_v<T, object_ref> ||
         std::is_convertible_v<T, std::string>;
}

}  // namespace step::detail

#endif  // STEP_VALID_PROPERTY_HEADER


namespace step {

/**
 * @class property
 *
 * @brief Represents small objects that have a name, type and value.
 *
 * @details A property can represent a `std::string`, `int`, `float`, `bool`,
 * `color` or `file`.
 *
 * @since 0.1.0
 *
 * @headerfile step_property.hpp
 */
class property final
{
 public:
  /**
   * @enum type
   *
   * @brief Provides different values that represent the various kinds of
   * possible property types.
   *
   * @since 0.1.0
   *
   * @headerfile step_property.hpp
   */
  enum class type
  {
    string,    ///< For string values, such as `"foo"`.
    integer,   ///< For integer values, e.g. `27`.
    floating,  ///< For floating-point values, e.g. `182.4`.
    boolean,   ///< For the boolean values `true`/`false`.
    color,     ///< For ARGB/RGB colors, e.g. `"AARRGGBB"` and `"RRGGBB"`.
    file,      ///< For file paths, e.g. `"some/path/abc.png"`.
    object     ///< For referencing other objects. Really just an integer ID.
  };

  explicit property(const json& json)
      : m_name{json.at("name").get<std::string>()}
      , m_type{json.at("type").get<property::type>()}
  {
    switch (m_type) {
      case property::type::integer: {
        m_value.emplace<int>(json.at("value").get<int>());
        break;
      }
      case property::type::floating: {
        m_value.emplace<float>(json.at("value").get<float>());
        break;
      }
      case property::type::boolean: {
        m_value.emplace<bool>(json.at("value").get<bool>());
        break;
      }
      case property::type::color: {
        m_value.emplace<color>(json.at("value").get<std::string>());
        break;
      }
      case property::type::file: {
        m_value.emplace<file>(json.at("value").get<std::string>());
        break;
      }
      case property::type::object: {
        m_value.emplace<object_ref>(json.at("value").get<int>());
        break;
      }
      case property::type::string: {
        m_value.emplace<std::string>(json.at("value").get<std::string>());
        break;
      }
      default:
        throw step_exception{"Unknown property type!"};
    }
  }

  /**
   * @brief Returns the value of the property as the specified type.
   *
   * @note This method will throw an exception if the property doesn't contain
   * the specified type.
   *
   * @details A compile-time error will be raised if the type of the supplied
   * value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type of the value that will be returned. Must be the same
   * type of the value stored in the property. An unsupported type will cause a
   * compile-time error.
   *
   * @return the value of the property.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto get() const -> const T&
  {
    return std::get<T>(m_value);
  }

  /**
   * @brief Attempts to return the value of the property as the specified type.
   *
   * @note This method doesn't throw any exceptions on its own.
   *
   * @details If the property doesn't contain a value of the specified type,
   * then the supplied default value is returned instead.
   *
   * @details A compile-time error will be raised if the type of the supplied
   * value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type of the value that will be obtained. An unsupported type
   * will cause a compile-time error.
   *
   * @param defaultValue the backup value that will be returned if the
   * desired value cannot be obtained.
   *
   * @return the value stored in the property; `defaultValue` if the property
   * doesn't contain a value of the specified type.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto get_or(const T& defaultValue) const -> const T&
  {
    if (is<T>()) {
      return get<T>();
    } else {
      return defaultValue;
    }
  }

  /**
   * @brief Indicates whether or not the property holds a value of the specified
   * type.
   *
   * @details A compile-time error will be raised if the type of the supplied
   * value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type to compare with the type of the stored value. An
   * unsupported type will cause a compile-time error.
   *
   * @return `true` if the property holds a value of the specified type; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    if constexpr (std::is_same_v<T, bool>) {
      return m_type == type::boolean;

    } else if constexpr (std::is_same_v<T, int>) {
      return m_type == type::integer;

    } else if constexpr (std::is_same_v<T, float>) {
      return m_type == type::floating;

    } else if constexpr (std::is_same_v<T, color>) {
      return m_type == type::color;

    } else if constexpr (std::is_same_v<T, file>) {
      return m_type == type::file;

    } else if constexpr (std::is_same_v<T, object_ref>) {
      return m_type == type::object;

    } else /*if constexpr (std::is_convertible_v<T, std::string>)*/ {
      return m_type == type::string;
    }
  }

  /**
   * @brief Indicates whether or not the property holds a value equal to the
   * specified value.
   *
   * @tparam T the type of the value. An unsupported type will cause a
   * compile-time error. If `T` is convertible to `std::string`, e.g. `const
   * char*`, the behaviour of this function is as if `T` was `std::string`.
   *
   * @param value the value that will be compared with the stored value.
   *
   * @return `true` if the stored value is equal to the supplied value; `false`
   * otherwise.
   *
   * @since 0.2.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto is(const T& value) const -> bool
  {
    if constexpr (std::is_convertible_v<T, std::string>) {
      if (is<std::string>()) {
        return get<std::string>() == value;
      }
    } else {
      if (is<T>()) {
        return get<T>() == value;
      }
    }
    return false;
  }

  /**
   * @brief Returns the name associated with the property.
   *
   * @return the name associated with the property.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return m_name;
  }

  /**
   * @brief Returns the type associated with the property.
   *
   * @return the type associated with the property.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return m_type;
  }

 private:
  type m_type{type::string};
  std::string m_name;
  std::variant<std::string, file, object_ref, color, int, float, bool> m_value;
};

NLOHMANN_JSON_SERIALIZE_ENUM(property::type,
                             {{property::type::string, "string"},
                              {property::type::integer, "int"},
                              {property::type::floating, "float"},
                              {property::type::boolean, "bool"},
                              {property::type::color, "color"},
                              {property::type::object, "object"},
                              {property::type::file, "file"}})

}  // namespace step

#endif  // STEP_PROPERTY_HEADER

// #include "step_api.hpp"

// #include "step_exception.hpp"

// #include "types.hpp"

// #include "utils.hpp"

// #include "valid_property.hpp"


namespace step {

/**
 * @class properties
 *
 * @brief Represents a collection of `property` instances.
 *
 * @see property
 *
 * @since 0.1.0
 */
class properties final
{
 public:
  explicit properties(const json& json)
  {
    for (const auto& [key, value] : json.items()) {
      const property property{value};
      m_properties.emplace(property.name(), value);
    }
  }

  /**
   * @brief Iterates over all of the properties store in this instance.
   *
   * @tparam Lambda the type of the lambda object.
   *
   * @param lambda the lambda that takes one argument, `std::pair<std::string,
   * Property>`, either by value or const reference.
   *
   * @since 0.1.0
   */
  template <typename Lambda>
  void each(Lambda&& lambda) const
  {
    std::for_each(m_properties.cbegin(), m_properties.cend(), lambda);
  }

  /**
   * @brief Indicates whether or not there is a property associated with the
   * specified name.
   *
   * @param name the name of the property to look for.
   *
   * @return `true` if there is a property associated with the specified name;
   * `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto has(std::string_view name) const -> bool
  {
    return m_properties.find(name) != m_properties.end();
  }

  /**
   * @brief Returns the property associated with the specified name.
   *
   * @note This method will throw an exception if the desired property doesn't
   * exist.
   *
   * @param name the name of the desired property.
   *
   * @return the property associated with the specified name.
   *
   * @throws `step_exception` if the desired property doesn't exist.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get(std::string_view name) const -> const property&
  {
    if (const auto it = m_properties.find(name); it != m_properties.end()) {
      return it->second;
    } else {
      throw step_exception{"properties > Couldn't find property!"};
    }
  }

  /**
   * @brief Indicates whether or not the specified property is equal to the
   * supplied value.
   *
   * @details This method does not throw any exceptions by itself and is the
   * preferred way to check the value of a property. The returned value is
   * always `false` if the property doesn't exist or if the property has another
   * type.
   *
   * @details A compile-time error will be raised if the type of the
   * supplied value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type of the value that will be compared to the value of
   * the specified property. An unsupported type will cause a compile-time
   * error.
   *
   * @param name the name of the property to check the value of.
   * @param value the value that will be compared with the value of the
   * specified property.
   *
   * @return `true` if the specified property had a value and it turned out to
   * be equal to the supplied value; `false` otherwise.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto is(std::string_view name, const T& value) const -> bool
  {
    if (!has(name)) {
      return false;
    }
    const auto& property = get(name);
    return property.is(value);
  }

  /**
   * @brief Returns the amount of `property` instances handled by this instance.
   *
   * @return the amount of properties handled by this instance.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto amount() const noexcept -> int
  {
    return static_cast<int>(m_properties.size());
  }

  /**
   * @brief Indicates whether or not there are any `property` instances handled
   * by this instance.
   *
   * @return `true` if there are properties handled by this instance; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto empty() const noexcept -> bool
  {
    return m_properties.empty();
  }

 private:
  std::map<std::string, property, std::less<>> m_properties;
};

}  // namespace step

#endif  // STEP_PROPERTIES_HEADER

// #include "step_api.hpp"

// #include "text.hpp"
#ifndef STEP_TEXT_HEADER
#define STEP_TEXT_HEADER

#include <string>

// #include "color.hpp"

// #include "step_api.hpp"

// #include "types.hpp"

// #include "utils.hpp"


namespace step {

/**
 * @class text
 *
 * @brief Represents objects that represent a piece of text.
 *
 * @since 0.1.0
 *
 * @headerfile step_text.hpp
 */
class text final
{
 public:
  /**
   * @enum halign
   *
   * @brief Provides values that represents the different possible horizontal
   * alignment modes for text.
   *
   * @since 0.1.0
   *
   * @headerfile step_text.hpp
   */
  enum class halign
  {
    center,
    right,
    left,
    justify
  };

  /**
   * @enum valign
   *
   * @brief Provides values that represents the different possible vertical
   * alignment modes for text.
   *
   * @since 0.1.0
   *
   * @headerfile step_text.hpp
   */
  enum class valign
  {
    center,
    bottom,
    top
  };

  explicit text(const json& json)
  {
    if (!json.count("text")) {
      throw step_exception{"Text > Missing \"text\" attribute!"};
    }

    m_text = json.at("text").get<std::string>();
    detail::safe_bind(json, "fontfamily", m_fontFamily);

    if (const auto it = json.find("color"); it != json.end()) {
      m_color = color{it->get<std::string>()};
    }

    detail::safe_bind(json, "halign", m_halign);
    detail::safe_bind(json, "valign", m_valign);
    detail::safe_bind(json, "pixelsize", m_pixelSize);
    detail::safe_bind(json, "bold", m_bold);
    detail::safe_bind(json, "italic", m_italic);
    detail::safe_bind(json, "kerning", m_kerning);
    detail::safe_bind(json, "strikeout", m_strikeout);
    detail::safe_bind(json, "underline", m_underline);
    detail::safe_bind(json, "wrap", m_wrap);
  }

  /**
   * @brief Returns the text associated with the instance.
   *
   * @note This property has no default value since it is a required attribute.
   *
   * @return the text associated with the instance.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_text() const -> const std::string&
  {
    return m_text;
  }

  /**
   * @brief Returns the name of the font family associated with the text.
   *
   * @note The default value of this property is `"sans-serif"`.
   *
   * @return the name of the font family associated with the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto font_family() const -> const std::string&
  {
    return m_fontFamily;
  }

  /**
   * @brief Returns the color associated with the text.
   *
   * @note The default value of this property is `#000000`.
   *
   * @return the color associated with the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_color() const noexcept -> color
  {
    return m_color;
  }

  /**
   * @brief Returns the horizontal alignment of the text.
   *
   * @note The default value of this property is `Left`
   *
   * @return the horizontal alignment of the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto horizontal_alignment() const noexcept -> halign
  {
    return m_halign;
  }

  /**
   * @brief Returns the vertical alignment of the text.
   *
   * @note The default value of this property is `Top`.
   *
   * @return the vertical alignment of the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto vertical_alignment() const noexcept -> valign
  {
    return m_valign;
  }

  /**
   * @brief Returns the pixel size of the associated font that the text uses.
   *
   * @note The default value of this property is `16`.
   *
   * @return the pixel size of the associated font.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto pixel_size() const noexcept -> int
  {
    return m_pixelSize;
  }

  /**
   * @brief Indicates whether or not the text is bold.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is bold; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto bold() const noexcept -> bool
  {
    return m_bold;
  }

  /**
   * @brief Indicates whether or not the text is italic.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is italic; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto italic() const noexcept -> bool
  {
    return m_italic;
  }

  /**
   * @brief Indicates whether or not the text uses kerning.
   *
   * @note The default value of this property is `true`.
   *
   * @return `true` if the text used kerning; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto kerning() const noexcept -> bool
  {
    return m_kerning;
  }

  /**
   * @brief Indicates whether or not the text is strikethrough.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is strikethrough; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto strikeout() const noexcept -> bool
  {
    return m_strikeout;
  }

  /**
   * @brief Indicates whether or not the text is underlined.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is underlined; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto underline() const noexcept -> bool
  {
    return m_underline;
  }

  /**
   * @brief Indicates whether or not the text is wrapped within the object
   * bounds.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is wrapped within the object bounds; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto wrap() const noexcept -> bool
  {
    return m_wrap;
  }

 private:
  std::string m_text;
  std::string m_fontFamily{"sans-serif"};
  color m_color;
  halign m_halign{halign::left};
  valign m_valign{valign::top};
  int m_pixelSize{16};
  bool m_bold{false};
  bool m_italic{false};
  bool m_kerning{true};
  bool m_strikeout{false};
  bool m_underline{false};
  bool m_wrap{false};
};

NLOHMANN_JSON_SERIALIZE_ENUM(text::halign,
                             {{text::halign::center, "center"},
                              {text::halign::right, "right"},
                              {text::halign::left, "left"},
                              {text::halign::justify, "justify"}})

NLOHMANN_JSON_SERIALIZE_ENUM(text::valign,
                             {{text::valign::center, "center"},
                              {text::valign::top, "top"},
                              {text::valign::bottom, "bottom"}})
}  // namespace step

#endif  // STEP_TEXT_HEADER

// #include "types.hpp"


namespace step {

/**
 * @struct polygon
 *
 * @brief A simple data container for polygon objects.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
struct polygon final
{
  std::vector<point> points;
};

/**
 * @struct polyline
 *
 * @brief A simple data container for polyline objects.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
struct polyline final
{
  std::vector<point> points;
};

/**
 * @struct template_object
 *
 * @brief A simple data container for template objects.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
struct template_object final
{
  std::string templateFile;
  // TODO std::shared_ptr<Tileset>
  // TODO std::shared_ptr<Object>
};

/**
 * @class object
 *
 * @brief Represents different kinds of objects in tile maps, such as polygons
 * or text.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
class object final
{
 private:
  template <typename T>
  static constexpr auto valid_object_type() noexcept -> bool;

 public:
  /**
   * @brief Creates an tiled object from a JSON object.
   *
   * @param json the JSON object that represents the tiled object.
   *
   * @since 0.1.0
   */
  explicit object(const json& json)
      : m_id{json.at("id").get<int>()}
      , m_x{json.at("x").get<double>()}
      , m_y{json.at("y").get<double>()}
      , m_width{json.at("width").get<double>()}
      , m_height{json.at("height").get<double>()}
      , m_rotation{json.at("rotation").get<double>()}
      , m_name{json.at("name").get<std::string>()}
      , m_type{json.at("type").get<std::string>()}
      , m_isEllipse{detail::safe_get<bool>(json, "ellipse", false)}
      , m_isPoint{detail::safe_get<bool>(json, "point", false)}
      , m_visible{json.at("visible").get<bool>()}
  {
    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties.emplace(it.value());
    }

    if (const auto gidIt = json.find("gid"); gidIt != json.end()) {
      m_specificData.emplace<global_id>(gidIt->get<unsigned>());

    } else if (const auto textIt = json.find("text"); textIt != json.end()) {
      m_specificData.emplace<text>(*textIt);

    } else if (const auto polyIt = json.find("polygon"); polyIt != json.end()) {
      auto& poly = m_specificData.emplace<polygon>();

      for (const auto& [key, value] : polyIt->items()) {
        poly.points.emplace_back(point{value});
      }

    } else if (const auto lineIt = json.find("polyline");
               lineIt != json.end()) {
      auto& line = m_specificData.emplace<polyline>();

      for (const auto& [key, value] : lineIt->items()) {
        line.points.emplace_back(point{value});
      }

    } else if (json.contains("template")) {
      auto& templ = m_specificData.emplace<template_object>();
      json.at("template").get_to(templ.templateFile);
    }
  }

  /**
   * @brief Returns the incremental ID associated with the object.
   *
   * @return the incremental ID associated with the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto id() const noexcept -> int
  {
    return m_id;
  }

  /**
   * @brief Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> double
  {
    return m_x;
  }

  /**
   * @brief Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> double
  {
    return m_y;
  }

  /**
   * @brief Returns the width of the object.
   *
   * @return the width of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> double
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the object.
   *
   * @return the height of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> double
  {
    return m_height;
  }

  /**
   * @brief Returns the amount of clockwise rotation of the object.
   *
   * @return the clockwise rotation of the object, in degrees.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto rotation() const noexcept -> double
  {
    return m_rotation;
  }

  /**
   * @brief Returns the name of the object.
   *
   * @return the name of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the type associated with the object.
   *
   * @return the type associated with the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto type() const -> std::string_view
  {
    return m_type;
  }

  /**
   * @brief Returns the properties associated with the object.
   *
   * @return the properties associated with the object; `nullptr` if there are
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const -> const properties*
  {
    return m_properties ? m_properties.operator->() : nullptr;
  }

  /**
   * @brief Indicates whether or not the object is visible.
   *
   * @return `true` if the object is visible; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto visible() const noexcept -> bool
  {
    return m_visible;
  }

  /**
   * Indicates whether or not the object represents an ellipse.
   *
   * @return `true` if the object represents an ellipse; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto is_ellipse() const noexcept -> bool
  {
    return m_isEllipse;
  }

  /**
   * @brief Indicates whether or not the object represents a point.
   *
   * @return `true` if the object represents a point; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto is_point() const noexcept -> bool
  {
    return m_isPoint;
  }

  /**
   * @brief Returns a reference to the internal object type-specific data.
   *
   * @note This function throws if the stored data isn't actually of the
   * specified type.
   *
   * @tparam T the type of the data to obtain, i.e. `polygon`, `polyline`,
   * `template_object`, `text` or `global_id`.
   *
   * @return a reference to the internal data.
   *
   * @since 0.2.0
   */
  template <typename T, typename = std::enable_if_t<valid_object_type<T>()>>
  [[nodiscard]] auto as() const -> const T&
  {
    return std::get<T>(m_specificData);
  }

  /**
   * @brief Returns a pointer to the internal object type-specific data.
   *
   * @note Unlike `get`, this function doesn't throw if the types mismatch,
   * instead `nullptr` is returned.
   *
   * @tparam T the type of the data to obtain, i.e. `polygon`, `polyline`,
   * `template_object`, `text` or `global_id`.
   *
   * @return a pointer to the internal data; `nullptr` if the types mismatch.
   *
   * @since 0.2.0
   */
  template <typename T, typename = std::enable_if_t<valid_object_type<T>()>>
  [[nodiscard]] auto try_as() const noexcept -> const T*
  {
    return std::get_if<T>(&m_specificData);
  }

  /**
   * @brief Indicates whether or not the stored data is of the specified type.
   *
   * @tparam T the type to look for, i.e. `polygon`, `polyline`,
   * `template_object`, `text` or `global_id`.
   *
   * @return `true` if the stored data is of the specified type; `false`
   * otherwise.
   *
   * @since 0.2.0
   */
  template <typename T, typename = std::enable_if_t<valid_object_type<T>()>>
  [[nodiscard]] auto has() const noexcept -> bool
  {
    return std::holds_alternative<T>(m_specificData);
  }

 private:
  using data = std::variant<std::monostate,
                            polygon,
                            polyline,
                            text,
                            template_object,
                            global_id>;
  int m_id{0};
  double m_x{0};
  double m_y{0};
  double m_width{0};
  double m_height{0};
  double m_rotation{0};
  std::string m_name;
  std::string m_type;
  std::optional<properties> m_properties;
  data m_specificData;
  bool m_isEllipse{false};
  bool m_isPoint{false};
  bool m_visible{true};

  // TODO improve template object support
};

template <typename T>
constexpr auto object::valid_object_type() noexcept -> bool
{
  return std::is_same_v<T, polygon> || std::is_same_v<T, polyline> ||
         std::is_same_v<T, text> || std::is_same_v<T, template_object> ||
         std::is_same_v<T, global_id>;
}

}  // namespace step

#endif  // STEP_OBJECT_HEADER

// #include "step_api.hpp"

// #include "types.hpp"


namespace step {

/**
 * @class object_group
 *
 * @brief Represents the API for layers that represent "object groups", that
 * hold data about various objects in a tile map.
 *
 * @todo begin, end, remove objects-getter
 *
 * @since 0.1.0
 *
 * @headerfile step_object_group.hpp
 */
class object_group final
{
 public:
  /**
   * @enum object_group::draw_order
   *
   * @brief Provides hints for how rendering should be performed of layers.
   *
   * @since 0.1.0
   */
  enum class draw_order
  {
    top_down,
    index
  };

  explicit object_group(const json& json) : m_drawOrder{json.at("draworder")}
  {
    m_objects.reserve(json.size());
    for (const auto& [key, value] : json.at("objects").items()) {
      m_objects.emplace_back(value);
    }
  }

  /**
   * @brief Returns the draw order used by the object group.
   *
   * @details The default value of this property is `top_down`.
   *
   * @return the draw order used by the object group.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_draw_order() const noexcept -> draw_order
  {
    return m_drawOrder;
  }

  /**
   * @brief Returns the objects contained in the object group.
   *
   * @return the objects contained in the object group.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto objects() const -> const std::vector<object>&
  {
    return m_objects;
  }

 private:
  draw_order m_drawOrder{draw_order::top_down};
  std::vector<object> m_objects;
};

NLOHMANN_JSON_SERIALIZE_ENUM(object_group::draw_order,
                             {{object_group::draw_order::index, "index"},
                              {object_group::draw_order::top_down, "topdown"}})

}  // namespace step

#endif  // STEP_OBJECT_GROUP_HEADER

// #include "properties.hpp"

// #include "step_api.hpp"

// #include "tile_layer.hpp"
#ifndef STEP_TILE_LAYER_HEADER
#define STEP_TILE_LAYER_HEADER

#include <memory>

// #include "chunk.hpp"

// #include "data.hpp"

// #include "step_api.hpp"

// #include "types.hpp"

// #include "utils.hpp"


namespace step {

/**
 * @class tile_layer
 *
 * @brief Represents the API for layers that represent "tile layers", that
 * mainly hold tile data.
 *
 * @since 0.1.0
 *
 * @headerfile step_tile_layer.hpp
 */
class tile_layer final
{
 public:
  /**
   * @enum tile_layer::compression
   *
   * @brief Provides values for the different kinds of compression used by
   * layers.
   *
   * @since 0.1.0
   */
  enum class compression
  {
    zlib,
    gzip,
    none
  };

  /**
   * @enum tile_layer::encoding
   *
   * @brief Provides identifiers for the different encodings used by layers.
   *
   * @since 0.1.0
   */
  enum class encoding
  {
    csv,
    base64
  };

  explicit tile_layer(const json& json)
  {
    detail::safe_bind(json, "compression", m_compression);
    detail::safe_bind(json, "encoding", m_encoding);

    if (json.contains("chunks")) {
      m_chunks = detail::fill<std::vector<chunk>>(json, "chunks");
    }

    if (json.contains("data")) {
      m_data = std::make_unique<detail::data>(json.at("data"));
    }
  }

  /**
   * @brief Returns the encoding used by the tile layer.
   *
   * @details The default value of this property is `csv`.
   *
   * @return the encoding used by the tile layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_encoding() const noexcept -> encoding
  {
    return m_encoding;
  }

  /**
   * @brief Returns the compression used by the tile layer.
   *
   * @details The default value of this property is `none`.
   *
   * @return the compression used by the tile layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_compression() const noexcept -> compression
  {
    return m_compression;
  }

  /**
   * @brief Returns a pointer to the tile data associated with the tile layer.
   *
   * @details This property is optional.
   *
   * @warning Do not claim ownership of the returned pointer.
   *
   * @return the tile data associated with the tile layer; null if there is
   * no such data.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto data() const -> const detail::data*
  {
    return m_data.get();
  }

  /**
   * @brief Returns the chunks associated with the tile layer.
   *
   * @return the chunks associated with the tile layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto chunks() const noexcept -> const std::vector<chunk>&
  {
    return m_chunks;
  }

 private:
  encoding m_encoding{encoding::csv};
  compression m_compression{compression::none};
  std::unique_ptr<detail::data> m_data;
  std::vector<chunk> m_chunks;
};

NLOHMANN_JSON_SERIALIZE_ENUM(tile_layer::compression,
                             {{tile_layer::compression::none, ""},
                              {tile_layer::compression::gzip, "gzip"},
                              {tile_layer::compression::zlib, "zlib"}})

NLOHMANN_JSON_SERIALIZE_ENUM(tile_layer::encoding,
                             {{tile_layer::encoding::csv, "csv"},
                              {tile_layer::encoding::base64, "base64"}})

}  // namespace step

#endif  // STEP_TILE_LAYER_HEADER

// #include "types.hpp"

// #include "utils.hpp"


namespace step {

class layer;

/**
 * @class group
 *
 * @brief Represents the API for layers that represent "groups", that
 * in turn contain zero or more layers.
 *
 * @since 0.1.0
 *
 * @headerfile step_group.hpp
 */
class group final
{
 public:
  friend void from_json(const json&, group&);

  /**
   * Iterates over all of the layers store in this group.
   *
   * @tparam Lambda the type of the lambda object.
   * @param lambda the lambda that takes one argument, <code>const
   * Layer&</code>.
   * @since 0.1.0
   */
  template <typename Lambda>
  void each(Lambda&& lambda) const
  {
    for (const auto& layer : m_layers) {
      lambda(*layer);
    }
  }

  /**
   * @brief Returns the layer at the specified index.
   *
   * @note This function throws if the index is out-of-bounds.
   *
   * @param index the index of the desired layer.
   *
   * @return the layer at the specified index.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto at(std::size_t index) const -> const layer&
  {
    return *m_layers.at(index);
  }

  /**
   * @brief Returns the amount of layers that are in the group.
   *
   * @return the amount of layers that are in the group.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto num_layers() const noexcept -> int
  {
    return static_cast<int>(m_layers.size());
  }

 private:
  std::vector<std::unique_ptr<layer>> m_layers;
};

inline void from_json(const json& json, group& group)
{
  for (const auto& [key, value] : json.at("layers").items()) {
    group.m_layers.push_back(std::make_unique<layer>(value));
  }
}

/**
 * @class layer
 *
 * @brief Represents the tile layers that reside in the tile maps.
 *
 * @since 0.1.0
 *
 * @headerfile step_layer.hpp
 */
class layer final
{
 public:
  /**
   * @enum layer::type
   *
   * @brief Provides identifiers for all of the different possible layer types.
   *
   * @since 0.1.0
   */
  enum class type
  {
    tile_layer,
    object_group,
    image_layer,
    group
  };

  explicit layer(const json& json)
  {
    init_common(json);
    switch (get_type()) {
      case layer::type::tile_layer: {
        m_layerData.emplace<tile_layer>(json);
        break;
      }
      case layer::type::object_group: {
        m_layerData.emplace<object_group>(json);
        break;
      }
      case layer::type::image_layer: {
        m_layerData.emplace<image_layer>(json.get<image_layer>());
        break;
      }
      case layer::type::group: {
        m_layerData.emplace<group>(json.get<group>());
        break;
      }
      default: {
        const auto id = std::to_string(static_cast<int>(type()));
        throw step_exception{"Layer > Unknown layer type: " + id};
      }
    }
  }

  /**
   * @brief Returns specific information associated with the layer, depending
   * on the type of the layer.
   *
   * @note This function throws if the layer doesn't contain the specified
   * type.
   *
   * @tparam T the type of the internal layer information.
   *
   * @return the layer information.
   *
   * @throws step_exception if there is a type mismatch.
   *
   * @since 0.1.0
   */
  template <typename T>
  [[nodiscard]] auto as() const -> const T&
  {
    return std::get<T>(m_layerData);
  }

  /**
   * @brief Returns specific information associated with the layer.
   *
   * @tparam T the type of the internal layer information.
   *
   * @return the layer information; null if there was a type mismatch.
   *
   * @since 0.2.0
   */
  template <typename T>
  [[nodiscard]] auto try_as() const noexcept -> const T*
  {
    return std::get_if<T>(&m_layerData);
  }

  /**
   * @brief Indicates whether or not the layer is of the specified layer type.
   *
   * @tparam T the layer type to check for.
   *
   * @return `true` if the layer matches the supplied layer type; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  template <typename T>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    return std::holds_alternative<T>(m_layerData);
  }

  /**
   * @brief Returns the type of the layer.
   *
   * @return the type of the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return m_type;
  }

  /**
   * @brief Returns the unique integer ID associated with the layer.
   *
   * @return the unique integer ID associated with the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto id() const noexcept -> int
  {
    return m_id;
  }

  /**
   * @brief Returns the amount of columns in the layer.
   *
   * @return the amount of columns in the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the amount of rows in the layer.
   *
   * @return the amount of rows in the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

  /**
   * @brief Returns the properties associated with the layer.
   *
   * @return the properties associated with the layer; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

  /**
   * @brief Returns the x-coordinate of where the layer content begins.
   *
   * @details This is used by infinite maps.
   *
   * @return the x-coordinate of where the layer content begins.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto start_x() const noexcept -> int
  {
    return m_startX;
  }

  /**
   * @brief Returns the y-coordinate of where the layer content begins.
   *
   * @details This is used by infinite maps.
   *
   * @return the y-coordinate of where the layer content begins.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto start_y() const noexcept -> int
  {
    return m_startY;
  }

  /**
   * @brief Returns the horizontal offset of the layer.
   *
   * @details The default value of this property is 0.
   *
   * @return the horizontal offset of the layer, in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto offset_x() const noexcept -> double
  {
    return m_offsetX;
  }

  /**
   * @brief Returns the vertical offset of the layer.
   *
   * @details The default value of this property is 0.
   *
   * @return the vertical offset of the layer, in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto offset_y() const noexcept -> double
  {
    return m_offsetY;
  }

  /**
   * @brief Returns the opacity of the layer.
   *
   * @return the opacity of the layer, in the range [0, 1].
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto opacity() const noexcept -> double
  {
    return m_opacity;
  }

  /**
   * @brief Indicates whether or not the layer is visible.
   *
   * @return `true` if the layer is visible; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto visible() const noexcept -> bool
  {
    return m_visible;
  }

  /**
   * @brief Returns the name associated with the layer.
   *
   * @return the name associated with the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return m_name;
  }

 private:
  type m_type{};
  int m_id{0};
  std::variant<std::monostate, tile_layer, image_layer, object_group, group>
      m_layerData;
  std::unique_ptr<properties> m_properties;
  int m_width{0};
  int m_height{0};
  int m_startX{0};
  int m_startY{0};
  double m_offsetX{0};
  double m_offsetY{0};
  double m_opacity{1};
  std::string m_name;
  bool m_visible{true};

  void init_common(const json& json)
  {
    json.at("type").get_to(m_type);

    detail::safe_bind(json, "name", m_name);
    detail::safe_bind(json, "opacity", m_opacity);
    detail::safe_bind(json, "visible", m_visible);
    detail::safe_bind(json, "id", m_id);
    detail::safe_bind(json, "width", m_width);
    detail::safe_bind(json, "height", m_height);
    detail::safe_bind(json, "startx", m_startX);
    detail::safe_bind(json, "starty", m_startY);
    detail::safe_bind(json, "offsetx", m_offsetX);
    detail::safe_bind(json, "offsety", m_offsetY);

    m_properties = detail::safe_bind_unique<properties>(json, "properties");
  }
};

NLOHMANN_JSON_SERIALIZE_ENUM(layer::type,
                             {{layer::type::tile_layer, "tilelayer"},
                              {layer::type::image_layer, "imagelayer"},
                              {layer::type::object_group, "objectgroup"},
                              {layer::type::group, "group"}})

}  // namespace step

#endif  // STEP_LAYER_HEADER

// #include "map.hpp"
#ifndef STEP_MAP_HEADER
#define STEP_MAP_HEADER

#include <memory>       // unique_ptr
#include <string>       // string
#include <string_view>  // string_view
#include <vector>       // vector

// #include "color.hpp"

// #include "layer.hpp"

// #include "properties.hpp"

// #include "step_api.hpp"

// #include "tileset.hpp"
#ifndef STEP_TILESET_HEADER
#define STEP_TILESET_HEADER

#include <memory>       // unique_ptr
#include <optional>     // optional
#include <string_view>  // string_view
#include <vector>       // vector

// #include "color.hpp"

// #include "grid.hpp"

// #include "properties.hpp"

// #include "step_api.hpp"

// #include "terrain.hpp"
#ifndef STEP_TERRAIN_HEADER
#define STEP_TERRAIN_HEADER

#include <memory>
#include <string>
#include <vector>

// #include "properties.hpp"

// #include "step_api.hpp"

// #include "utils.hpp"


namespace step {

/**
 * @class terrain
 *
 * @brief Represents optional terrains in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_terrain.hpp
 */
class terrain final
{
 public:
  explicit terrain(const json& json)
      : m_tile{json.at("tile").get<int>()}
      , m_name{json.at("name").get<std::string>()}
  {
    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties = std::make_unique<properties>(*it);
    }
  }

  /**
   * @brief Returns the local GID of the tile associated with the terrain.
   *
   * @return the local GID of the tile associated with the terrain.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile() const noexcept -> local_id
  {
    return m_tile;
  }

  /**
   * @brief Returns the name associated with the terrain.
   *
   * @return the name associated with the terrain.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return m_name;
  }

  /**
   * @brief Returns the properties associated with the terrain.
   *
   * @details This property is optional.
   *
   * @return the properties associated with the terrain; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

 private:
  local_id m_tile{0};
  std::string m_name;
  std::unique_ptr<properties> m_properties;
};

}  // namespace step

#endif  // STEP_TERRAIN_HEADER

// #include "tile.hpp"
#ifndef STEP_TILE_HEADER
#define STEP_TILE_HEADER

#include <array>     // array
#include <optional>  // optional
#include <string>    // string

// #include "animation.hpp"

// #include "layer.hpp"

// #include "properties.hpp"

// #include "step_api.hpp"

// #include "step_fwd.hpp"
#ifndef STEP_FWD_HEADER
#define STEP_FWD_HEADER

namespace step {

class layer;

class properties;

class tile;

}  // namespace step

#endif  // STEP_FWD_HEADER

// #include "types.hpp"

// #include "utils.hpp"


namespace step {

/**
 * @class tile
 *
 * @brief Provides information about a tile in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tile.hpp
 */
class tile final
{
 public:
  /**
   * @enum terrain_pos
   *
   * @brief Provides values that represent the different positions that could be
   * inhabited by terrain IDs, in relation to the tile.
   *
   * @since 0.1.0
   *
   * @headerfile step_tile.hpp
   */
  enum class terrain_pos
  {
    top_left = 0,
    top_right = 1,
    bottom_left = 2,
    bottom_right = 3
  };

  explicit tile(const json& json) : m_id{json.at("id").get<int>()}
  {
    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties.emplace(*it);
    }

    if (const auto it = json.find("terrain"); it != json.end()) {
      m_terrain.emplace();
      for (const auto& [key, value] : it->items()) {
        m_terrain->at(detail::convert<std::size_t>(key)) = value.get<int>();
      }
    }

    if (const auto it = json.find("objectgroup"); it != json.end()) {
      m_objectGroup.emplace(*it);
    }

    detail::emplace_opt(json, "animation", m_animation);

    detail::bind_opt(json, "type", m_type);
    detail::bind_opt(json, "image", m_image);
    detail::bind_opt(json, "imagewidth", m_imageWidth);
    detail::bind_opt(json, "imageheight", m_imageHeight);
    detail::bind_opt(json, "probability", m_probability);
  }

  /**
   * @brief Returns the local ID associated with the tile.
   *
   * @return the local ID associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto id() const noexcept -> local_id
  {
    return m_id;
  }

  /**
   * @brief Returns the animation associated with the tile.
   *
   * @return the animation associated with the tile; `std::nullopt` if there is
   * no animation associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_animation() const noexcept
      -> const std::optional<animation>&
  {
    return m_animation;
  }

  /**
   * @brief Returns the properties associated with the tile.
   *
   * @note Don't take ownership of the returned pointer.
   *
   * @return the properties associated with the tile; `nullptr` if there are
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const -> const properties*
  {
    return m_properties ? m_properties.operator->() : nullptr;
  }

  /**
   * @brief Returns the object group layer associated with the tile.
   *
   * @note Don't take ownership of the returned pointer.
   *
   * @return a shared pointer to the object group associated with the tile;
   * `nullptr` if there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto object_group() const noexcept -> const layer*
  {
    return m_objectGroup ? m_objectGroup.operator->() : nullptr;
  }

  /**
   * @brief Returns the type of the tile.
   *
   * @return the type of the tile; `std::nullopt` if there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto type() const -> const std::optional<std::string>&
  {
    return m_type;
  }

  /**
   * @brief Returns the image associated with the tile.
   *
   * @return the image associated with the tile; `std::nullopt` if there is
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image() const -> const std::optional<std::string>&
  {
    return m_image;
  }

  /**
   * @brief Returns the width of the image associated with the tile.
   *
   * @return the width of the image associated with the tile; `std::nullopt` if
   * there is no image associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_width() const noexcept -> std::optional<int>
  {
    return m_imageWidth;
  }

  /**
   * @brief Returns the height of the image associated with the tile.
   *
   * @return the height of the image associated with the tile; `std::nullopt` if
   * there is no image associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_height() const noexcept -> std::optional<int>
  {
    return m_imageHeight;
  }

  /**
   * @brief Returns the probability associated with the tile.
   *
   * @return the probability associated with the tile; `std::nullopt` if there
   * is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto probability() const noexcept -> std::optional<double>
  {
    return m_probability;
  }

  /**
   * @brief Returns the ID of the terrain at the specified position, in relation
   * to the tile.
   *
   * @param position the position that will be checked.
   *
   * @return the ID of the terrain at the specified position; `std::nullopt`
   * if there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto terrain_at(terrain_pos position) const noexcept
      -> std::optional<int>
  {
    if (m_terrain) {
      return m_terrain->at(static_cast<std::size_t>(position));
    } else {
      return std::nullopt;
    }
  }

 private:
  local_id m_id{0};
  std::optional<properties> m_properties;
  std::optional<layer> m_objectGroup;
  std::optional<animation> m_animation;
  std::optional<std::array<int, 4>> m_terrain;
  std::optional<std::string> m_type;
  std::optional<std::string> m_image;
  std::optional<int> m_imageWidth;
  std::optional<int> m_imageHeight;
  std::optional<double> m_probability;
};

}  // namespace step

#endif  // STEP_TILE_HEADER

// #include "tile_offset.hpp"
#ifndef STEP_TILE_OFFSET_HEADER
#define STEP_TILE_OFFSET_HEADER

// #include "step_api.hpp"

// #include "types.hpp"


namespace step {

/**
 * @class tile_offset
 *
 * @brief Provides offsets in pixels that are to be applied when rendering a
 * tile from a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tile_offset.hpp
 */
class tile_offset final
{
 public:
  explicit tile_offset(const json& json)
      : m_x{json.at("x").get<int>()}
      , m_y{json.at("y").get<int>()}
  {}

  /**
   * @brief Returns the offset in the x-axis associated with the tile offset
   * instance.
   *
   * @return the offset in the x-axis.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    return m_x;
  }

  /**
   * @brief Returns the offset in the y-axis associated with the tile offset
   * instance.
   *
   * @return the offset in the y-axis.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    return m_y;
  }

 private:
  int m_x;
  int m_y;
};

}  // namespace step

#endif  // STEP_TILE_OFFSET_HEADER

// #include "types.hpp"

// #include "wang_set.hpp"
#ifndef STEP_WANG_SET_HEADER
#define STEP_WANG_SET_HEADER

#include <string>
#include <string_view>
#include <vector>

// #include "properties.hpp"

// #include "step_api.hpp"

// #include "utils.hpp"

// #include "wang_color.hpp"
#ifndef STEP_WANG_COLOR_HEADER
#define STEP_WANG_COLOR_HEADER

#include <string>       // string
#include <string_view>  // string_view

// #include "color.hpp"

// #include "step_api.hpp"

// #include "types.hpp"

// #include "utils.hpp"


namespace step {

class wang_color final
{
 public:
  /**
   * @param json the JSON object that holds the data for a Wang color.
   * @since 0.1.0
   */
  explicit wang_color(const json& json)
      : m_name{json.at("name").get<std::string>()}
      , m_color{json.at("color").get<std::string>()}
      , m_tile{json.at("tile").get<int>()}
      , m_probability{json.at("probability").get<double>()}
  {}

  /**
   * @brief Returns the name associated with the Wang color.
   *
   * @return the name associated with the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the color associated with the Wang color.
   *
   * @return the color associated with the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_color() const noexcept -> const color&
  {
    return m_color;
  }

  /**
   * @brief Returns the local ID of the tile that represents the Wang color.
   *
   * @return the local ID of the tile that represents the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile() const noexcept -> local_id
  {
    return m_tile;
  }

  /**
   * @brief Returns the probability associated with the Wang color.
   *
   * @return the probability associated with the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto probability() const noexcept -> double
  {
    return m_probability;
  }

 private:
  std::string m_name;
  color m_color;
  local_id m_tile{0};
  double m_probability{};
};

}  // namespace step

#endif  // STEP_WANG_COLOR_HEADER

// #include "wang_tile.hpp"
#ifndef STEP_WANG_TILE_HEADER
#define STEP_WANG_TILE_HEADER

#include <array>

// #include "step_api.hpp"

// #include "types.hpp"

// #include "utils.hpp"


namespace step {

class WangTile final
{
 public:
  /**
   * @param json the JSON object that holds the data for a Wang tile.
   * @since 0.1.0
   */
  explicit WangTile(const json& json)
      : m_tileID{json.at("tileid").get<int>()}
      , m_wangColorIndices{json.at("wangid").get<std::array<int, 8>>()}
      , m_flippedDiagonally{json.at("dflip").get<bool>()}
      , m_flippedHorizontally{json.at("hflip").get<bool>()}
      , m_flippedVertically{json.at("vflip").get<bool>()}
  {}

  /**
   * Returns the local ID associated with the Wang tile.
   *
   * @return the local ID associated with the Wang tile.
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tileID;
  }

  /**
   * Returns the Wang color indices associated with the Wang tile.
   *
   * @return the Wang color indices associated with the Wang tile.
   * @since 0.1.0
   */
  [[nodiscard]] auto wang_color_indices() const -> const std::array<int, 8>&
  {
    return m_wangColorIndices;
  }

  /**
   * @brief Indicates whether or not the tile is flipped diagonally.
   *
   * @details The default value of this property is false.
   *
   * @return `true` if the tile is flipped diagonally; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto flipped_diagonally() const noexcept -> bool
  {
    return m_flippedDiagonally;
  }

  /**
   * @brief Indicates whether or not the tile is flipped horizontally.
   *
   * @details The default value of this property is false.
   *
   * @return `true` if the tile is flipped horizontally; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto flipped_horizontally() const noexcept -> bool
  {
    return m_flippedHorizontally;
  }

  /**
   * @brief Indicates whether or not the tile is flipped vertically.
   *
   * @details The default value of this property is false.
   *
   * @return `true` if the tile is flipped vertically; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto flipped_vertically() const noexcept -> bool
  {
    return m_flippedVertically;
  }

 private:
  local_id m_tileID{0};
  std::array<int, 8> m_wangColorIndices{};
  bool m_flippedDiagonally{false};
  bool m_flippedHorizontally{false};
  bool m_flippedVertically{false};
};

}  // namespace step

#endif  // STEP_WANG_TILE_HEADER


namespace step {

class wang_set final
{
  using colors = std::vector<wang_color>;
  using tiles = std::vector<WangTile>;

 public:
  /**
   * @param json the JSON object that holds the data for a Wang set.
   *
   * @since 0.1.0
   */
  explicit wang_set(const json& json)
      : m_tile{json.at("tile").get<int>()}
      , m_cornerColors{detail::fill<colors>(json, "cornercolors")}
      , m_edgeColors{detail::fill<colors>(json, "edgecolors")}
      , m_wangTiles{detail::fill<tiles>(json, "wangtiles")}
      , m_properties{json.at("properties")}
      , m_name{json.at("name").get<std::string>()}
  {}

  /**
   * @brief Returns all of the corner colors associated with the Wang set.
   *
   * @return all of the corner colors associated with the Wang set.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto corner_colors() const -> const colors&
  {
    return m_cornerColors;
  }

  /**
   * @brief Returns all of the edge colors associated with the Wang set.
   *
   * @return all of the edge colors associated with the Wang set.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto edge_colors() const -> const colors&
  {
    return m_edgeColors;
  }

  /**
   * @brief Returns all of the Wang tiles associated with the Wang set.
   *
   * @return all of the Wang tiles associated with the Wang set.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto wang_tiles() const -> const tiles&
  {
    return m_wangTiles;
  }

  /**
   * @brief Returns the properties associated with the Wang set.
   *
   * @return the properties associated with the Wang set.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const -> const properties&
  {
    return m_properties;
  }

  /**
   * @brief Returns the name associated with the Wang set.
   *
   * @return the name associated with the Wang set.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the local ID of the tile that represents the Wang set.
   *
   * @return the local ID of the tile that represents the Wang set.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tile;
  }

 private:
  local_id m_tile{0};
  std::vector<wang_color> m_cornerColors;
  std::vector<wang_color> m_edgeColors;
  std::vector<WangTile> m_wangTiles;
  properties m_properties;
  std::string m_name;
};

}  // namespace step

#endif  // STEP_WANG_SET_HEADER


namespace step {

class tileset;

/**
 * @class tileset
 *
 * @brief Represents a collection of tiles associated with an image.
 *
 * @details All tilesets have a global ID (GID) associated with them, that
 * starts at 1 for the first tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tileset.hpp
 */
class tileset final
{
 public:
  [[nodiscard]] static auto embedded(const json& json)
      -> std::unique_ptr<tileset>
  {
    return std::unique_ptr<tileset>{new tileset{json}};
  }

  [[nodiscard]] static auto external(std::string_view root,
                                     global_id id,
                                     std::string_view src)
      -> std::unique_ptr<tileset>
  {
    return std::unique_ptr<tileset>{new tileset{root, id, src}};
  }

  /**
   * @brief Returns the GID (Global ID) of the first tile in the tileset.
   *
   * @return the GID (Global ID) of the first tile in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto first_gid() const noexcept -> global_id
  {
    return m_firstGID;
  }

  /**
   * @brief Returns the maximum width of tiles in the tileset.
   *
   * @return the maximum width of tiles in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_width() const noexcept -> int
  {
    return m_tileWidth;
  }

  /**
   * @brief Returns the maximum height of tiles in the tileset.
   *
   * @return the maximum height of tiles in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_height() const noexcept -> int
  {
    return m_tileHeight;
  }

  /**
   * @brief Returns the number of tiles in the tileset.
   *
   * @return the number of tiles in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_count() const noexcept -> int
  {
    return m_tileCount;
  }

  /**
   * @brief Returns the number of columns in the tileset.
   *
   * @return the number of columns in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto columns() const noexcept -> int
  {
    return m_nColumns;
  }

  /**
   * @brief Returns the width of the source image in pixels.
   *
   * @return the width of the source image in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_width() const noexcept -> int
  {
    return m_imageWidth;
  }

  /**
   * @brief Returns the height of the source image in pixels.
   *
   * @return the height of the source image in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_height() const noexcept -> int
  {
    return m_imageHeight;
  }

  /**
   * @brief Returns the buffer amount between the image edge and the first tile,
   * in pixels.
   *
   * @return the buffer amount between the image edge and the first tile, in
   * pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto margin() const noexcept -> int
  {
    return m_margin;
  }

  /**
   * @brief Returns the amount of spacing between adjacent tiles in the tileset,
   * in pixels.
   *
   * @return the amount of spacing between adjacent tiles in the tileset, in
   * pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto spacing() const noexcept -> int
  {
    return m_spacing;
  }

  /**
   * @brief Returns the tiles associated with the tileset that have custom
   * properties.
   *
   * @details This property is optional.
   *
   * @return the tiles associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tiles() const -> const std::vector<tile>&
  {
    return m_tiles;
  }

  /**
   * @brief Returns all of the Wang sets that are associated with the tileset.
   *
   * @return the Wang sets associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto wang_sets() const -> const std::vector<wang_set>&
  {
    return m_wangSets;
  }

  /**
   * @brief Returns the properties associated with the tileset.
   *
   * @return the properties associated with the tileset; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

  /**
   * @brief Returns the terrains associated with the tileset.
   *
   * @details This property is optional.
   *
   * @return the terrains associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto terrains() const -> const std::vector<terrain>&
  {
    return m_terrains;
  }

  /**
   * @brief Returns the path to the external file that holds the actual tileset
   * data, if this tileset isn't embedded.
   *
   * @details This method will return the empty string if the tileset is
   * embedded.
   *
   * @return the path to the external file that holds the tileset data if the
   * the tileset is external; the empty string is returned if the tileset is
   * embedded.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto source() const -> std::string_view
  {
    return m_source;
  }

  /**
   * @brief Returns the path to the image associated with the tileset.
   *
   * @return the path to the image associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image() const -> std::string_view
  {
    return m_image;
  }

  /**
   * @brief Returns the name associated with the tileset.
   *
   * @return the name associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the background color of the tileset.
   *
   * @details This property is optional.
   *
   * @return the background color of the tileset; `std::nullopt` if there is
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto background_color() const noexcept
      -> const std::optional<color>&
  {
    return m_backgroundColor;
  }

  /**
   * @brief Returns the transparent color of the tileset. This property is
   * optional.
   *
   * @return the transparent color of the tileset; `std::nullopt`if there is
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto transparent_color() const noexcept
      -> const std::optional<color>&
  {
    return m_transparentColor;
  }

  /**
   * @brief Returns the grid associated with the tileset. This property is
   * optional.
   *
   * @return the grid associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_grid() const noexcept -> const std::optional<grid>&
  {
    return m_grid;
  }

  /**
   * @brief Returns the tile offset associated with the tileset.
   *
   * @details This property is optional.
   *
   * @return the tile offset associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_tile_offset() const noexcept
      -> const std::optional<tile_offset>&
  {
    return m_tileOffset;
  }

  /**
   * @brief Returns the Tiled version associated with the tileset.
   *
   * @return the Tiled version associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tiled_version() const -> std::string_view
  {
    return m_tiledVersion;
  }

  /**
   * Returns the JSON format version associated with the tileset.
   *
   * @return the JSON format version associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] auto json_version() const noexcept -> double
  {
    return m_jsonVersion;
  }

 private:
  global_id m_firstGID{1};
  int m_tileWidth{};
  int m_tileHeight{};
  int m_tileCount{};
  int m_nColumns{};
  int m_imageWidth{};
  int m_imageHeight{};
  int m_margin{};
  int m_spacing{};
  std::vector<tile> m_tiles;
  std::vector<terrain> m_terrains;
  std::vector<wang_set> m_wangSets;
  std::unique_ptr<properties> m_properties;
  std::string m_image;
  std::string m_source;
  std::string m_name;
  std::optional<color> m_backgroundColor;
  std::optional<color> m_transparentColor;
  std::optional<grid> m_grid;
  std::optional<tile_offset> m_tileOffset;
  std::string m_tiledVersion;
  double m_jsonVersion{};

  tileset(std::string_view root, global_id id, std::string_view src)
      : m_firstGID{id}
      , m_source{src.data()}
  {
    std::string fullPath{root.data()};
    fullPath += src.data();
    parse(detail::parse_json(fullPath));
  }

  explicit tileset(const json& json)
  {
    parse(json);
  }

  void parse(const json& json)
  {
    if (json.at("type").get<std::string>() != "tileset") {
      throw step_exception{R"(Tileset "type" must be "tileset"!)"};
    }

    json.at("tilewidth").get_to(m_tileWidth);
    json.at("tileheight").get_to(m_tileHeight);
    json.at("tilecount").get_to(m_tileCount);
    json.at("columns").get_to(m_nColumns);
    json.at("imagewidth").get_to(m_imageWidth);
    json.at("imageheight").get_to(m_imageHeight);
    json.at("margin").get_to(m_margin);
    json.at("spacing").get_to(m_spacing);
    json.at("image").get_to(m_image);
    json.at("name").get_to(m_name);

    if (const auto it = json.find("firstgid"); it != json.end()) {
      m_firstGID = global_id{it->get<unsigned>()};
    }

    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties = std::make_unique<properties>(*it);
    }

    detail::safe_bind(json, "tiledversion", m_tiledVersion);
    detail::safe_bind(json, "version", m_jsonVersion);
    detail::bind_opt(json, "grid", m_grid);
    detail::emplace_opt(json, "tileoffset", m_tileOffset);

    const auto fill_if_array = [&json](auto& container, std::string_view key) {
      const auto it = json.find(key);
      if (it != json.end() && it->is_array()) {
        container.reserve(it->size());
        for (const auto& [key, value] : it->items()) {
          container.emplace_back(value);
        }
      }
    };

    fill_if_array(m_tiles, "tiles");
    fill_if_array(m_terrains, "terrains");
    fill_if_array(m_wangSets, "wangsets");

    if (const auto it = json.find("backgroundcolor"); it != json.end()) {
      m_backgroundColor = color{it->get<std::string>()};
    }

    if (const auto it = json.find("transparentcolor"); it != json.end()) {
      m_transparentColor = color{it->get<std::string>()};
    }
  }
};

}  // namespace step

#endif  // STEP_TILESET_HEADER

// #include "types.hpp"


namespace step {

/**
 * @class map
 *
 * @brief Represents tile map files created in the Tiled editor.
 *
 * @since 0.1.0
 *
 * @headerfile step_map.hpp
 */
class map final
{
 public:
  enum class render_order
  {
    right_down,
    right_up,
    left_down,
    left_up
  };

  enum class orientation
  {
    orthogonal,
    isometric,
    staggered,
    hexagonal
  };

  enum class stagger_axis
  {
    x,
    y
  };

  enum class stagger_index
  {
    odd,
    even
  };

  explicit map(const fs::path& path)
  {
    auto parent = path.parent_path();
    parent += fs::path::preferred_separator;

    parse(parent.string(), detail::parse_json(path.string()));
  }

  /**
   * @param root the file path of the directory that contains the map.
   * @param file the name of the JSON map file, including the .json extension.
   *
   * @since 0.1.0
   */
  [[deprecated("Use the path version instead!")]] map(std::string_view root,
                                                      std::string_view file)
  {
    std::string map{root.data()};
    map += file;
    parse(root, detail::parse_json(map));
  }

  /**
   * @brief Returns the width of the map.
   *
   * @return the width of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the map.
   *
   * @return the height of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

  /**
   * @brief Returns the width of the tiles in the map.
   *
   * @return the width of the tiles in the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_width() const noexcept -> int
  {
    return m_tileWidth;
  }

  /**
   * @brief Returns the height of the tiles in the map.
   *
   * @return the height of the tiles in the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_height() const noexcept -> int
  {
    return m_tileHeight;
  }

  /**
   * @brief Returns the next layer ID, this is incremented every time an layer
   * is added to the map in the Tiled editor.
   *
   * @return the next layer ID.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto next_layer_id() const noexcept -> int
  {
    return m_nextLayerID;
  }

  /**
   * @brief Returns the next object ID, this is incremented every time an object
   * is placed in the map in the Tiled editor.
   *
   * @return the next object ID.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto next_object_id() const noexcept -> int
  {
    return m_nextObjectID;
  }

  /**
   * @brief Returns the tile layers associated with the map.
   *
   * @return the tile layers associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto layers() const -> const std::vector<layer>&
  {
    return m_layers;
  }

  /**
   * @brief Returns the tilesets associated with the map.
   *
   * @return the tilesets associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tilesets() const
      -> const std::vector<std::unique_ptr<tileset>>&
  {
    return m_tilesets;
  }

  /**
   * @brief Returns the properties associated with the map.
   *
   * @return the properties associated with the map; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

  /**
   * @brief Returns the orientation of the map.
   *
   * @return the orientation of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_orientation() const noexcept -> orientation
  {
    return m_orientation;
  }

  /**
   * @brief Returns the render-order associated with the map.
   *
   * @details The default value of this property is `right_down`.
   *
   * @note This property is only used by orthogonal maps.
   *
   * @return the render-order associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_render_order() const noexcept -> render_order
  {
    return m_renderOrder;
  }

  /**
   * @brief Returns the stagger axis associated with the map.
   *
   * @details This property is only for staggered and hexagonal maps.
   *
   * @return the stagger axis associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_stagger_axis() const noexcept -> stagger_axis
  {
    return m_staggerAxis;
  }

  /**
   * @brief Returns the stagger index associated with the map.
   *
   * @details This property is only for staggered and hexagonal maps.
   *
   * @return the stagger index associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_stagger_index() const noexcept -> stagger_index
  {
    return m_staggerIndex;
  }

  /**
   * @brief Indicates whether or not the map is infinite.
   *
   * @return true if the map is infinite; false otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto infinite() const noexcept -> bool
  {
    return m_infinite;
  }

  /**
   * @brief Returns the length of the side of a hex tile, in pixels.
   *
   * @details This property is only for hexagonal maps.
   *
   * @return the length of the side of a hex tile, in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto hex_side_length() const noexcept -> int
  {
    return m_hexSideLength;
  }

  /**
   * @brief Returns the background color associated with the map.
   *
   * @details This property is optional.
   *
   * @return the background color of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto background_color() const noexcept
      -> const std::optional<color>&
  {
    return m_backgroundColor;
  }

  /**
   * @brief Returns the JSON format version associated with the map.
   *
   * @return the JSON format version associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto json_version() const noexcept -> double
  {
    return m_jsonVersion;
  }

  /**
   * @brief Returns the Tiled version associated with the map.
   *
   * @return the Tiled version associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tiled_version() const -> std::string_view
  {
    return m_tiledVersion;
  }

 private:
  int m_width{0};
  int m_height{0};
  int m_tileWidth{0};
  int m_tileHeight{0};
  int m_nextLayerID{0};
  int m_nextObjectID{0};
  std::vector<layer> m_layers;
  std::vector<std::unique_ptr<tileset>> m_tilesets;
  std::unique_ptr<properties> m_properties;
  orientation m_orientation{orientation::orthogonal};
  render_order m_renderOrder{render_order::right_down};
  stagger_axis m_staggerAxis{stagger_axis::x};
  stagger_index m_staggerIndex{stagger_index::odd};
  int m_hexSideLength{0};
  std::optional<color> m_backgroundColor;
  std::string m_tiledVersion;
  double m_jsonVersion{0};
  bool m_infinite{false};

  void parse(std::string_view root, const json& json)
  {
    using namespace std::string_view_literals;
    if (const auto it = json.find("type");
        it == json.end() || it.key() == "map"sv) {
      throw step_exception{R"(Map "type" attribute must be "map"!)"};
    }

    json.at("width").get_to(m_width);
    json.at("height").get_to(m_height);
    json.at("tilewidth").get_to(m_tileWidth);
    json.at("tileheight").get_to(m_tileHeight);
    json.at("infinite").get_to(m_infinite);
    json.at("nextlayerid").get_to(m_nextLayerID);
    json.at("nextobjectid").get_to(m_nextObjectID);
    json.at("orientation").get_to(m_orientation);
    json.at("version").get_to(m_jsonVersion);
    json.at("tiledversion").get_to(m_tiledVersion);

    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties = std::make_unique<properties>(*it);
    }

    detail::safe_bind(json, "renderorder", m_renderOrder);
    detail::safe_bind(json, "staggeraxis", m_staggerAxis);
    detail::safe_bind(json, "staggerindex", m_staggerIndex);
    detail::safe_bind(json, "hexsidelength", m_hexSideLength);

    if (const auto it = json.find("backgroundcolor"); it != json.end()) {
      m_backgroundColor = color{it->get<std::string>()};
    }

    for (const auto& [key, value] : json.at("layers").items()) {
      m_layers.emplace_back(value);
    }

    for (const auto& [key, value] : json.at("tilesets").items()) {
      if (const auto it = value.find("source"); it != value.end()) {
        const auto firstgid = global_id{value.at("firstgid").get<unsigned>()};
        const auto src = it->get<std::string>();
        m_tilesets.push_back(tileset::external(root, firstgid, src.data()));
      } else {
        m_tilesets.push_back(tileset::embedded(value));
      }
    }
  }
};

NLOHMANN_JSON_SERIALIZE_ENUM(map::render_order,
                             {{map::render_order::right_down, "right-down"},
                              {map::render_order::right_up, "right-up"},
                              {map::render_order::left_down, "left-down"},
                              {map::render_order::left_up, "left-up"}})

NLOHMANN_JSON_SERIALIZE_ENUM(map::orientation,
                             {{map::orientation::orthogonal, "orthogonal"},
                              {map::orientation::isometric, "isometric"},
                              {map::orientation::staggered, "staggered"},
                              {map::orientation::hexagonal, "hexagonal"}})

NLOHMANN_JSON_SERIALIZE_ENUM(map::stagger_axis,
                             {{map::stagger_axis::x, "x"},
                              {map::stagger_axis::y, "y"}})

NLOHMANN_JSON_SERIALIZE_ENUM(map::stagger_index,
                             {{map::stagger_index::odd, "odd"},
                              {map::stagger_index::even, "even"}})

}  // namespace step

#endif  // STEP_MAP_HEADER

// #include "object.hpp"

// #include "object_group.hpp"

// #include "point.hpp"

// #include "properties.hpp"

// #include "property.hpp"

// #include "step_api.hpp"

// #include "step_exception.hpp"

// #include "step_fwd.hpp"

// #include "terrain.hpp"

// #include "text.hpp"

// #include "tile.hpp"

// #include "tile_layer.hpp"

// #include "tile_offset.hpp"

// #include "tileset.hpp"

// #include "types.hpp"

// #include "utils.hpp"

// #include "valid_property.hpp"

// #include "wang_color.hpp"

// #include "wang_set.hpp"

// #include "wang_tile.hpp"
