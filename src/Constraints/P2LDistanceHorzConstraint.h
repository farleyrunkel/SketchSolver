#ifndef P2LDistanceHorzConstraint_H
#define P2LDistanceHorzConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"
#include "../Segments/Line.h"

namespace ssr
{

class P2LDistanceHorzErrorFunction;

/// @brief Constraint that ensures the horizontal distance from a point to a vertical projection on a line equals a target distance.
class P2LDistanceHorzConstraint : public Constraint
{
private:
    Line line_;
    Point point_;
    Param targetDistance_;

public:
    P2LDistanceHorzConstraint(const Line& line, const Point& point, const Param& targetDistance)
        : Constraint(std::make_unique<P2LDistanceHorzErrorFunction>()),
        line_(line), point_(point), targetDistance_(targetDistance)
    {
        targetDistance_.setConstant();
    }

    std::vector<Param> parameters() const override
    {
        auto lineParams = line_.parameters();     // [x1, y1, x2, y2]
        auto pointParams = point_.parameters();   // [px, py]
        lineParams.insert(lineParams.end(), pointParams.begin(), pointParams.end());
        lineParams.push_back(targetDistance_);    // total: 7
        return lineParams;
    }

    bool isValid() const override
    {
        return line_.isValid() && point_.isValid() && targetDistance_.isValid();
    }
};

}

#endif // P2LDistanceHorzConstraint_H
