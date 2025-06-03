#ifndef P2LDistanceHorzErrorFunction_H
#define P2LDistanceHorzErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for horizontal point-to-line distance constraint.
class P2LDistanceHorzErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 7)
        {
            throw std::invalid_argument("P2LDistanceHorzError requires 7 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        double t = (*params[5] - *params[1]) / dy;
        double Xint = *params[0] + dx * t;
        double temp = std::abs(*params[4] - Xint) - *params[6];
        return temp * temp / 10.0;
    }
};

}

#endif // P2LDistanceHorzErrorFunction_H