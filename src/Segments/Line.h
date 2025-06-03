#ifndef SKETCHSOLVER_LINE_H
#define SKETCHSOLVER_LINE_H

#include <vector>

#include "../Param.h"
#include "../Point.h"
#include "../Segment.h"

namespace ssr
{

/// @brief Represents a line segment defined by two points.
class Line : public Segment
{
private:
    Point p1_; ///< Starting point.
    Point p2_; ///< Ending point.

public:
    /// @brief Default constructor.
    Line() = default;

    /// @brief Constructs a Line with two points.
    Line(const Point& p1, const Point& p2) : p1_(p1), p2_(p2) {}

    /// @brief Gets the starting point.
    Point p1() const noexcept { return p1_; }

    /// @brief Gets the ending point.
    Point p2() const noexcept { return p2_; }

    /// @brief Sets the starting point.
    void setP1(const Point& p1) { p1_ = p1; }

    /// @brief Sets the ending point.
    void setP2(const Point& p2) { p2_ = p2; }

    /// @brief Checks if the line's points are valid.
    bool isValid() const noexcept override { return p1_.isValid() && p2_.isValid(); }

    /// @brief Gets all parameters of the line.
    std::vector<Param> parameters() const override
    {
        return {p1_.x(), p1_.y(), p2_.x(), p2_.y()};
    }
};


} // namespace ssr

#endif // SKETCHSOLVER_LINE_H
