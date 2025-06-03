#ifndef SKETCHSOLVER_ARC_H
#define SKETCHSOLVER_ARC_H

#include <vector>

#include "../Param.h"
#include "../Point.h"
#include "../Segment.h"

namespace ssr
{

/// @brief Represents an arc defined by a center, angles, and radius.
class Arc : public Segment
{
private:
    Point center_;     ///< Center point.
    Param startAngle_; ///< Start angle (radians).
    Param endAngle_;   ///< End angle (radians).
    Param radius_;     ///< Radius.

public:
    /// @brief Default constructor.
    Arc() = default;

    /// @brief Constructs an Arc with given parameters.
    Arc(const Point& center, const Param& start, const Param& end, const Param& rad)
        : center_(center), startAngle_(start), endAngle_(end), radius_(rad)
    {}

    /// @brief Gets the center point.
    Point center() const noexcept { return center_; }

    /// @brief Gets the start angle.
    Param startAngle() const noexcept { return startAngle_; }

    /// @brief Gets the end angle.
    Param endAngle() const noexcept { return endAngle_; }

    /// @brief Gets the radius.
    Param radius() const noexcept { return radius_; }

    /// @brief Sets the center point.
    void setCenter(const Point& center) { center_ = center; }

    /// @brief Sets the start angle.
    void setStartAngle(const Param& start) { startAngle_ = start; }

    /// @brief Sets the end angle.
    void setEndAngle(const Param& end) { endAngle_ = end; }

    /// @brief Sets the radius.
    void setRadius(const Param& rad) { radius_ = rad; }

    /// @brief Checks if the arc's components are valid.
    bool isValid() const noexcept override
    {
        return center_.isValid() && startAngle_.isValid() && endAngle_.isValid() && radius_.isValid();
    }

    /// @brief Gets all parameters of the arc.
    std::vector<Param> parameters() const override
    {
        return {center_.x(), center_.y(), startAngle_, endAngle_, radius_};
    }
};

} // namespace ssr

#endif // SKETCHSOLVER_ARC_H
