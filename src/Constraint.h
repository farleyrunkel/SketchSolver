#ifndef SKETCHSOLVER_CONSTRAINTS_CONSTRAINT_H
#define SKETCHSOLVER_CONSTRAINTS_CONSTRAINT_H

#include <memory>
#include <stdexcept>
#include <vector>

#include "Param.h"
#include "Point.h"
#include "Function.h"
#include "Segment.h"

namespace ssr // SketchSolver
{

/// @brief Abstract base class for constraints in the solver.
class Constraint
{
protected:
    std::unique_ptr<Function> errorFunction_; ///< Error computation strategy.

public:
    /// @brief Constructs a Constraint with an error function.
    /// @param errorFunction The error computation strategy.
    explicit Constraint(std::unique_ptr<Function> errorFunction)
        : errorFunction_(std::move(errorFunction))
    {}

    /// @brief Virtual destructor for polymorphism.
    virtual ~Constraint() = default;

    /// @brief Computes the error of the constraint using the error function.
    /// @return The error value (typically non-negative).
    /// @throws std::runtime_error if errorFunction_ is null.
    double error() const
    {
        if(!errorFunction_)
        {
            throw std::runtime_error("No error function defined");
        }
        return errorFunction_->error(parameters());
    }

    /// @brief Gets the parameters involved in the constraint.
    /// @return Vector of parameters.
    virtual std::vector<Param> parameters() const = 0;

	/// @brief Checks if a parameter is variant.
    virtual void checkPrameters() { return; }

    /// @brief Checks if the constraint is valid.
    /// @return True if all parameters are valid.
    virtual bool isValid() const = 0;

    /// @brief Sets a new error function.
    /// @param errorFunction The new error computation strategy.
    void setErrorFunction(std::unique_ptr<Function> errorFunction)
    {
        errorFunction_ = std::move(errorFunction);
    }
};

} // namespace ssr

#endif // SKETCHSOLVER_CONSTRAINTS_CONSTRAINT_H