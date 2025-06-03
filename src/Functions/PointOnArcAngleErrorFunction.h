#ifndef PointOnArcAngleErrorFunction_H
#define PointOnArcAngleErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for point on arc angle constraint.
class PointOnArcAngleErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 6)
        {
            throw std::invalid_argument("PointOnArcAngleError requires 6 parameters");
        }
        double a1x = std::sin(*params[5]) * *params[4] + *params[2];
        double a1y = std::cos(*params[5]) * *params[4] + *params[3];
        double dx = *params[0] - a1x;
        double dy = *params[1] - a1y;
        return dx * dx + dy * dy;
    }
};

}

#endif // PointOnArcAngleErrorFunction_H