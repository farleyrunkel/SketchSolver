#ifndef HorizontalErrorFunction_H
#define HorizontalErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for horizontal line constraint.
class HorizontalErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 4)
        {
            throw std::invalid_argument("HorizontalError requires 4 parameters");
        }
        double ody = *params[3] - *params[1];
        return ody * ody * 1000.0;
    }
};


}

#endif // HorizontalErrorFunction_H