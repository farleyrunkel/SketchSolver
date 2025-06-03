#ifndef EqualLengthErrorFunction_H
#define EqualLengthErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for equal length constraint between two lines.
class EqualLengthErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 8)
        {
            throw std::invalid_argument("EqualLengthError requires 8 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        double dx2 = *params[4] - *params[6];
        double dy2 = *params[5] - *params[7];
        double temp = std::sqrt(dx * dx + dy * dy) - std::sqrt(dx2 * dx2 + dy2 * dy2);
        return temp * temp;
    }
};
}

#endif // EqualLengthErrorFunction_H