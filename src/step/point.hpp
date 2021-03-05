#ifndef STEP_POINT_HEADER
#define STEP_POINT_HEADER

#include "step_api.hpp"
#include "types.hpp"

namespace step {

/**
 * \class point
 *
 * \brief Represents a simple 2D-coordinate in the plane.
 *
 * \since 0.1.0
 *
 * \headerfile step_point.hpp
 */
class point final
{
 public:
  point() noexcept = default;

  /**
   * \brief Parses a point from a JSON object.
   *
   * \param json the JSON object that represents the point.
   *
   * \since 0.2.0
   */
  explicit point(const json& json)
      : m_x{json.at("x").get<double>()}
      , m_y{json.at("y").get<double>()}
  {}

  /**
   * \brief Returns the x-coordinate associated with the point.
   *
   * \return the x-coordinate of the point.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> double
  {
    return m_x;
  }

  /**
   * \brief Returns the y-coordinate associated with the point.
   *
   * \return the y-coordinate of the point.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> double
  {
    return m_y;
  }

 private:
  double m_x{};
  double m_y{};
};

}  // namespace step

#endif  // STEP_POINT_HEADER