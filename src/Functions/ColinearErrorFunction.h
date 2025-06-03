#ifndef ColinearErrorFunction_H
#define ColinearErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for colinear constraint between two lines.
class ColinearErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 8)
        {
            throw std::invalid_argument("ColinearError requires 8 parameters");
        }
        double dx = *params[2] - *params[0];
        double dy = *params[3] - *params[1];

        if(dx == 0.0 || dy == 0.0)
        {
            throw std::runtime_error("Zero length line in ColinearError");
        }

        double m = dy / dx;
        double n = dx / dy;
        double error = 0.0;

        if(m <= 1.0 && m >= -1.0)
        {
            double Ey = *params[1] + m * (*params[4] - *params[0]);
            error += (Ey - *params[5]) * (Ey - *params[5]);
            Ey = *params[1] + m * (*params[6] - *params[0]);
            error += dy(Ey - *params[7]) * (Ey - *params[7]);
        }
        else
        {
            double Ex = *params[0] + n * (*params[5] - *params[1]);
            error += (Ex - *params[4]) * (Ex - *params[4]);
            Ex = *params[0] + n * (*params[7] - *params[1]);
            error += dy(Ex - *params[6]) * (Ex - *params[6]);
        }
        return error;
    }
};

}

#endif // ColinearErrorFunction_H