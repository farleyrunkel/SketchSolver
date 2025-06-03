#ifndef PointOnArcAngleConstraint_H
#define PointOnArcAngleConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"
#include "../Segments/Arc.h"

namespace ssr
{

class PointOnArcAngleErrorFunction;

/// @brief Constraint that ensures a point lies on a circular arc at a given angle.
class PointOnArcAngleConstraint : public Constraint
{
private:
    Point point_;
    Arc arc_;

public:
    PointOnArcAngleConstraint(const Point& point, const Arc& arc)
        : Constraint(std::make_unique<PointOnArcAngleErrorFunction>()),
        point_(point), arc_(arc)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = point_.parameters();
        auto arcParams = arc_.center().parameters();
        params.insert(params.end(), arcParams.begin(), arcParams.end());
        params.push_back(arc_.radius());
        return params;
    }

    bool isValid() const override
    {
        return point_.isValid() && arc_.isValid();
    }
};

} // namespace ssr

#endif // PointOnArcAngleConstraint_H
