#ifndef SKETCHSOLVER_CONFIG_H
#define SKETCHSOLVER_CONFIG_H

#include <string>

namespace ssr
{

constexpr double Pi = 3.14159265358979323846;

constexpr double PertMag = 1e-6;
constexpr double PertMin = 1e-10;
constexpr double XConvergenceRough = 1e-8;
constexpr double XConvergenceFine = 1e-10;
constexpr double SmallF = 1e-20;
constexpr double ValidSolutionFine = 1e-12;
constexpr double ValidSolutionRough = 1e-4;
constexpr int MaxIterations = 50;

}

#endif // SKETCHSOLVER_CONFIG_H
