#ifndef PointVerticalDistanceConstraint_H
#define PointVerticalDistanceConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"

namespace ssr
{

class PointVerticalDistanceErrorFunction;

/// @brief Constraint that ensures a point has a fixed vertical distance from a reference (y = 0 or another baseline).
class PointVerticalDistanceConstraint : public Constraint
{
private:
    Param y_;
    Param targetDistance_;

public:
    PointVerticalDistanceConstraint(const Param& y, const Param& targetDistance)
        : Constraint(std::make_unique<PointVerticalDistanceErrorFunction>()),
        y_(y), targetDistance_(targetDistance)
    {}

    std::vector<Param> parameters() const override
    {
        // Assuming params: [x_dummy, y_actual, target_distance]
        // A dummy x param is used to align with function signature expectations (param[0] is unused)
        return {Param(nullptr), y_, targetDistance_};
    }

    bool isValid() const override
    {
        return y_.isValid() && targetDistance_.isValid();
    }
};

}

#endif // PointVerticalDistanceConstraint_H
