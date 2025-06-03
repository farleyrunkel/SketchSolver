#ifndef SKETCHSOLVER_SEGMENT_H
#define SKETCHSOLVER_SEGMENT_H

#include <memory>
#include <stdexcept>
#include <vector>

#include "Param.h"

namespace ssr
{

/// @brief Abstract base class for geometric segments.
class Segment
{
public:
    /// @brief Virtual destructor for polymorphism.
    virtual ~Segment() = default;

    /// @brief Checks if the segment is valid.
    virtual bool isValid() const noexcept = 0;

    /// @brief Gets all parameters of the segment.
    virtual std::vector<Param> parameters() const = 0;
};

} // namespace ssr

#endif // SKETCHSOLVER_SEGMENT_H