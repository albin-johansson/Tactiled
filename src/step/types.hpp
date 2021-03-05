#ifndef STEP_TYPES_HEADER
#define STEP_TYPES_HEADER

#include <cstdint>
#include <filesystem>
#include <json.hpp>
#include <named_type.hpp>
#include <optional>

#include "step_api.hpp"

namespace step {

namespace fs = std::filesystem;

using nlohmann::json;
using czstring = const char*;

/**
 * The type used for properties that represent a file path.
 *
 * @since 0.1.0
 */
using file = fluent::NamedType<std::string,
                               struct file_t,
                               fluent::Comparable,
                               fluent::Printable>;

/**
 * The type used for global IDs (GIDs).
 *
 * @since 0.1.0
 */
using global_id = fluent::NamedType<unsigned,
                                    struct global_id_t,
                                    fluent::Comparable,
                                    fluent::Addable,
                                    fluent::Subtractable,
                                    fluent::Printable>;

/**
 * The type used for local IDs (LIDs).
 *
 * @since 0.1.0
 */
using local_id = fluent::NamedType<int,
                                   struct local_id_t,
                                   fluent::Comparable,
                                   fluent::Addable,
                                   fluent::Subtractable,
                                   fluent::Printable>;

/**
 * The type used for object references.
 *
 * @since 0.2.0
 */
using object_ref = fluent::NamedType<int,
                                     struct object_ref_t,
                                     fluent::Comparable,
                                     fluent::Addable,
                                     fluent::Subtractable,
                                     fluent::Printable>;

/**
 * Constructs a global ID from an integer literal.
 *
 * @param value the literal that will be converted.
 * @return a global ID value.
 * @since 0.1.0
 */
[[nodiscard]] inline auto operator"" _gid(unsigned long long int value) noexcept
    -> global_id
{
  return global_id{static_cast<unsigned>(value)};
}

/**
 * Constructs a local ID from an integer literal.
 *
 * @param value the literal that will be converted.
 * @return a local ID value.
 * @since 0.1.0
 */
[[nodiscard]] inline auto operator"" _lid(unsigned long long int value) noexcept
    -> local_id
{
  return local_id{static_cast<int>(value)};
}

/**
 * Constructs a File instance from a string literal.
 *
 * @param str the string that will be converted to a File instance.
 * @return a File instance.
 * @since 0.1.0
 */
[[nodiscard]] inline auto operator"" _file(const char* str, std::size_t) -> file
{
  return file{str};
}

}  // namespace step

#endif  // STEP_TYPES_HEADER
