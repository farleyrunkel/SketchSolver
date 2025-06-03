#ifndef P2PDistanceVertErrorFunction_H
#define P2PDistanceVertErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for vertical point-to-point distance constraint.
class P2PDistanceVertErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 5)
        {
            throw std::invalid_argument("P2PDistanceVertError requires 5 parameters");
        }
        double dy = *params[1] - *params[3];
        double d = *params[4];
        double err = dy * dy - d * d;
        return err * err;
    }
};


}

#endif // P2PDistanceVertErrorFunction_H