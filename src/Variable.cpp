//
// Created by adrien_bedel on 09/09/19.
//

#include "Variable.h"

template <typename T>
SLRVar<T>::SLRVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
{
    _varIndex = 0;
    _constant = 0;
    _varRep = std::make_shared<SLRVarRep<T>>(lowerBound, upperBound, solution, name);
    _coeffs.push_back(1);
    _vars.push_back(std::vector<std::shared_ptr<SLRVarRep<T>>>());
    _vars.at(_varIndex).push_back(_varRep);
    _varIndex++;
}

template <typename T>
SLRVar<T>::SLRVar()
{
    _varIndex = 0;
    _constant = 0;
    _varRep = std::make_shared<SLRVarRep<T>>(0.0, 0.0, 0.0, "");
    _coeffs.push_back(1);
    _vars.push_back(std::vector<std::shared_ptr<SLRVarRep<T>>>());
    _vars.at(_varIndex).push_back(_varRep);
    _varIndex++;
}

template <typename T>
std::string SLRVar<T>::getName() const
{
    return (_varRep->_name);
}

template <typename T>
T SLRVar<T>::getLowerBound() const
{
    return (_varRep->_lowerBound);
}

template <typename T>
T SLRVar<T>::getUpperBound() const
{
    return (_varRep->_upperBound);
}

template <typename T>
T SLRVar<T>::get() const
{
    return (_varRep->_solution);
}


template <typename T>
T SLRVar<T>::getSolution() const
{
    return (_varRep->_solution);
}

template <typename T>
void SLRVar<T>::set(const T &solution)
{
    _varRep->_solution = solution;
}


template <typename T>
bool SLRVar<T>::operator==(const SLRVar<T> &var) const
{
    return (_varRep->_name == var.getName());
}

template <typename T>
bool SLRVar<T>::operator==(const std::string &name) const
{
    return (_varRep->_name == name);
}

template <typename T>
bool SLRVar<T>::operator==(const std::shared_ptr<SLRVarRep<T>> &varRep) const
{
    return (_varRep == varRep);
}

template <typename T>
bool SLRVar<T>::operator<(const SLRVar<T> &var) const
{
    return (_varRep->_name < var.getName());
}

template <typename T>
int SLRVarRep<T>::operator[](const std::vector<SLRVar<T>> &vars) const
{
    return ((int)std::distance(vars.begin(), std::find(vars.begin(), vars.end(), *this)));
}

template <typename T>
std::shared_ptr<SLRVarRep<T>>   SLRVar<T>::getVarRep() const
{
    return (_varRep);
}

