#ifndef SKETCHSOLVER_CONSTRAINTS_GEOMETRY_H
#define SKETCHSOLVER_CONSTRAINTS_GEOMETRY_H

#include <memory>
#include <stdexcept>
#include <functional>

namespace ssr
{

/// @brief Encapsulates a double* with safe access and constant flag.
class Param
{
private:
    double* value_ = nullptr;   ///< Pointer to the parameter value.
    bool isConst_ = false;      ///< Indicates if the parameter is constant (immutable).

public:
    /// @brief Default constructor, initializes to nullptr and non-constant.
    Param() noexcept = default;

    /// @brief Constructs Param from a double pointer.
    explicit Param(double* v, bool isConst = false) noexcept
        : value_(v), isConst_(isConst)
    {}

    /// @brief Constructs Param from a double value (allocated internally).
    explicit Param(double v, bool isConst = false)
        : value_(new double(v)), isConst_(isConst)
    {}

    /// @brief Copy constructor (deep copy if valid).
    Param(const Param& other)
        : value_(other.isValid() ? new double(*other.value_) : nullptr),
        isConst_(other.isConst_)
    {}

    /// @brief Move constructor.
    Param(Param&& other) noexcept
        : value_(other.value_), isConst_(other.isConst_)
    {
        other.value_ = nullptr;
        other.isConst_ = false;
    }

    /// @brief Destructor.
    ~Param() = default;

    /// @brief Copy assignment.
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
            isConst_ = other.isConst_;
        }
        return *this;
    }

    /// @brief Move assignment.
    Param& operator=(Param&& other) noexcept
    {
        if(this != &other)
        {
            value_ = other.value_;
            isConst_ = other.isConst_;
            other.value_ = nullptr;
            other.isConst_ = false;
        }
        return *this;
    }

    /// @brief Assigns a double value.
    Param& operator=(double v)
    {
        if(!isValid()) throw std::runtime_error("Cannot assign to invalid Param");
        if(isConst_) throw std::runtime_error("Cannot assign to constant Param");
        *value_ = v;
        return *this;
    }

    /// @brief Checks if pointer is valid.
    bool isValid() const noexcept { return value_ != nullptr; }

    /// @brief Raw pointer access.
    explicit operator double* () const noexcept { return value_; }

    /// @brief Dereference with check.
    double& operator*() const
    {
        if(!isValid()) throw std::runtime_error("Invalid Param dereference");
        return *value_;
    }

    /// @brief Reference conversion.
    operator double& () const
    {
        if(!isValid()) throw std::runtime_error("Invalid Param dereference");
        return *value_;
    }

    /// @brief Value conversion.
    operator double() const
    {
        if(!isValid()) throw std::runtime_error("Invalid Param dereference");
        return *value_;
    }

    /// @brief Equality (by address).
    bool operator==(const Param& other) const noexcept { return value_ == other.value_; }

    /// @brief Inequality (by address).
    bool operator!=(const Param& other) const noexcept { return value_ != other.value_; }

    /// @brief Strict weak ordering for map/set.
    bool operator<(const Param& other) const noexcept
    {
        return value_ < other.value_;
    }

    /// @brief Whether the parameter is constant.
    bool isConstant() const noexcept { return isConst_; }

    /// @brief Sets constant flag.
    void setConstant(bool isConst = true) noexcept { isConst_ = isConst; }

    /// @brief Returns underlying raw pointer for hashing.
    double* rawPtr() const noexcept { return value_; }
};

} // namespace ssr

/// @brief Custom hash function for Param (for unordered_map/set)
namespace std
{
template <>
struct hash<ssr::Param>
{
    std::size_t operator()(const ssr::Param& p) const noexcept
    {
        return std::hash<double*>{}(p.rawPtr());
    }
};
}

#endif // SKETCHSOLVER_CONSTRAINTS_GEOMETRY_H
