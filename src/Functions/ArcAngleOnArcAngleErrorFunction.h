#ifndef ArcAngleOnArcAngleErrorFunction_H
#define ArcAngleOnArcAngleErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for arc angle on arc angle constraint.
class ArcAngleOnArcAngleErrorFunction : public {
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 8)
        {
            throw std::invalid_argument("ArcAngleOnArcError requires 8 parameters");
        }
        double a1x = std::sin(*params[3]) * *params[2] + *params[0];
        double a1y = std::cos(*params[3]) * *params[2] + *params[1];
        double a2x = std::sin(*params[7]) * *params[6] + *params[4];
        double a2y = std::cos(*params[7]) * *params[6] + *params[5];
        double dx = a2x - a1x;
        double dy = a2y - a1y;
        return dx * dx + dy * dy;
    }
};

}  // namespace ssr

#endif // ArcAngleOnArcAngleErrorFunction_H