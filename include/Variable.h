//
// Created by adrien_bedel on 09/09/19.
// class 05
//

#ifndef SOLVEUR_VARIABLE_H
#define SOLVEUR_VARIABLE_H

#include <iostream>
#include <algorithm>

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
    SLRVar(const T &, const T &, const T &, const std::string &);

    std::string getName() const;
    T getLowerBound() const;
    T getUpperBound() const;
    T getSolution() const;
    T get() const;

    void set(const T &);
    bool operator==(const SLRVar<T> &) const;
    bool operator==(const std::string &) const;
    bool operator<(const SLRVar<T> &) const;
    int operator[](const std::vector<SLRVar<T>> &) const;

};

#include "Variable.cpp"

#endif //SOLVEUR_VARIABLE_H
