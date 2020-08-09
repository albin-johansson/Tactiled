#include "step_property.hpp"

#include "step_exception.hpp"

namespace step {

property::property(const json& json)
{
  m_name = json.at("name").get<std::string>();
  m_type = json.at("type").get<property::Type>();
  switch (m_type) {
    case property::Type::Int: {
      m_value.emplace<int>(json.at("value").get<int>());
      break;
    }
    case property::Type::Float: {
      m_value.emplace<float>(json.at("value").get<float>());
      break;
    }
    case property::Type::Bool: {
      m_value.emplace<bool>(json.at("value").get<bool>());
      break;
    }
    case property::Type::Color: {
      m_value.emplace<Color>(json.at("value").get<std::string>());
      break;
    }
    case property::Type::File: {
      m_value.emplace<file>(json.at("value").get<std::string>());
      break;
    }
    case property::Type::String: {
      m_value.emplace<std::string>(json.at("value").get<std::string>());
      break;
    }
    default:
      throw step_exception{"Unknown property type!"};
  }
}

}  // namespace step
