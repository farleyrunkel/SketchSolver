#ifndef SKETCHSOLVER_CONSTRAINTS_dasdSOLVER_H
#define SKETCHSOLVER_CONSTRAINTS_dasdSOLVER_H

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../Config.h"
#include "../Constraint.h"
#include "../Solver.h"

// 求解器类
class BFGSSolver : public Solver
{
    std::vector<double> x_;
    std::vector<double> origSolution_;
    std::vector<double> grad_;
    std::vector<double> s_;
    std::vector<std::vector<double>> n_;
    std::vector<double> xOld_;
    std::vector<double> deltaX_;
    std::vector<double> gradNew_;
    std::vector<double> gamma_;
    std::vector<double> gammatDotN_;
    std::vector<std::vector<double>> firstSecond_;
    std::vector<std::vector<double>> deltaXDotGammatDotN_;
    std::vector<std::vector<double>> gammatDotDeltaXt_;
    std::vector<std::vector<double>> nDotGammaDotDeltaXt_;

    void allocate(size_t xLength);
    SolveStatus solveImpl(std::vector<double>& x, bool isFine);

public:
    BFGSSolver();
    ~BFGSSolver() override = default;

    SolveStatus solve(std::vector<double>& x, bool isFine) override;
    double getElement(size_t i) const override { return x_[i]; }
    void setElement(size_t i, double v) override { x_[i] = v; }
};

#endif // SKETCHSOLVER_CONSTRAINTS_dasdSOLVER_H