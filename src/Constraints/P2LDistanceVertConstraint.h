#ifndef P2LDistanceVertConstraint_H
#define P2LDistanceVertConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"
#include "../Segments/Line.h"

namespace ssr
{

class P2LDistanceVertErrorFunction;

/// @brief Constraint that ensures the vertical distance from a point to its projection on a line equals a target distance.
class P2LDistanceVertConstraint : public Constraint
{
private:
    Line line_;
    Point point_;
    Param targetDistance_;

public:
    P2LDistanceVertConstraint(const Line& line, const Point& point, const Param& targetDistance)
        : Constraint(std::make_unique<P2LDistanceVertErrorFunction>()),
        line_(line), point_(point), targetDistance_(targetDistance)
    {
        targetDistance_.setConstant();
    }

    std::vector<Param> parameters() const override
    {
        auto lineParams = line_.parameters();    // [x1, y1, x2, y2]
        auto pointParams = point_.parameters();  // [px, py]
        lineParams.insert(lineParams.end(), pointParams.begin(), pointParams.end());
        lineParams.push_back(targetDistance_);   // total: 7
        return lineParams;
    }

    bool isValid() const override
    {
        return line_.isValid() && point_.isValid() && targetDistance_.isValid();
    }
};

}

#endif // P2LDistanceVertConstraint_H
