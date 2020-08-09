#include "step_property.hpp"

#include "step_exception.hpp"

namespace step {

property::property(const json& json)
    : m_name{json.at("name").get<std::string>()},
      m_type{json.at("type").get<property::type>()}
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
      m_value.emplace<Color>(json.at("value").get<std::string>());
      break;
    }
    case property::type::file: {
      m_value.emplace<file>(json.at("value").get<std::string>());
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

auto property::name() const -> std::string
{
  return m_name;
}

auto property::get_type() const noexcept -> property::type
{
  return m_type;
}

}  // namespace step
