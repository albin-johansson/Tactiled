#include "step_data.hpp"

#include "step_exception.hpp"
#include "step_utils.hpp"

namespace step::detail {

Data::Data(const json& json)
{
  if (json.is_array()) {
    //    m_data = detail::fill<GIDData>(json);
    auto& gidData = m_data.emplace<GIDData>();
    for (const auto& [key, value] : json.items()) {
      gidData.emplace_back(value.get<unsigned>());
    }
  } else if (json.is_string()) {
    m_data.emplace<Data::Base64Data>(json.get<Data::Base64Data>());
  } else {
    throw step_exception{"Data > Failed to determine the kind of data!"};
  }
}

const Data::GIDData& Data::as_gid() const
{
  if (std::holds_alternative<GIDData>(m_data)) {
    return std::get<GIDData>(m_data);
  } else {
    throw step_exception{"Data > Couldn't obtain GID data!"};
  }
}

const Data::Base64Data& Data::as_base64() const
{
  if (std::holds_alternative<Base64Data>(m_data)) {
    return std::get<Base64Data>(m_data);
  } else {
    throw step_exception{"Data > Couldn't obtain Base64 data!"};
  }
}

}  // namespace step::detail
