#include "step_color.h"

#include <charconv>
#include <string>

#include "step_exception.h"
#include "step_utils.h"

namespace step {
namespace {

/**
 * Converts the supplied string that is in hex format to the corresponding
 * value.
 *
 * @param view the string that will be converted, e.g "E7".
 * @return the value of the supplied string.
 * @throws StepException if the conversion is unsuccessful.
 * @since 0.1.0
 */
uint8_t from_hex(std::string_view view)
{
  try {
    return detail::convert<uint8_t>(view, 16);
  } catch (...) {
    using namespace std::string_literals;
    throw StepException{"Color > Failed to parse hex string: "s.append(view)};
  }
}

}  // namespace

Color::Color(std::string_view value)
{
  if (value.length() != 7 && value.length() != 9) {
    const auto badLen = std::to_string(value.length());
    throw StepException{"Color > Input string has incorrect length: " + badLen};
  }

  if (value.at(0) != '#') {
    throw StepException{"Color > Input string must begin with #"};
  }

  const auto withoutHash = value.substr(1);
  const auto len = withoutHash.length();

  try {
    m_red = from_hex(withoutHash.substr(0, 2));
    m_green = from_hex(withoutHash.substr(2, 2));
    m_blue = from_hex(withoutHash.substr(4, 2));
    if (len == 8) {
      m_alpha = from_hex(withoutHash.substr(6, 2));
    }
  } catch (const StepException&) {
    throw;
  } catch (...) {
    throw StepException{"Couldn't create Color!"};
  }
}

}  // namespace step
