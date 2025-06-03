#ifndef PerpendicularConstraint_H
#define PerpendicularConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class PerpendicularErrorFunction;

/// @brief Constraint enforcing two lines to be perpendicular.
class PerpendicularConstraint : public Constraint
{
private:
    Line line1_, line2_;

public:
    PerpendicularConstraint(const Line& line1, const Line& line2)
        : Constraint(std::make_unique<PerpendicularErrorFunction>()), line1_(line1), line2_(line2)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = line1_.parameters();
        auto params2 = line2_.parameters();
        params.insert(params.end(), params2.begin(), params2.end());
        return params;
    }

    bool isValid() const override
    {
        return line1_.isValid() && line2_.isValid();
    }
};

}

#endif // PerpendicularConstraint_H
