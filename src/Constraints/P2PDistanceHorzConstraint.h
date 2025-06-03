#ifndef P2PDistanceHorzConstraint_H
#define P2PDistanceHorzConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"

namespace ssr
{

class P2PDistanceHorzErrorFunction;

/// @brief Constraint that ensures the horizontal distance between two points equals a target value.
class P2PDistanceHorzConstraint : public Constraint
{
private:
    Point point1_;
    Point point2_;
    Param targetDistance_;

public:
    P2PDistanceHorzConstraint(const Point& point1, const Point& point2, const Param& targetDistance)
        : Constraint(std::make_unique<P2PDistanceHorzErrorFunction>()),
        point1_(point1), point2_(point2), targetDistance_(targetDistance)
    {
        targetDistance_.setConstant();
    }

    std::vector<Param> parameters() const override
    {
        auto p1 = point1_.parameters();   // [x1, y1]
        auto p2 = point2_.parameters();   // [x2, y2]
        p1.insert(p1.end(), p2.begin(), p2.end());
        p1.push_back(targetDistance_);   // total: 5
        return p1;
    }

    bool isValid() const override
    {
        return point1_.isValid() && point2_.isValid() && targetDistance_.isValid();
    }
};

}

#endif // P2PDistanceHorzConstraint_H
