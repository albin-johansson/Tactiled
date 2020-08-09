#include "step_property.h"

#include "step_exception.h"

namespace step {

Property::Property(const json& json)
{
  m_name = json.at("name").get<std::string>();
  m_type = json.at("type").get<Property::Type>();
  switch (m_type) {
    case Property::Type::Int: {
      m_value.emplace<int>(json.at("value").get<int>());
      break;
    }
    case Property::Type::Float: {
      m_value.emplace<float>(json.at("value").get<float>());
      break;
    }
    case Property::Type::Bool: {
      m_value.emplace<bool>(json.at("value").get<bool>());
      break;
    }
    case Property::Type::Color: {
      m_value.emplace<Color>(json.at("value").get<std::string>());
      break;
    }
    case Property::Type::File: {
      m_value.emplace<file>(json.at("value").get<std::string>());
      break;
    }
    case Property::Type::String: {
      m_value.emplace<std::string>(json.at("value").get<std::string>());
      break;
    }
    default:
      throw StepException{"Unknown property type!"};
  }
}

}  // namespace step
