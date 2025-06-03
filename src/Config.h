#ifndef SKETCHSOLVER_CONFIG_H
#define SKETCHSOLVER_CONFIG_H

#include <string>

namespace ssr
{

constexpr double Pi = 3.14159265358979323846;

constexpr double pertMag = 1e-6;
constexpr double pertMin = 1e-10;
constexpr double XconvergenceRough = 1e-8;
constexpr double XconvergenceFine = 1e-10;
constexpr double smallF = 1e-20;
constexpr double validSolutionFine = 1e-12;
constexpr double validSoltuionRough = 1e-4;
constexpr int MaxIterations = 50;

}

#endif // SKETCHSOLVER_CONFIG_H
