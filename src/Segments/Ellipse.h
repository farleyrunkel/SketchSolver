#ifndef SKETCHSOLVER_ELLIPSE_H
#define SKETCHSOLVER_ELLIPSE_H

#include <vector>

#include "../Param.h"
#include "../Point.h"
#include "../Segment.h"

namespace ssr
{

/// @brief Represents an ellipse defined by a center, radii, and rotation.
class Ellipse : public Segment
{
private:
    Point center_;    ///< Center point.
    Param radiusOne_; ///< First radius.
    Param radiusTwo_; ///< Second radius.
    Param rotation_;  ///< Rotation angle (radians).

public:
    /// @brief Default constructor.
    Ellipse() = default;

    /// @brief Constructs an Ellipse with given parameters.
    Ellipse(const Point& center, const Param& r1, const Param& r2, const Param& rot)
        : center_(center), radiusOne_(r1), radiusTwo_(r2), rotation_(rot)
    {}

    /// @brief Gets the center point.
    Point center() const noexcept { return center_; }

    /// @brief Gets the first radius.
    Param radiusOne() const noexcept { return radiusOne_; }

    /// @brief Gets the second radius.
    Param radiusTwo() const noexcept { return radiusTwo_; }

    /// @brief Gets the rotation angle.
    Param rotation() const noexcept { return rotation_; }

    /// @brief Sets the center point.
    void setCenter(const Point& center) { center_ = center; }

    /// @brief Sets the first radius.
    void setRadiusOne(const Param& r1) { radiusOne_ = r1; }

    /// @brief Sets the second radius.
    void setRadiusTwo(const Param& r2) { radiusTwo_ = r2; }

    /// @brief Sets the rotation angle.
    void setRotation(const Param& rot) { rotation_ = rot; }

    /// @brief Checks if the ellipse's components are valid.
    bool isValid() const noexcept override
    {
        return center_.isValid() && radiusOne_.isValid() && radiusTwo_.isValid() && rotation_.isValid();
    }

    /// @brief Gets all parameters of the ellipse.
    std::vector<Param> parameters() const override
    {
        return {center_.x(), center_.y(), radiusOne_, radiusTwo_, rotation_};
    }
};

} // namespace ssr

#endif // SKETCHSOLVER_ELLIPSE_H
