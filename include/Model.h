//
// Created by adrien_bedel on 09/09/19.
// class 03
//

#ifndef SOLVEUR_MODEL_H
#define SOLVEUR_MODEL_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <tuple>

#ifdef GRB
#include "gurobi_c++.h"
#elif OSQP
#include "osqp.h"
#endif

#include "SLRException.h"
#include "Variable.h"
#include "ConstraintExpression.h"



/* Objective sense */

#define SLR_MINIMIZE 1
#define SLR_MAXIMIZE -1


template <typename T>
class SLRModel
{
public:
    std::vector<SLRVar<T>>  _varsVector;
    unsigned int                     _nbVar;
    int                     _solutionState;


#ifdef GRB
    std::shared_ptr<GRBModel>   _model;
    static inline GRBEnv        _env = true;
    std::vector<GRBVar>         _vars;

    GRBLinExpr                  SLRExprToGRBLineExpr(const SLRExpr<T> &expr);
    GRBQuadExpr                 SLRExprToGRBQuadExpr(const SLRExpr<T> &expr);

#elif OSQP
    bool                                _isObjectivSet;
    double                             _constant;
    int                                 _nbConstr;
    std::vector<double>                _lowerBound;
    std::vector<double>                 _upperBound;
    std::vector<double>         _objQuadricCoeffs;
    std::vector<double>         _objLinearCoeffs;
    std::vector<c_int>           _objCoeffsRaws;
    std::vector<c_int>           _objCoeffsColumns;
    std::vector<double>  _constrLinearCoeffs;
    std::vector<std::tuple<double, int, int>>   _constrLinearCoeffsPos;
    std::vector<c_int>  _constrCoeffsRaws;
    std::vector<c_int>  _constrCoeffsColumns;

    std::vector<double> _x;
    OSQPWorkspace   *_work;
    OSQPSettings    _settings;
    OSQPData        _data;
    unsigned int             _quadricNb;

    void            fillData();
    void            printOSQPVariables(OSQPData &data);
    void            updateVariableConstraints();
    ~SLRModel();
#endif


public:
    void        printExpression(const SLRConstrExpr<T> &) const;
    void        setObjective(const SLRExpr<T> &, int goal = 0);
    void        addConstr(const SLRConstrExpr<T> &, const std::string &name = "");
    SLRVar<T>   addVar(const T &, const T &, const T &, const std::string &name = "");
    SLRVar<T>   getVarByName(const std::string &name);
    void        optimize();
    bool        hasSolution() const;
    void        printDebug(const bool &);
    void        update();
    double      getObjectiveError(const SLRExpr<T> &) const;


#ifdef GRB
    SLRModel();
    void                    printResult();
    void        set(GRB_IntParam flag, int todo);
    void        set(GRB_DoubleParam flag, float todo);
#elif OSQP
    SLRModel();
    void                    printResult();
#endif


};

#include "Model.cpp"


#endif //SOLVEUR_MODEL_H
