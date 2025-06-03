#ifndef P2PDistanceErrorFunction_H
#define P2PDistanceErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for point-to-point distance constraint.
class P2PDistanceErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 5)
        {
            throw std::invalid_argument("P2PDistanceError requires 5 parameters");
        }
        double dx = *params[0] - *params[2];
        double dy = *params[1] - *params[3];
        double d = *params[4];
        double err = dx * dx + dy * dy - d * d;
        return err * err;
    }
};

}

#endif // P2PDistanceErrorFunction_H