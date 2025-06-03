#ifndef HorizontalConstraint_H
#define HorizontalConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class HorizontalErrorFunction;

/// @brief Constraint for ensuring a line is horizontal.
class HorizontalConstraint : public Constraint
{
private:
    Line line_; ///< Line to be constrained horizontal.

public:
    /// @brief Constructs constraint for a line to be horizontal.
    /// @param line The line.
    HorizontalConstraint(const Line& line)
        : Constraint(std::make_unique<HorizontalErrorFunction>()),
        line_(line)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = line_.parameters();
        if(params.size() != 4)
        {
            throw std::runtime_error("Invalid line parameters: expected 4 parameters (x1, y1, x2, y2)");
        }
        return params;
    }

    bool isValid() const override
    {
        return line_.isValid();
    }
};

} // namespace ssr

#endif // HorizontalConstraint_H