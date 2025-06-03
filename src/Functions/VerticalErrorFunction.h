#ifndef VerticalErrorFunction_H
#define VerticalErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for vertical line constraint.
class VerticalErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 4)
        {
            throw std::invalid_argument("VerticalError requires 4 parameters");
        }
        double odx = *params[2] - *params[0];
        return odx * odx * 1000.0;
    }
};


}

#endif // VerticalErrorFunction_H