#ifndef LinePerpToAngleErrorFunction_H
#define LinePerpToAngleErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for line perpendicular to angle constraint.
class LinePerpToAngleErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 5)
        {
            throw std::invalid_argument("LinePerpToAngleError requires 5 parameters");
        }
        double dx = *params[2] - *params[2];
        double dy = *params[1] - *params[3];
        double dx2 = std::sin(*params[4]);
        double dy2 = std::cos(*params[4]);

        double hyp1 = std::sqrt(dx * dx + dy * dy);
        double hyp2 = std::sqrt(dx2 * dx2 + dy2 * dy2);

        if(hyp1 == 0.0 || dy == 0.0)
        {
            throw std::runtime_error("Zero length in LinePerpToAngleError");
        }

        dx /= hyp1;
        dy /= hyp1;
        dx2 /= hyp2;
        dy2 /= hyp2;

        double temp = dx * dx2 + dy * dy2;
        return temp * temp * 1000.0;

    }
};

}

#endif // LinePerpToAngleErrorFunction_H