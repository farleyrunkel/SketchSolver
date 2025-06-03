#ifndef PointVerticalDistanceErrorFunction_H
#define PointVerticalDistanceErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for vertical distance point error constraint.
class PointVerticalDistanceErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 3)
        {
            throw std::invalid_argument("PointVerticalDistanceError requires 3 parameters");
        }

        double err = std::abs(*params[1]) - std::abs(*params[2]);
        return err * err;

    }
};
}

#endif // PointVerticalDistanceErrorFunction_H