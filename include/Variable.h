//
// Created by adrien_bedel on 09/09/19.
//

#ifndef SOLVEUR_VARIABLE_H
#define SOLVEUR_VARIABLE_H

#include <iostream>

template <typename T>
class SLRVar
{
private:
    T               _lowerBound;
    T               _upperBound;
    T               _solution;
    std::string     _name;

public:
    SLRVar() = delete;
    SLRVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name);

    std::string getName() const;
    T getLowerBound() const;
    T getUpperBound() const;
    T getSolution() const;

    bool operator==(const SLRVar<T> &) const;
    bool operator<(const SLRVar<T> &) const;

};

#include "Variable.cpp"

#endif //SOLVEUR_VARIABLE_H
