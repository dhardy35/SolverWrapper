//
// Created by adrien_bedel on 09/09/19.
//

#ifndef SOLVEUR_MODEL_H
#define SOLVEUR_MODEL_H

#include <iostream>
#include <vector>
#include <string>

#include "Variable.h"

#define RAW 0
#define COLUMN 1
#define SLR_MINIMIZE 1
#define SLR_MAXIMIZE -1
enum ConstrSign {INF, SUP, EQUAL};

template <class T> class SLRExpr;


template <typename T>
class SLRModel
{
private:
    std::vector<SLRVar<T>>  _varsVector;
    int                     _nbVar;

#ifdef OSQP
    c_float         *_quadricCoeffs;
    c_float         *_linearCoeffs;
    c_int           **_coeffsPositions;
    OSQPWorkspace   *_work;
    OSQPSettings    _settings;
    OSQPData        _data;
    int             _quadricNb;
#endif

public:
    SLRModel();
    void        printExpression(const SLRExpr<T> &expr);
    int         setObjective(const SLRExpr<T> &, int goal = 0);
    int         addConstr(const SLRExpr<T> &, const std::string &);
    SLRVar<T>   addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name);


};

#include "Model.cpp"


#endif //SOLVEUR_MODEL_H
