#include "step_properties.h"

#include "step_exception.h"

namespace step {

Properties::Properties(const json& json)
{
  for (const auto& [key, value] : json.items()) {
    const Property property{value};
    m_properties.emplace(property.name(), value);
  }
}

bool Properties::has(const std::string& name) const
{
  return m_properties.count(name);
}

const Property& Properties::get(const std::string& name) const
{
  try {
    return m_properties.at(name);
  } catch (...) {
    throw StepException{"Properties > Couldn't lookup property: " + name};
  }
}

int Properties::amount() const noexcept
{
  return static_cast<int>(m_properties.size());
}

bool Properties::empty() const noexcept
{
  return m_properties.empty();
}

}  // namespace step
