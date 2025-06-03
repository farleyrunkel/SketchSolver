#ifndef ExternalAngleErrorFunction_H
#define ExternalAngleErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for external angle between two lines.
class ExternalAngleErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 9)
        {
            throw std::invalid_argument("ExternalAngleError requires 9 parameters");
        }
        double dx = *params[2] - *params[0];
        double dy = *params[3] - *params[1];
        double dx2 = *params[6] - *params[4];
        double dy2 = *params[7] - *params[5];
        double angleP = *params[8];

        double hyp1 = std::hypot(dx, dy);
        double hyp2 = std::hypot(dx2, dy2);

        if(hyp1 == 0.0 || hyp2 == 0.0)
        {
            throw std::runtime_error("Zero length line in ExternalAngleError");
        }

        dx /= hyp1;
        dy /= hyp1;
        dx2 /= hyp2;
        dy2 /= hyp2;

        double temp = dx * dx2 - dy * dy2;
        double temp2 = std::cos(M_PI - angleP);
        return (temp - temp2) * (temp - temp2);
    }
};

} // namespace ssr

#endif // ExternalAngleErrorFunction_H