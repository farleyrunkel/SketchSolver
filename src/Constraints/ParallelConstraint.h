#ifndef ParallelConstraint_H
#define ParallelConstraint_H

#include <memory>
#include <vector>

#include "../Constraint.h"
#include "../Param.h"
#include "../Segments/Line.h"

namespace ssr
{

class ParallelErrorFunction;

/// @brief Constraint enforcing two lines to be parallel.
class ParallelConstraint : public Constraint
{
private:
    Line line1_, line2_;

public:
    ParallelConstraint(const Line& line1, const Line& line2)
        : Constraint(std::make_unique<ParallelErrorFunction>()), line1_(line1), line2_(line2)
    {}

    std::vector<Param> parameters() const override
    {
        auto params = line1_.parameters();
        auto params2 = line2_.parameters();
        params.insert(params.end(), params2.begin(), params2.end());
        return params;
    }
    /// @brief Checks if a parameter is variant.
    virtual bool isVariant(int i) const 
    {
		// Assuming both lines are defined by 4 parameters each (x1, y1, x2, y2)
		return i < 8 && i >= 0; // First 8 parameters correspond to the two lines
    }

    bool isValid() const override
    {
        return line1_.isValid() && line2_.isValid();
    }
};

}

#endif // ParallelConstraint_H
