#ifndef PointOnPointErrorFunction_H
#define PointOnPointErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for point-on-point constraint.
class PointOnPointErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 4)
        {
            throw std::invalid_argument("PointOnPointError requires 4 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        return dx * dx + dy * dy;
    }
};

}

#endif // PointOnPointErrorFunction_H