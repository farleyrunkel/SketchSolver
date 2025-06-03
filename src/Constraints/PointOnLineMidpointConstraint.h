#ifndef PointOnLineMidpointConstraint_H
#define PointOnLineMidpointConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"
#include "../Segments/Line.h"

namespace ssr
{

class PointOnLineMidpointErrorFunction;

/// @brief Constraint that ensures a point lies at the midpoint of a given line.
class PointOnLineMidpointConstraint : public Constraint
{
private:
    Line line_;
    Point point_;

public:
    PointOnLineMidpointConstraint(const Line& line, const Point& point)
        : Constraint(std::make_unique<PointOnLineMidpointErrorFunction>()),
        line_(line), point_(point)
    {}

    std::vector<Param> parameters() const override
    {
        auto lineParams = line_.parameters();
        auto pointParams = point_.parameters();
        lineParams.insert(lineParams.end(), pointParams.begin(), pointParams.end());
        return lineParams;
    }

    bool isValid() const override
    {
        return line_.isValid() && point_.isValid();
    }
};

}

#endif // PointOnLineMidpointConstraint_H
