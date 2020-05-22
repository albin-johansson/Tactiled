#ifndef TACTILED_TYPES_HEADER
#define TACTILED_TYPES_HEADER

#include <optional>

namespace tactiled {

//template <typename T, typename Deleter = std::default_delete<T>()>
//using UniquePtr = std::unique_ptr<T, Deleter>;
//
//template <typename T>
//using SharedPtr = std::shared_ptr<T>;
//
//template <typename T>
//using WeakPtr = std::weak_ptr<T>;

inline constexpr std::nullopt_t nothing = std::nullopt;

}  // namespace tactiled

#endif  // TACTILED_TYPES_HEADER
