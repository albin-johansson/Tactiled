#include "step_utils.hpp"

#include <fstream>

#include "step_exception.hpp"

namespace step::detail {

json parse_json(std::string_view file)
{
  if (!file.data()) {
    throw StepException{"Cannot parse JSON from null file!"};
  }

  try {
    json json;
    std::ifstream stream{file.data()};
    stream >> json;
    return json;
  } catch (const std::exception& e) {
    using namespace std::string_literals;
    throw StepException{e.what() ? e.what() : "Failed to parse JSON!"s};
  }
}

}  // namespace step::detail
