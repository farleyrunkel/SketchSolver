#ifndef SKETCHSOLVER_SOLVER_H
#define SKETCHSOLVER_SOLVER_H


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

    virtual double element(size_t i) = 0;
    virtual void setElement(size_t i, double v) = 0;
    virtual int solve() = 0;

    void unload() 
    {	
        //For every item in mapparms, copy variable from vector into pointer
        for(auto it = mapparms.begin(); it != mapparms.end(); ++it)
        {
            int parm = (*it).second;
            Param location = (*it).first;
            *location = element(parm);
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

    double computeError(int i) { return constraints_[i]->error(); }
	double computeError(const ConstraintPtr& constraint)
	{
		auto it = std::find(constraints_.begin(), constraints_.end(), constraint);
		if(it != constraints_.end())
		{
			return (*it)->error();
		}
		return 0.0; // or throw an exception
	}

	void loadConstraint(const std::shared_ptr<Constraint>& constraint) 
    {
		auto params = constraint->parameters();
        std::vector<Param> vecs;
        for(const auto& param : params)
        {
			loadParam(constraint, param, vecs);
        }
		constraintvars[constraint] = vecs;
		constraints_.push_back(constraint);
    }

    double catErrorForGrad(int i)
    {
        double error = 0;
        for(unsigned int j = 0; j < vecmap[i].size(); j++)
        {
            error += computeError(vecmap[i][j]);
        }
        return error;
    }

    double calGradient(int i, double pert)
    {
        double OldValue = element(i);
        setElement(i, OldValue - pert);
        double e1 = catErrorForGrad(i);
        setElement(i, OldValue + pert);
        double e2 = catErrorForGrad(i);
        setElement(i, OldValue);
        return 0.5 * (e2 - e1) / pert;
    }

private:
    void loadParam(const std::shared_ptr<Constraint>& c, const Param& param, std::vector<Param>& mylist)
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
#endif // SKETCHSOLVER_SOLVER_H