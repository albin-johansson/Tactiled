#ifndef STEP_ERROR_HEADER
#define STEP_ERROR_HEADER

#include <exception>  // exception

namespace step {

class step_error final : public std::exception
{
 public:
  explicit step_error(const char* msg) : m_msg{msg}
  {}

  [[nodiscard]] auto what() const -> const char* override
  {
    return m_msg;
  }

 private:
  const char* m_msg;
};

}  // namespace step

#endif  // STEP_ERROR_HEADER
