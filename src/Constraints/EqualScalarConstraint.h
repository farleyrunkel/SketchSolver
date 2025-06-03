#ifndef EqualScalarConstraint_H
#define EqualScalarConstraint_H

#include <cmath>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"

namespace ssr
{

class EqualScalarErrorFunction;

/// @brief Constraint for ensuring two scalar parameters are equal.
class EqualScalarConstraint : public Constraint
{
private:
    Param scalar1_; ///< First scalar parameter.
    Param scalar2_; ///< Second scalar parameter.

public:
    /// @brief Constructs constraint for two scalar parameters to be equal.
    /// @param scalar1 First scalar parameter.
    /// @param scalar2 Second scalar parameter.
    EqualScalarConstraint(const Param& scalar1, const Param& scalar2)
        : Constraint(std::make_unique<EqualScalarErrorFunction>()),
        scalar1_(scalar1), scalar2_(scalar2)
    {}

    std::vector<Param> parameters() const override
    {
        std::vector<Param> params = {scalar1_, scalar2_};
        return params;
    }

    bool isValid() const override
    {
        return scalar1_.isValid() && scalar2_.isValid();
    }
};

} // namespace ssr

#endif // EqualScalarConstraint_H