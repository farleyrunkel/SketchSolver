#ifndef PointHorizontalDistanceConstraint_H
#define PointHorizontalDistanceConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Geometry/Point.h"
#include "../Functions/PointHorizontalDistanceErrorFunction.h"

namespace ssr
{

class PointHorizontalDistanceErrorFunction;

/// @brief Constraint enforcing a horizontal distance between two points.
class PointHorizontalDistanceConstraint : public Constraint
{
private:
    Point p1_;
    Point p2_;
    Param distance_;

public:
    PointHorizontalDistanceConstraint(const Point& p1, const Point& p2, const Param& distance)
        : Constraint(std::make_unique<PointHorizontalDistanceErrorFunction>()), p1_(p1), p2_(p2), distance_(distance)
    {}

    std::vector<Param> parameters() const override
    {
        return {p1_.x, p2_.x, distance_};
    }

    bool isValid() const override
    {
        return p1_.isValid() && p2_.isValid() && distance_.isValid();
    }
};

}

#endif // PointHorizontalDistanceConstraint_H
