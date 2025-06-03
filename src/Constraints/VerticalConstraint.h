#ifndef VerticalConstraint_H
#define VerticalConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class VerticalErrorFunction;

/// @brief Constraint for ensuring a line is Vertical.
class VerticalConstraint : public Constraint
{
private:
    Line line_; ///< Line to be constrained Vertical.

public:
    /// @brief Constructs constraint for a line to be Vertical.
    /// @param line The line.
    VerticalConstraint(const Line& line)
        : Constraint(std::make_unique<VerticalErrorFunction>()),
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

#endif // VerticalConstraint_H