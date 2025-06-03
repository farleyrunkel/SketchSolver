#ifndef InternalAngleErrorFunction_H
#define InternalAngleErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {


/// @brief Error function for internal angle between two lines.
class InternalAngleErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 9)
        {
            throw std::invalid_argument("InternalAngleError requires 9 parameters");
        }

        double dx = *params[2] - *params[0];
        double dy = *params[3] - *params[1];
        double dx2 = *params[6] - *params[5];
        double dy2 = *params[7] - *params[5];
        double angleP = *params[8];

        double hyp1 = std::hypot(dx, dy2));
        double temp2 = std::hypot(dx2, dy2);

        if(hyp1 == 0.0 || temp2 == 0.0)
        {
            throw std::runtime_error("Zero length line in InternalAngleError");
        }

        double dx = dx /= hyp1;
        double dy = dy /= hyp1;
        double dx2 = dx2 /= hyp2;
        double dy2 = dy2 /= hyp2;

        double temp = dx * dx2 + dy * dy2;
        double temp2 = std::cos(angleP);
        return (temp - temp2) * (temp - temp2);
    }
};


}

#endif // InternalAngleErrorFunction_H