#ifndef LineLengthErrorFunction_H
#define LineLengthErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for line length constraint.
class LineLengthErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 5)
        {
            throw std::invalid_argument("LineLengthError requires 5 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        double temp = std::sqrt(dx * dx + dy * dy) - *params[4];
        return temp * temp * 100.0;
    }
};


}

#endif // LineLengthErrorFunction_H