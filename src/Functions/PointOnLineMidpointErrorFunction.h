#ifndef PointOnLineMidpointErrorFunction_H
#define PointOnLineMidpointErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for point on line midpoint constraint.
class PointOnLineMidpointErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 6)
        {
            throw std::invalid_argument("PointOnLineMidpointError requires 6 parameters");
        }
        double dx = *params[4] - *params[0];
        double dy = *params[5] - *params[1];
        double dx2 = *params[2] - *params[4];
        double dy2 = *params[3] - *params[5];

        double e1 = dx2 - dx;
        double e2 = dy2 - dy;
        return e1 * e1 + e2 * e2;
    }
};

}

#endif // PointOnLineMidpointErrorFunction_H