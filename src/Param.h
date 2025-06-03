#ifndef SKETCHSOLVER_CONSTRAINTS_GEOMETRY_H
#define SKETCHSOLVER_CONSTRAINTS_GEOMETRY_H

#include <memory>
#include <stdexcept>

namespace ssr
{

/// @brief Encapsulates a double* with safe access and default initialization.
class Param
{
private:
    double* value_ = nullptr; ///< Pointer to the parameter value.

public:
    /// @brief Default constructor, initializes to nullptr.
    Param() = default;

    /// @brief Constructs Param from a double pointer.
    /// @param v Pointer to a double value, or nullptr.
    explicit Param(double* v) noexcept : value_(v) {}

    /// @brief Constructs Param from a double value, allocating new memory.
    explicit Param(double v) : value_(new double(v)) {}

    /// @brief Copy constructor, creates a new copy of the value.
    Param(const Param& other) : value_(other.isValid() ? new double(*other.value_) : nullptr) {}

    /// @brief Move constructor, transfers ownership.
    Param(Param&& other) noexcept : value_(other.value_)
    {
        other.value_ = nullptr;
    }

    /// @brief Destructor, does not delete value (external management).
    ~Param() = default;

    /// @brief Copy assignment, creates a new copy of the value.
    Param& operator=(const Param& other)
    {
        if(this != &other)
        {
            if(other.isValid())
            {
                if(!value_) value_ = new double;
                *value_ = *other.value_;
            }
            else
            {
                value_ = nullptr;
            }
        }
        return *this;
    }

    /// @brief Move assignment, transfers ownership.
    Param& operator=(Param&& other) noexcept
    {
        if(this != &other)
        {
            value_ = other.value_;
            other.value_ = nullptr;
        }
        return *this;
    }

    /// @brief Assigns a double value to the pointed memory.
    /// @throws std::runtime_error if value is nullptr.
    Param& operator=(double v)
    {
        if(!isValid()) throw std::runtime_error("Cannot assign to invalid Param");
        *value_ = v;
        return *this;
    }

    /// @brief Checks if the pointer is valid.
    bool isValid() const noexcept { return value_ != nullptr; }

    /// @brief Converts to raw double* for compatibility.
    explicit operator double* () const noexcept { return value_; }

	/// @brief Dereferences the pointer, with safety check.
	/// @throws std::runtime_error if value is nullptr.
	double& operator*() const
	{
		if(!isValid()) throw std::runtime_error("Invalid Param dereference");
		return *value_;
	}

    /// @brief Converts to double reference, with safety check.
    /// @throws std::runtime_error if value is nullptr.
    operator double& () const
    {
        if(!isValid()) throw std::runtime_error("Invalid Param dereference");
        return *value_;
    }

    /// @brief Converts to double value, with safety check.
    /// @throws std::runtime_error if value is nullptr.
    operator double() const
    {
        if(!isValid()) throw std::runtime_error("Invalid Param dereference");
        return *value_;
    }

    /// @brief Equality comparison based on pointer address.
    bool operator==(const Param& other) const noexcept { return value_ == other.value_; }

    /// @brief Inequality comparison based on pointer address.
    bool operator!=(const Param& other) const noexcept { return value_ != other.value_; }
};

} // namespace SketchSolver

#endif // SKETCHSOLVER_CONSTRAINTS_GEOMETRY_H
