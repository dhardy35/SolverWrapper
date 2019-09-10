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

template <class T> class SLRExpr;


template <typename T>
class SLRModel
{
private:
    std::vector<SLRVar<T>> __varsVector;

public:
    void printExpression(const SLRExpr<T> &expr);
    void setObjective(const SLRExpr<T> &, int goal = 0);
    SLRVar<T>   addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name);


};

#include "Model.cpp"


#endif //SOLVEUR_MODEL_H
