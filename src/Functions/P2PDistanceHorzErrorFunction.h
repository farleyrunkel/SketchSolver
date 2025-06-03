#ifndef P2PDistanceHorzErrorFunction_H
#define P2PDistanceHorzErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for horizontal point-to-point distance constraint.
class P2PDistanceHorzErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 5)
        {
            throw std::invalid_argument("P2PDistanceHorzError requires 5 parameters");
        }
        double dx = *params[0] - *params[2];
        double d = *params[4];
        double err = dx * dx - d * d;
        return err * err;
    }
};

}

#endif // P2PDistanceHorzErrorFunction_H