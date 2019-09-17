//
// Created by adrien_bedel on 09/09/19.
// class 03
//

#ifndef SOLVEUR_MODEL_H
#define SOLVEUR_MODEL_H

#include <iostream>
#include <vector>
#include <string>

#ifdef GRB
#include "gurobi_c++.h"
#include <memory>
#elif OSQP
#include "osqp.h"
#endif

#include "Variable.h"
#include "SLRException.h"


#define SLR_MINIMIZE 1
#define SLR_MAXIMIZE -1

enum ConstrSign {INF, SUP, EQUAL};

template <class T> class SLRExpr;
template <typename T> class SLRConstrExpr;

template <typename T>
class SLRModel
{
private:
    std::vector<SLRVar<T>>  _varsVector;
    int                     _nbVar;


#ifdef GRB
    std::shared_ptr<GRBModel>   _model;
    GRBEnv                      _env;
    std::vector<GRBVar>         _vars;

    GRBQuadExpr                  SLRExprToGRBLineExpr(const SLRExpr<T> &expr);

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
    void        addConstr(const SLRConstrExpr<T> &, const std::string &);
    SLRVar<T>   addVar(const T &, const T &, const T &, const std::string &);
    void        optimize();

#ifdef GRB
    SLRModel();
    void                    printResult();
#elif OSQP
    SLRModel();
    void                    printResult();
#endif


};

#include "Model.cpp"


#endif //SOLVEUR_MODEL_H
