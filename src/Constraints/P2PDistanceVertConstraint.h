#ifndef P2PDistanceVertConstraint_H
#define P2PDistanceVertConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Point.h"

namespace ssr
{

class P2PDistanceVertErrorFunction;

/// @brief Constraint that ensures the vertical distance between two points equals a target value.
class P2PDistanceVertConstraint : public Constraint
{
private:
    Point point1_;
    Point point2_;
    Param targetDistance_;

public:
    P2PDistanceVertConstraint(const Point& point1, const Point& point2, const Param& targetDistance)
        : Constraint(std::make_unique<P2PDistanceVertErrorFunction>()),
        point1_(point1), point2_(point2), targetDistance_(targetDistance)
    {
        targetDistance_.setConstant();
    }

    std::vector<Param> parameters() const override
    {
        auto p1 = point1_.parameters();  // [x1, y1]
        auto p2 = point2_.parameters();  // [x2, y2]
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

#endif // P2PDistanceVertConstraint_H
