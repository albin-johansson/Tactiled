#include "step.hpp"

#include "step_utils.hpp"

namespace step {

auto parse(const fs::path& path) -> std::unique_ptr<Map>
{
  return std::make_unique<Map>(path);
}

auto parse(std::string_view root, std::string_view file) -> std::unique_ptr<Map>
{
  return std::make_unique<Map>(root, file);
}

}  // namespace step
