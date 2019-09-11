//
// Created by adrien_bedel on 09/09/19.
//

#ifndef SOLVEUR_MODEL_H
#define SOLVEUR_MODEL_H

#include <iostream>
#include <vector>
#include <string>


#include "Variable.h"


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

#ifdef OSQP
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
#endif

    void updateVariableConstraints();

public:
    SLRModel();
    void        printExpression(const SLRExpr<T> &) const;
    void        printExpression(const SLRConstrExpr<T> &) const;
    int         setObjective(const SLRExpr<T> &, int goal = 0);
    int         addConstr(const SLRConstrExpr<T> &, const std::string &);
    SLRVar<T>   addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name);
    void        optimize();


};

#include "Model.cpp"


#endif //SOLVEUR_MODEL_H
