#ifndef EqualLengthConstraint_H
#define EqualLengthConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class EqualLengthErrorFunction;

/// @brief Constraint for ensuring two lines have equal lengths.
class EqualLengthConstraint : public Constraint
{
private:
    Line line1_; ///< First line.
    Line line2_; ///< Second line.

public:
    /// @brief Constructs constraint for two lines to have equal lengths.
    /// @param line1 First line.
    /// @param line2 Second line.
    EqualLengthConstraint(const Line& line1, const Line& line2)
        : Constraint(std::make_unique<EqualLengthErrorFunction>()),
        line1_(line1), line2_(line2)
    {}

    std::vector<Param> parameters() const override
    {
        auto params1 = line1_.parameters();
        auto params2 = line2_.parameters();
        if(params1.size() != 4 || params2.size() != 4)
        {
            throw std::runtime_error("Invalid line parameters: expected 4 parameters (x1, y1, x2, y2)");
        }
        // Order: line1(x1, y1, x2, y2), line2(x1, y1, x2, y2)
        std::vector<Param> params = {
            params1[0], // line1 x1
            params1[1], // line1 y1
            params1[2], // line1 x2
            params1[3]  // line1 y2
        };
        params.insert(params.end(), {
            params2[0], // line2 x1
            params2[1], // line2 y1
            params2[2], // line2 x2
            params2[3]  // line2 y2
                      });
        return params;
    }

    bool isValid() const override
    {
        return line1_.isValid() && line2_.isValid();
    }
};

} // namespace ssr

#endif // EqualLengthConstraint_H
