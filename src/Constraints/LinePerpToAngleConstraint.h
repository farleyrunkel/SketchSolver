#ifndef LinePerpToAngleConstraint_H
#define LinePerpToAngleConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class LinePerpToAngleErrorFunction;

/// @brief Constraint enforcing a line to be perpendicular to a given angle.
class LinePerpToAngleConstraint : public Constraint
{
private:
    Line line_;
    Param angle_;

public:
    LinePerpToAngleConstraint(const Line& line, const Param& angle)
        : Constraint(std::make_unique<LinePerpToAngleErrorFunction>()), line_(line), angle_(angle)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = line_.parameters();
        params.push_back(angle_);
        return params;
    }

    bool isValid() const override
    {
        return line_.isValid() && angle_.isValid();
    }
};

}

#endif // LinePerpToAngleConstraint_H
