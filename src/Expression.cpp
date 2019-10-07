//
// Created by adrien_bedel on 09/09/19.
//

#include "../include/Expression.h"


template <class T>
SLRExpr<T>::SLRExpr() : _varIndex(-1), _constant(0)
{

}

template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x) : _varIndex(0), _constant(0)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
}

template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x, const double &coeff) : _varIndex(0), _constant(0)
{
    _coeffs.push_back(coeff);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
}

template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x, const SLRVar<T> &y) : _varIndex(0), _constant(0)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    // sort in alphabetical order
    if (x < y)
        _vars.at(_varIndex).push_back(y);
    else
        _vars.at(_varIndex).insert(_vars.at(_varIndex).begin(), y);
}

template <typename T>
SLRExpr<T> operator*(const SLRVar<T> &x, const SLRVar<T> &y)
{
    return (SLRExpr<T>(x, y));
}

template <typename T>
SLRExpr<T> operator*(const double &coeff, const SLRVar<T> &x)
{
    return (SLRExpr<T>(x, coeff));
}

template <typename T>
SLRExpr<T> operator*(const SLRVar<T> &x, const double &coeff)
{
    return (SLRExpr<T>(x, coeff));
}

template <typename T>
SLRExpr<T> operator+(const double &constant, SLRExpr<T> expr)
{
    expr = expr + constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator+(const SLRVar<T> &var, SLRExpr<T> expr)
{
    expr = expr + var;
    return (expr);
}

template <typename T>
SLRExpr<T> operator+(const SLRVar<T> &x, const SLRVar<T> &y)
{
    SLRExpr<T> expr(x);
    expr = expr + y;
    return (expr);
}

template <typename T>
SLRExpr<T> operator+(const SLRVar<T> &x, const double &v)
{
    SLRExpr<T> expr(x);
    expr = expr + v;
    return (expr);
}

template <typename T>
SLRExpr<T> operator-(const double &constant, SLRExpr<T> expr)
{
    expr = expr - constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator-(const SLRVar<T> &var, SLRExpr<T> expr)
{
    expr = expr - var;
    return (expr);
}

template <typename T>
SLRExpr<T> operator-(const SLRVar<T> &x, const SLRVar<T> &y)
{
    SLRExpr<T> expr(x);
    expr = expr - y;
    return (expr);
}

template <typename T>
SLRExpr<T> operator-(const SLRVar<T> &x, const double &v)
{
    SLRExpr<T> expr(x);
    expr = expr - v;
    return (expr);
}

template <typename T>
SLRExpr<T> operator*(const SLRExpr<T> &expr, const double &k)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
    {
        coeff *= k;
    }
    return (ex);
}

template <typename T>
SLRExpr<T> operator*(const double &k, const SLRExpr<T> &expr)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
        coeff *= k;
    return (ex);
}

template <typename T>
SLRExpr<T> operator/(const SLRExpr<T> &expr, const double &k)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
    {
        coeff /= k;
    }
    return (ex);
}

template <typename T>
SLRExpr<T> operator/(const double &k, const SLRExpr<T> &expr)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
        coeff /= k;
    return (ex);
}


template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const SLRExpr<T> &expr)
{
    for (int i = 0; i < _vars.size(); i++)
    {
        for (int j = 0; j < expr._vars.size(); j++)
        {
            _coeffs[i] *= expr._coeffs[j];
            _vars[i].push_back(expr._vars[j][0]);
            if (expr._vars[j].size() == 2)
                _vars[i].push_back(expr._vars[j][1]);
            simplify();
        }
    }
    return *this;
}


template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff *= k;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator/(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff /= k;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const SLRVar<T> &x)
{
    int i;
    // add variable in the right alphabetical place
    for (i = 0; i < _vars.at(_varIndex).size()
                && _vars.at(_varIndex)[i] < x; i++) {};
    _vars.at(_varIndex).insert(_vars.at(_varIndex).begin() + i, x);
    if (_vars.at(_varIndex).size() > 2)
        throw SLRException(021203, "SLRExpr::operator*(SLRvar)", "three dimensional is not allowed");

    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const double &constant)
{
    _constant = constant;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const SLRVar<T> &x)
{
    _varIndex++;
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    simplify();
    return *this;
}

// fuse two expressions
template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const SLRExpr<T> &expr)
{
    _varIndex += expr._varIndex + 1;
    _coeffs.insert(_coeffs.end(), expr._coeffs.begin(), expr._coeffs.end());
    _vars.insert(_vars.end(), expr._vars.begin(), expr._vars.end());
    simplify();
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+=(const SLRExpr<T> &expr)
{
    *this = *this + expr;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator*=(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff *= k;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator-(const double &constant)
{
    _constant = -constant;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator-(const SLRVar<T> &x)
{
    _varIndex++;
    _coeffs.push_back(-1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    simplify();
    return *this;
}

// fuse two expressions
template <typename T>
SLRExpr<T> SLRExpr<T>::operator-(const SLRExpr<T> &expr)
{
    SLRExpr<T> exprTmp = expr;
    exprTmp = exprTmp * -1;
    _varIndex += exprTmp._varIndex + 1;
    _coeffs.insert(_coeffs.end(), exprTmp._coeffs.begin(), exprTmp._coeffs.end());
    _vars.insert(_vars.end(), exprTmp._vars.begin(), exprTmp._vars.end());
    simplify();
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator-=(const SLRExpr<T> &expr)
{
    *this = *this - expr;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator/=(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff /= k;
    return *this;
}



// simplify expression
// ex : 2x + 2x will be 4x
template <typename T>
void    SLRExpr<T>::simplify()
{
    for (int i = 0; i < _varIndex; i++)
    {
        if (_vars[i].size() > 2)
            throw SLRException(021203, "SLRExpr::operator*(SLRvar)", "three dimensional is not allowed");
        if (_vars[_varIndex].size() == _vars[i].size())
        {
            int tmp = 0;
            for (int j = 0; j < _vars[i].size() &&
                            _vars[i][j] == _vars[_varIndex][j]; j++, tmp++);
            if (tmp == _vars[i].size())
            {
                _vars.erase(_vars.begin() + _varIndex);
                _coeffs[i] += _coeffs[_varIndex];
                _coeffs.erase(_coeffs.begin() + _varIndex);
                _varIndex--;
                return ;
            }
        }
    }
}

