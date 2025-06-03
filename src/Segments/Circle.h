#ifndef SKETCHSOLVER_CIRCLE_H
#define SKETCHSOLVER_CIRCLE_H

#include <vector>

#include "../Param.h"
#include "../Point.h"
#include "../Segment.h"

namespace ssr
{

/// @brief Represents a circle defined by a center and radius.
class Circle : public Segment
{
private:
    Point center_; ///< Center point.
    Param radius_; ///< Radius.

public:
    /// @brief Default constructor.
    Circle() = default;

    /// @brief Constructs a Circle with given center and radius.
    Circle(const Point& center, const Param& rad) : center_(center), radius_(rad) {}

    /// @brief Gets the center point.
    Point center() const noexcept { return center_; }

    /// @brief Gets the radius.
    Param radius() const noexcept { return radius_; }

    /// @brief Sets the center point.
    void setCenter(const Point& center) { center_ = center; }

    /// @brief Sets the radius.
    void setRadius(const Param& rad) { radius_ = rad; }

    /// @brief Checks if the circle's components are valid.
    bool isValid() const noexcept override { return center_.isValid() && radius_.isValid(); }

    /// @brief Gets all parameters of the circle.
    std::vector<Param> getParameters() const override
    {
        return {center_.x(), center_.y(), radius_};
    }
};

} // namespace ssr

#endif // SKETCHSOLVER_CIRCLE_H
