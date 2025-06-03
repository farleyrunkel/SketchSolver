#ifndef PointOnPointConstraint_H
#define PointOnPointConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"

namespace ssr
{

class PointOnPointErrorFunction;

/// @brief Constraint that ensures two points coincide.
class PointOnPointConstraint : public Constraint
{
private:
    Point point1_;
    Point point2_;

public:
    PointOnPointConstraint(const Point& point1, const Point& point2)
        : Constraint(std::make_unique<PointOnPointErrorFunction>()),
        point1_(point1), point2_(point2)
    {}

    std::vector<Param> parameters() const override
    {
        auto params1 = point1_.parameters();
        auto params2 = point2_.parameters();
        params1.insert(params1.end(), params2.begin(), params2.end());
        return params1;
    }

    bool isValid() const override
    {
        return point1_.isValid() && point2_.isValid();
    }
};

}

#endif // PointOnPointConstraint_H
