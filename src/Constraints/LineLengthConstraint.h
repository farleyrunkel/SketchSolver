#ifndef LineLengthConstraint_H
#define LineLengthConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class LineLengthErrorFunction;

/// @brief Constraint for maintaining a specified length for a line.
class LineLengthConstraint : public Constraint
{
private:
    Line line_; ///< Line to be constrained.
    Param length_; ///< Target length.

public:
    /// @brief Constructs constraint for a line with a specified length.
    /// @param line The line.
    /// @param length Target length.
    LineLengthConstraint(const Line& line, const Param& length)
        : Constraint(std::make_unique<LineLengthErrorFunction>()),
        line_(line), length_(length)
    {}

    std::vector<Param> parameters() const override
    {
        auto lineParams = line_.parameters();
        if(lineParams.size() != 4)
        {
            throw std::runtime_error("Invalid line parameters: expected 4 parameters (x1, y1, x2, y2)");
        }
        // Order: line(x1, y1, x2, y2), length
        std::vector<Param> params = {
            lineParams[0], // line x1
            lineParams[1], // line y1
            lineParams[2], // line x2
            lineParams[3]  // line y2
        };
        params.push_back(length_);
        return params;
    }

    bool isValid() const override
    {
        return line_.isValid() && length_.isValid();
    }
};

} // namespace ssr

#endif // LineLengthConstraint_H