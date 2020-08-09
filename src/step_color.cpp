#include "step_color.hpp"

#include <charconv>
#include <string>

#include "step_exception.hpp"
#include "step_utils.hpp"

namespace step {
namespace {

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
auto from_hex(std::string_view view) -> uint8_t
{
  try {
    return detail::convert<uint8_t>(view, 16);
  } catch (...) {
    using namespace std::string_literals;
    throw step_exception{"color > Failed to parse hex string: "s.append(view)};
  }
}

}  // namespace

color::color(std::string_view value)
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
      m_alpha = from_hex(withoutHash.substr(0, 2));
      m_red = from_hex(withoutHash.substr(2, 2));
      m_green = from_hex(withoutHash.substr(4, 2));
      m_blue = from_hex(withoutHash.substr(6, 2));
    } else {  // RRGGBB
      m_red = from_hex(withoutHash.substr(0, 2));
      m_green = from_hex(withoutHash.substr(2, 2));
      m_blue = from_hex(withoutHash.substr(4, 2));
    }

  } catch (const step_exception&) {
    throw;
  } catch (...) {
    throw step_exception{"Couldn't create color!"};
  }
}

}  // namespace step
