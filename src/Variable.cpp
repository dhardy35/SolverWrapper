//
// Created by adrien_bedel on 09/09/19.
//

#include "Variable.h"

template <typename T>
SLRVar<T>::SLRVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
        : _lowerBound(lowerBound), _upperBound(upperBound), _solution(solution), _name(name)
{
    _varIndex = 0;
    _constant = 0;
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(*this);
    _varIndex++;
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
