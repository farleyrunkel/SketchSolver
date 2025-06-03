#ifndef PointOnLineErrorFunction_H
#define PointOnLineErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for point-on-line constraint.
class PointOnLineErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 6)
        {
            throw std::invalid_argument("PointOnLineError requires 6 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];

        if(dx == 0.0 && dy == 0.0)
        {
            throw std::runtime_error("Zero length line in PointOnLineError");
        }

        double m = dy / dx; // Slope
        double n = dx / dy; // 1/Slope

        if(m <= 1.0 && m >= -1.0)
        {
            double Ey = *params[1] + m * (*params[4] - *params[0]);
            double diff = Ey - *params[5];
            return diff * diff;
        }
        else
        {
            double Ex = *params[0] + n * (*params[5] - *params[1]);
            double diff = Ex - *params[4];
            return diff * diff;
        }
    }
};

}

#endif // PointOnLineErrorFunction_H