#ifndef STEP_COMMON_HEADER
#define STEP_COMMON_HEADER

#include <cstdint>      // uint8_t
#include <string>       // string
#include <type_traits>  // is_nothrow_copy_constructible, ...
#include <utility>      // move

namespace step {

namespace detail {
struct local_id_t;
struct global_id_t;
struct object_id_t;
struct file_path_t;
}  // namespace detail

template <typename T, typename /*Tag*/>
struct strong_type final
{
  // clang-format off
  inline static constexpr bool nothrow_default_constructor = std::is_nothrow_constructible_v<T>;
  inline static constexpr bool nothrow_copy = std::is_nothrow_copy_constructible_v<T>;
  inline static constexpr bool nothrow_move = std::is_nothrow_move_constructible_v<T>;
  // clang-format on

  T value;

  constexpr strong_type() noexcept(nothrow_default_constructor) = default;

  explicit constexpr strong_type(T&& val) noexcept(nothrow_move)
      : value{std::move(val)}
  {}

  explicit constexpr strong_type(const T& val) noexcept(nothrow_copy)
      : value{val}
  {}

  constexpr strong_type(const strong_type&) noexcept(nothrow_copy) = default;
  constexpr strong_type(strong_type&&) noexcept(nothrow_move) = default;

  // clang-format off
  constexpr strong_type& operator=(const strong_type&) noexcept(nothrow_copy) = default;
  constexpr strong_type& operator=(strong_type&&) noexcept(nothrow_move) = default;
  // clang-format on

  /* implicit */ operator T() const noexcept(nothrow_copy)
  {
    return value;
  }

  /* implicit */ operator T&() noexcept(nothrow_copy)
  {
    return value;
  }

  /* implicit */ operator const T&() const noexcept(nothrow_copy)
  {
    return value;
  }
};

using uint8 = std::uint8_t;

using local_id = strong_type<int, detail::local_id_t>;

using global_id = strong_type<unsigned, detail::global_id_t>;

using object_id = strong_type<int, detail::object_id_t>;

using file_path = strong_type<std::string, detail::file_path_t>;

}  // namespace step

#endif  // STEP_COMMON_HEADER
