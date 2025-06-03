#ifndef PointOnLineConstraint_H
#define PointOnLineConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"
#include "../Segments/Line.h"

namespace ssr
{

class PointOnLineErrorFunction;

/// @brief Constraint that ensures a point lies on a given line.
class PointOnLineConstraint : public Constraint
{
private:
    Point point_;
    Line line_;

public:
    PointOnLineConstraint(const Point& point, const Line& line)
        : Constraint(std::make_unique<PointOnLineErrorFunction>()),
        point_(point), line_(line)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = point_.parameters();
        auto lineParams = line_.parameters();
        params.insert(params.end(), lineParams.begin(), lineParams.end());
        return params;
    }

    bool isValid() const override
    {
        return point_.isValid() && line_.isValid();
    }
};

}

#endif // PointOnLineConstraint_H
