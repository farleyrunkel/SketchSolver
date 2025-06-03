#ifndef EllipseTangentConstraint_H
#define EllipseTangentConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"
#include "../Segments/Ellipse.h"

namespace ssr
{

class EllipseTangentErrorFunction;

/// @brief Constraint for a line to be tangent to an ellipse.
class EllipseTangentConstraint : public Constraint
{
private:
    Line line_; ///< Line to be tangent.
    Ellipse ellipse_; ///< Ellipse to be tangent to.

public:
    /// @brief Constructs constraint for a line tangent to an ellipse.
    /// @param line The line.
    /// @param ellipse The ellipse.
    EllipseTangentConstraint(const Line& line, const Ellipse& ellipse)
        : Constraint(std::make_unique<EllipseTangentErrorFunction>()),
        line_(line), ellipse_(ellipse)
    {}

    std::vector<Param> parameters() const override
    {
        auto lineParams = line_.parameters();
        auto ellipseParams = ellipse_.parameters();
        if(lineParams.size() != 4 || ellipseParams.size() != 5)
        {
            throw std::runtime_error("Invalid parameters: expected 4 for line (x1, y1, x2, y2) and 5 for ellipse (ex, ey, majr, minr, rot)");
        }
        // Order: line(x1, y1, x2, y2), ellipse(ex, ey, majr, minr, rot)
        std::vector<Param> params = {
            lineParams[0], // line x1
            lineParams[1], // line y1
            lineParams[2], // line x2
            lineParams[3]  // line y2
        };
        params.insert(params.end(), {
            ellipseParams[0], // ellipse center x
            ellipseParams[1], // ellipse center y
            ellipseParams[2], // ellipse major radius
            ellipseParams[3], // ellipse minor radius
            ellipseParams[4]  // ellipse rotation
                      });
        return params;
    }

    bool isValid() const override
    {
        return line_.isValid() && ellipse_.isValid();
    }
};

} // namespace ssr

#endif // EllipseTangentConstraint_H