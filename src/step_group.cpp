#include "step_group.hpp"

#include "step_layer.hpp"

namespace step {

const Layer& Group::at(int index) const
{
  return *m_layers.at(static_cast<std::size_t>(index));
}

int Group::layers() const noexcept
{
  return static_cast<int>(m_layers.size());
}

void from_json(const json& json, Group& group)  // FIXME
{
  for (const auto& [key, value] : json.at("layers").items()) {
    group.m_layers.push_back(std::make_unique<Layer>(value));
  }
}

}  // namespace step
