#ifndef ArcStartToArcStartConstraint_H
#define ArcStartToArcStartConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Arc.h"

namespace ssr
{

class ArcStartToArcStartErrorFunction;

/// @brief Constraint for aligning start endpoints of two arcs.
class ArcStartToArcStartConstraint : public Constraint
{
private:
    Arc arc1_; ///< First arc.
    Arc arc2_; ///< Second arc.
    bool useStart1_; ///< Use start angle of first arc (true) or end angle (false).
    bool useStart2_; ///< Use start angle of second arc (true) or end angle (false).

public:
    /// @brief Constructs constraint for two arcs' start endpoints.
    /// @param arc1 First arc.
    /// @param arc2 Second arc.
    /// @param useStart1 True to use arc1's start angle, false for end angle.
    /// @param useStart2 True to use arc2's start angle, false for end angle.
    ArcStartToArcStartConstraint(const Arc& arc1, const Arc& arc2, bool useStart1 = true, bool useStart2 = true)
        : Constraint(std::make_unique<ArcStartToArcStartErrorFunction>()),
        arc1_(arc1), arc2_(arc2), useStart1_(useStart1), useStart2_(useStart2)
    {}

    std::vector<Param> parameters() const override
    {
        auto params1 = arc1_.parameters();
        auto params2 = arc2_.parameters();
        if(params1.size() != 5 || params2.size() != 5)
        {
            throw std::runtime_error("Invalid arc parameters: expected 5 parameters (cx, cy, r, startAngle, endAngle)");
        }
        // Order: arc1(cx, cy, r, startAngle), arc2(cx, cy, r, startAngle)
        std::vector<Param> params = {
            params1[0], // arc1 center x
            params1[1], // arc1 center y
            params1[2], // arc1 radius
            params1[3]  // arc1 start angle
        };
        params.insert(params.end(), {
            params2[0], // arc2 center x
            params2[1], // arc2 center y
            params2[2], // arc2 radius
            params2[3]  // arc2 start angle
                      });
        return params;
    }

    bool isValid() const override
    {
        return arc1_.isValid() && arc2_.isValid();
    }
};

} // namespace ssr

#endif // ArcStartToArcStartConstraint_H