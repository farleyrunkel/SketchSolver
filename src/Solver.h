#ifndef SKETCHSOLVER_CONSTRAINTS_SOLVER_H
#define SKETCHSOLVER_CONSTRAINTS_SOLVER_H


#include <vector>
#include <memory>
#include <map>
#include <set>

#include "Config.h"
#include "Constraint.h"
#include "Param.h"

namespace ssr  // SketchSolver
{

class Solver
{
protected:
    using ConstraintPtr = std::shared_ptr<Constraint>;

    std::vector<ConstraintPtr> constraints_;

    std::set<Param> mapset;
    std::map<ConstraintPtr, std::vector<Param>> constraintvars;
    std::map<Param, int> mapparms;
    std::map<size_t, std::vector<ConstraintPtr>> vecmap;
    std::vector<Param> myvec;
    size_t next_vector = 0;

public:
    double initialValue(size_t i)
    {
        return *myvec[i];
    }

    int variantSize() const
    {
        return myvec.size();
    }

    virtual double GetElement(size_t i) = 0;
    virtual void SetElement(size_t i, double v) = 0;
    virtual int solve() = 0;

    void Unload() 
    {	
        //For every item in mapparms, copy variable from vector into pointer
        for(auto it = mapparms.begin(); it != mapparms.end(); ++it)
        {
            int parm = (*it).second;
            Param location = (*it).first;
            *location = GetElement(parm);
        }
    }

    double computeError() {
		double totalError = 0.0;
		for(const auto& constraint : constraints_)
		{
			totalError += constraint->error();
		}
		return totalError;
    }

    double GetError(int i) { return constraints_[i]->error(); }
	double GetError(const ConstraintPtr& constraint)
	{
		auto it = std::find(constraints_.begin(), constraints_.end(), constraint);
		if(it != constraints_.end())
		{
			return (*it)->error();
		}
		return 0.0; // or throw an exception
	}

	void LoadConstraint(const std::shared_ptr<Constraint>& constraint) 
    {
		auto params = constraint->parameters();
        std::vector<Param> vecs;
        for(const auto& param : params)
        {
			LoadParam(constraint, param, vecs);
        }
		constraintvars[constraint] = vecs;
		constraints_.push_back(constraint);
    }

    double GetErrorForGrad(int i)
    {
        double error = 0;
        for(unsigned int j = 0; j < vecmap[i].size(); j++)
        {
            error += GetError(vecmap[i][j]);
        }
        return error;
    }

    double GetGradient(int i, double pert)
    {
        double OldValue = GetElement(i);
        SetElement(i, OldValue - pert);
        double e1 = GetErrorForGrad(i);
        SetElement(i, OldValue + pert);
        double e2 = GetErrorForGrad(i);
        SetElement(i, OldValue);
        return 0.5 * (e2 - e1) / pert;
    }

private:
    void LoadParam(const std::shared_ptr<Constraint>& c, const Param& param, std::vector<Param>& mylist)
    {
        if(param.isConstant())
        {
			mylist.push_back(param);
            return;
        }

        if(mapset.find(param) != mapset.end())
        {
			size_t index = mapparms[param];
            mylist.push_back(param);
			vecmap[index].push_back(c);
			return;
        }

        vecmap[next_vector].push_back(c);
        mylist.push_back(param);
		mapparms[param] = next_vector;
		mapset.insert(param);
        myvec.push_back(param);
        next_vector++;
    }
};

}
#endif // SKETCHSOLVER_CONSTRAINTS_SOLVER_H