//
// Created by adrien_bedel on 09/09/19.
//

#include "Variable.h"

template <typename T>
SLRVar<T>::SLRVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
{
    _varRep = std::make_shared<SLRVarRep<T>>(lowerBound, upperBound, solution, name);
}

template <typename T>
SLRVar<T>::SLRVar() : _lowerBound(0.0), _upperBound(0.0), _solution(0.0), _name("")
{
    _varRep = std::make_shared<SLRVarRep<T>>(0.0, 0.0, 0.0, "");
}

template <typename T>
std::string SLRVar<T>::getName() const
{
    return (_name);
}

template <typename T>
T SLRVar<T>::getLowerBound() const
{
    return (_lowerBound);
}

template <typename T>
T SLRVar<T>::getUpperBound() const
{
    return (_upperBound);
}

template <typename T>
T SLRVar<T>::get() const
{
    return (_solution);
}


template <typename T>
T SLRVar<T>::getSolution() const
{
    return (_solution);
}

template <typename T>
void SLRVar<T>::set(const T &solution)
{
    _solution = solution;
}


template <typename T>
bool SLRVar<T>::operator==(const SLRVar<T> &var) const
{
    return (_name == var.getName());
}

template <typename T>
bool SLRVar<T>::operator==(const std::string &name) const
{
    return (_name == name);
}

template <typename T>
bool SLRVar<T>::operator<(const SLRVar<T> &var) const
{
    return (_name < var.getName());
}

template <typename T>
int SLRVar<T>::operator[](const std::vector<SLRVar<T>> &vars) const
{
    return ((int)std::distance(vars.begin(), std::find(vars.begin(), vars.end(), *this)));
}
