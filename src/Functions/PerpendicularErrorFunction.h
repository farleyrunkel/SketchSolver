#ifndef PerpendicularErrorFunction_H
#define PerpendicularErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for perpendicular constraint between two lines.
class PerpendicularErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 8)
        {
            throw std::invalid_argument("PerpendicularError requires 8 parameters");
        }
        double dx = *params[2] - *params[0];
        double dy = *params[3] - *params[1];
        double dx2 = *params[6] - *params[4];
        double dy2 = *params[7] - *params[5];

        double hyp1 = std::sqrt(dx * dx + dy * dy);
        double hyp2 = std::sqrt(dx2 * dx2 + dy2 * dy2);

        if(hyp1 == 0.0 || hyp2 == 0.0)
        {
            throw std::runtime_error("Zero length line in PerpendicularError");
        }

        dx /= hyp1;
        dy /= hyp1;
        dx2 /= hyp2;
        dy2 /= hyp2;

        double temp = dx * dx2 + dy * dy2;
        return temp * temp * 10.0;
    }
};


}

#endif // PerpendicularErrorFunction_H