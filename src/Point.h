#ifndef SKETCHSOLVER_POINT_H
#define SKETCHSOLVER_POINT_H

#include <vector>

#include "Param.h"

namespace ssr
{

/// @brief Represents a 2D point with parameter coordinates.
class Point
{
private:
    Param x_; ///< X-coordinate parameter.
    Param y_; ///< Y-coordinate parameter.

public:
    /// @brief Default constructor, initializes params to nullptr.
    Point() = default;

    /// @brief Constructs a Point with given parameters.
    Point(const Param& px, const Param& py) : x_(px), y_(py) {}

    /// @brief Constructs a Point with given values, allocating new memory.
    Point(double px, double py) : x_(px), y_(py) {}

    /// @brief Gets the x-coordinate parameter.
    Param x() const noexcept { return x_; }

    /// @brief Gets the y-coordinate parameter.
    Param y() const noexcept { return y_; }

    /// @brief Sets the x-coordinate parameter.
    void setX(const Param& px) { x_ = px; }

    /// @brief Sets the y-coordinate parameter.
    void setY(const Param& py) { y_ = py; }

    /// @brief Checks if the point's parameters are valid.
    bool isValid() const noexcept { return x_.isValid() && y_.isValid(); }

    /// @brief Gets all parameters of the point.
    std::vector<Param> parameters() const { return {x_, y_}; }
};

} // namespace ssr

#endif // SKETCHSOLVER_POINT_H
