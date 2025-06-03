#ifndef P2LDistanceVertErrorFunction_H
#define P2LDistanceVertErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for vertical point-to-line distance constraint.
class P2LDistanceVertErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 7)
        {
            throw std::invalid_argument("P2LDistanceVertError requires 7 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        double t = (*params[4] - *params[0]) / dx;
        double Yint = *params[1] + dy * t;
        double temp = std::abs(*params[5] - Yint) - *params[6];
        return temp * temp;
    }
};

}

#endif // P2LDistanceVertErrorFunction_H