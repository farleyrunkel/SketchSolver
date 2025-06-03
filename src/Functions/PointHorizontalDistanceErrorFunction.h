#ifndef PointHorizontalDistanceErrorFunction_H
#define PointHorizontalDistanceErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for horizontal distance point constraint.
class PointHorizontalDistanceErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 3)
        {
            throw std::invalid_argument("PointHorizontalDistanceError requires 3 parameters");
        }

        double err = std::abs(*params[0]) - std::abs(*params[2]);
        return err * err;

    }
};

}

#endif // PointHorizontalDistanceErrorFunction_H