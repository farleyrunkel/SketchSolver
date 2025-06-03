#ifndef SKETCHSOLVER_CONSTRAINTS_SOLVER_H
#define SKETCHSOLVER_CONSTRAINTS_SOLVER_H

#include "Config.h"
#include "Constraint.h"
#include <vector>
#include <memory>
#include <map>
#include <set>

// 求解器实现基类
class Solver
{
protected:
    using ConstraintPtr = std::unique_ptr<Constraint>;
    std::vector<ConstraintPtr> constraints_;
    std::vector<std::vector<std::pair<VarLocation, double*>>> constraintVars_;
    std::vector<double*> vecParams_;
    std::map<double*, std::pair<VarLocation, size_t>> paramMap_;
    std::set<double*> paramSet_;
    std::vector<double> paramVec_;
    std::map<size_t, std::vector<size_t>> vecMap_;
    size_t nextVector_ = 0;
    std::map<double*, int> parms_;

    void loadDouble(std::vector<std::pair<VarLocation, double*>>& list, double* d, size_t c);
    void loadPoint(std::vector<std::pair<VarLocation, double*>>& list, const Point& p, size_t c);
    void loadLine(std::vector<std::pair<VarLocation, double*>>& list, const Line& l, size_t c);
    double getErrorForGrad(size_t i);

public:
    Solver();
    virtual ~Solver() = default;

    void load(const std::vector<std::unique_ptr<Constraint>>& constraints, const std::vector<double*>& params);
    void unload();
    double getError() const;
    double getError(size_t i) const;
    size_t getVectorSize() const;
    double getInitialValue(size_t i) const;
    double getGradient(size_t i, double pert);
    virtual double getElement(size_t i) const = 0;
    virtual void setElement(size_t i, double v) = 0;
    virtual SolveStatus solve(std::vector<double>& x, bool isFine) = 0;
};

#endif // SKETCHSOLVER_CONSTRAINTS_SOLVER_H