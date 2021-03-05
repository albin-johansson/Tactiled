#ifndef STEP_EXCEPTION_HEADER
#define STEP_EXCEPTION_HEADER

#include <exception>
#include <utility>

#include "types.hpp"

namespace step {

class step_exception final : public std::exception
{
 public:
  step_exception() noexcept = default;

  explicit step_exception(std::string what) : m_what{std::move(what)}
  {}

  ~step_exception() noexcept override = default;

  czstring what() const noexcept override
  {
    return m_what.c_str();
  }

 private:
  std::string m_what;
};

}  // namespace step

#endif  // STEP_EXCEPTION_HEADER
