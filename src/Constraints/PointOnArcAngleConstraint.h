#ifndef PointOnArcAngleConstraint_H
#define PointOnArcAngleConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"

namespace ssr
{

class PointOnArcAngleErrorFunction;

/// @brief Constraint that ensures a point lies on an arc defined by center, radius, and angle.
class PointOnArcAngleConstraint : public Constraint
{
private:
    Point point_;
    Param centerX_, centerY_;
    Param radius_, angle_;

public:
    PointOnArcAngleConstraint(
        const Point& point,
        const Param& centerX,
        const Param& centerY,
        const Param& radius,
        const Param& angle)
        : Constraint(std::make_unique<PointOnArcAngleErrorFunction>()),
        point_(point), centerX_(centerX), centerY_(centerY),
        radius_(radius), angle_(angle)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = point_.parameters();
        params.push_back(centerX_);
        params.push_back(centerY_);
        params.push_back(radius_);
        params.push_back(angle_);
        return params;
    }

    bool isValid() const override
    {
        return point_.isValid()
            && centerX_.isValid()
            && centerY_.isValid()
            && radius_.isValid()
            && angle_.isValid();
    }
};

}

#endif // PointOnArcAngleConstraint_H
