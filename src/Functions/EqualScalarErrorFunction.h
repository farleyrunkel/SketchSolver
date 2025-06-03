#ifndef EqualScalarErrorFunction_H
#define EqualScalarErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for equal scalar constraint.
class EqualScalarErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 2)
        {
            throw std::invalid_argument("EqualScalarError requires 2 parameters");
        }
        double temp = *params[0] - *params[1];
        return temp * temp;
    }
};

}

#endif // EqualScalarErrorFunction_H