#ifndef P2LDistanceErrorFunction_H
#define P2LDistanceErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for point-to-line distance constraint.
class P2LDistanceErrorFunction : public Function
{
private:
    static double p2LDistanceE(double lx, double ly, double dx, double dy, double px, double py)
    {
        double t = -(lx * dx - px * dx + ly * dy - py * dy) / (dx * dx + dy * dy);
        double Xint = lx + dx * t;
        double Yint = ly + dy * t;
        return std::sqrt((px - Xint) * (px - Xint) + (py - Yint) * (py - Yint));
    }

public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 7)
        {
            throw std::invalid_argument("P2LDistanceError requires 7 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        double rad = *params[6];
        double temp = p2LDistanceE(
            *params[0], *params[1],
            dx, dy,
            *params[4], *params[5]
        ) - std::sqrt(rad * rad);
        return temp * temp * 100.0;
    }
};

}

#endif // P2LDistanceErrorFunction_H