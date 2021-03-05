#ifndef STEP_DATA_HEADER
#define STEP_DATA_HEADER

#include <string>
#include <variant>
#include <vector>

#include "common.hpp"
#include "step_api.hpp"
#include "step_exception.hpp"

namespace step::detail {

/**
 * \class data
 *
 * \brief A helper class that represents either GID or Base64 tile data.
 *
 * \since 0.1.0
 *
 * \headerfile step_data.hpp
 */
class data final
{
 public:
  using gid_data = std::vector<global_id>;
  using base64_data = std::string;

  explicit data(const json& json)
  {
    if (json.is_array()) {
      auto& gidData = m_data.emplace<gid_data>();
      for (const auto& [key, value] : json.items()) {
        gidData.emplace_back(value.get<unsigned>());
      }
    } else if (json.is_string()) {
      m_data.emplace<data::base64_data>(json.get<data::base64_data>());
    } else {
      throw step_exception{"Failed to determine the kind of data!"};
    }
  }

  /**
   * \brief Returns the GID data associated with the Data instance.
   *
   * \details This method throws if the internal data isn't actually GID data.
   *
   * \return the GID data associated with the Data instance.
   *
   * \throws step_exception if the data cannot be obtained.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto as_gid() const -> const gid_data&
  {
    if (std::holds_alternative<gid_data>(m_data)) {
      return std::get<gid_data>(m_data);
    } else {
      throw step_exception{"Couldn't obtain GID data!"};
    }
  }

  /**
   * \brief Returns the Base64 data associated with the Data instance.
   *
   * \note This function throws if the internal data isn't actually Base64
   * data.
   *
   * \return the Base64 data associated with the data instance.
   *
   * \throws step_exception if the data cannot be obtained.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto as_base64() const -> const base64_data&
  {
    if (std::holds_alternative<base64_data>(m_data)) {
      return std::get<base64_data>(m_data);
    } else {
      throw step_exception{"Couldn't obtain Base64 data!"};
    }
  }

 private:
  std::variant<gid_data, base64_data> m_data;
};

}  // namespace step::detail

#endif  // STEP_DATA_HEADER
