#ifndef SKETCHSOLVER_FUNCTION_H
#define SKETCHSOLVER_FUNCTION_H

#include <vector>

#include "Param.h"

namespace ssr  // SketchSolver
{

class Function
{
public:
    /// @brief Virtual destructor for polymorphism.
    virtual ~Function() = default;

    /// @brief Computes the error for the constraint.
    /// @param params List of parameters involved in the constraint.
    /// @return The error value (typically non-negative).
    virtual double error(const std::vector<Param>& params) const = 0;
};

} // namespace ssr

#endif // SKETCHSOLVER_FUNCTION_H
