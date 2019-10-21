//
// Created by adrien_bedel on 09/09/19.
// class 05
//

#ifndef SOLVEUR_VARIABLE_H
#define SOLVEUR_VARIABLE_H

#include "Expression.h"

template <typename T>
class SLRVarRep
{
private:
    T               _lowerBound;
    T               _upperBound;
    T               _solution;
    std::string     _name;
public:
    SLRVarRep(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
    : _lowerBound(lowerBound), _upperBound(upperBound), _solution(solution), _name(name)
    {}
    friend class SLRVar<T>;
    T get() const {return _solution; }
    std::string getName() const { return _name; }
    T getLowerBound() const {return _lowerBound; }
    T getUpperBound() const {return _upperBound; }
    T getSolution() const {return _solution; }

    void setName(const std::string &name) { _name = name;}
    void setLowerBound(const T &lowerBound) {_lowerBound = lowerBound;}
    void setUpperBound(const T &upperBound) {_upperBound = upperBound; }
    void setSolution(const T &solution) {_solution = solution; }
    int operator[](const std::vector<SLRVar<T>> &) const;
};

template <typename T>
class SLRVar : public SLRExpr<T>
{
    using SLRExpr<T>::_constant;
    using SLRExpr<T>::_coeffs;
    using SLRExpr<T>::_vars;
    using SLRExpr<T>::_varIndex;
private:
    std::shared_ptr<SLRVarRep<T>>   _varRep;

public:
    SLRVar(const T &, const T &, const T &, const std::string &);
    SLRVar();
    T get() const;
    std::string getName() const;
    T getLowerBound() const;
    T getUpperBound() const;
    T getSolution() const;

    void set(const T &);
    bool operator==(const SLRVar<T> &) const;
    bool operator==(const std::string &) const;
    bool operator<(const SLRVar<T> &) const;
    bool operator==(const std::shared_ptr<SLRVarRep<T>> &varRep) const;

    std::shared_ptr<SLRVarRep<T>>   getVarRep() const;

};

#include "Variable.cpp"

#endif //SOLVEUR_VARIABLE_H
