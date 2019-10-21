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
    int                     _nbVar;
    int                     _solutionState;


#ifdef GRB
    std::shared_ptr<GRBModel>   _model;
    GRBEnv                      _env;
    std::vector<GRBVar>         _vars;

    GRBLinExpr                  SLRExprToGRBLineExpr(const SLRExpr<T> &expr);
    GRBQuadExpr                 SLRExprToGRBQuadExpr(const SLRExpr<T> &expr);

#elif OSQP
    int                                 _nbConstr;
    std::vector<double>                 _lowerBound;
    std::vector<double>                 _upperBound;
    std::vector<std::vector<double>>    _constrCoeffs;
    c_float         *_quadricCoeffs;
    c_float         *_linearCoeffs;
    c_int           *_coeffsRaws;
    c_int           *_coeffsColumns;
    OSQPWorkspace   *_work;
    OSQPSettings    _settings;
    OSQPData        _data;
    int             _quadricNb;

    void            fillData();
    void            printOSQPVariables(OSQPData &data);
    void            updateVariableConstraints();
#endif


public:
    void        printExpression(const SLRExpr<T> &) const;
    void        printExpression(const SLRConstrExpr<T> &) const;
    void        setObjective(const SLRExpr<T> &, int goal = 0);
    void        addConstr(const SLRConstrExpr<T> &, const std::string &name = "");
    SLRVar<T>   addVar(const T &, const T &, const T &, const std::string &name = "");
    SLRVar<T>   getVarByName(const std::string &name);
    void        optimize();
    bool        hasSolution() const;
    void        printDebug(const bool &);
    void        update();


#ifdef GRB
    SLRModel();
    SLRModel(const GRBEnv &);
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
