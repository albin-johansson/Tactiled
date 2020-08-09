#include "step_properties.hpp"

#include "step_exception.hpp"

namespace step {

properties::properties(const json& json)
{
  for (const auto& [key, value] : json.items()) {
    const property property{value};
    m_properties.emplace(property.name(), value);
  }
}

auto properties::has(std::string_view name) const -> bool
{
  return m_properties.count(name);
}

auto properties::get(std::string_view name) const -> const property&
{
  const auto iterator = m_properties.find(name);
  if (iterator != m_properties.end()) {
    return iterator->second;
  } else {
    throw step_exception{"properties > Couldn't find property!"};
  }
}

auto properties::amount() const noexcept -> int
{
  return static_cast<int>(m_properties.size());
}

auto properties::empty() const noexcept -> bool
{
  return m_properties.empty();
}

}  // namespace step
