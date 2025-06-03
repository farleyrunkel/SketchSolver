#ifndef EllipseTangentErrorFunction_H
#define EllipseTangentErrorFunction_H

#include <cmath>
#include <vector>

#include "../Function.h"
#include "../Param.h"

namespace ssr {

/// @brief Error function for ellipse tangent constraint.
class EllipseTangentErrorFunction : public Function
{
public:
    double error(const std::vector<Param>& params) const override
    {
        if(params.size() != 9)
        {
            throw std::invalid_argument("EllipseTangentError requires 9 parameters");
        }
        double ex = *params[4];
        double ey = *params[5];
        double majr = *params[6];
        double minr = *params[7];
        double rot = *params[8];

        // Adjust major and minor axes
        double adjusted_majr = minr;
        double adjusted_minr = majr;
        double adjusted_rot = -rot;

        // Rotate line around ellipse
        double lx1 = std::cos(adjusted_rot) * (*params[0] - ex) -
            std::sin(adjusted_rot) * (*params[1] - ey);
        double ly1 = std::sin(adjusted_rot) * (*params[0] - ex) +
            std::cos(adjusted_rot) * (*params[1] - ey);
        double lx2 = std::cos(adjusted_rot) * (*params[2] - ex) -
            std::sin(adjusted_rot) * (*params[3] - ey);
        double ly2 = std::sin(adjusted_rot) * (*params[2] - ex) +
            std::cos(adjusted_rot) * (*params[3] - ey);

        double ldx = lx1 - lx2;
        double ldy = ly1 - ly2;

        double g = (2.0 * ldx * lx1) / (adjusted_majr * adjusted_majr) +
            (2.0 * ldy * ly1) / (adjusted_minr * adjusted_minr);
        double det = g * g - 4.0 * (ldx * ldx / (adjusted_majr * adjusted_majr) +
                                    ldy * ldy / (adjusted_minr * adjusted_minr)) *
            (lx1 * lx1 / (adjusted_majr * adjusted_majr) +
             ly1 * ly1 / (adjusted_minr * adjusted_minr) - 1.0);

        return det * det * 10.0;
    }
};

}

#endif // EllipseTangentErrorFunction_H