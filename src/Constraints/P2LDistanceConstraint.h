#ifndef P2LDistanceConstraint_H
#define P2LDistanceConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"
#include "../Segments/Line.h"

namespace ssr
{

class P2LDistanceErrorFunction;

/// @brief Constraint that ensures a point lies at a fixed distance from a given line.
class P2LDistanceConstraint : public Constraint
{
private:
    Line line_;
    Point point_;
    Param distance_;

public:
    P2LDistanceConstraint(const Line& line, const Point& point, const Param& distance)
        : Constraint(std::make_unique<P2LDistanceErrorFunction>()),
        line_(line), point_(point), distance_(distance)
    {}

    std::vector<Param> parameters() const override
    {
        auto lineParams = line_.parameters();   // start(x,y), end(x,y)
        auto pointParams = point_.parameters(); // px, py
        lineParams.insert(lineParams.end(), pointParams.begin(), pointParams.end());
        lineParams.push_back(distance_);
        return lineParams;
    }

    bool isValid() const override
    {
        return line_.isValid() && point_.isValid() && distance_.isValid();
    }
};

}

#endif // P2LDistanceConstraint_H
