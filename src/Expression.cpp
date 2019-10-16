//
// Created by adrien_bedel on 09/09/19.
//

#include "Expression.h"


template <class T>
SLRExpr<T>::SLRExpr() : _varIndex(0), _constant(0)
{

}

template <class T>
SLRExpr<T>::SLRExpr(const double &constant) : _varIndex(0), _constant(constant)
{

}

template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x) : _varIndex(0), _constant(x._constant)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    _varIndex++;
}

//-----------------
//        *
//-----------------
template <typename T>
SLRExpr<T> operator*(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T> result;
    for (int i = 0; i < x._varIndex; i++)
    {
        for (int j = 0; j < y._varIndex; j++)
        {
            if (x._coeffs[i] * y._coeffs[j] != 0.0)
            {
                result._coeffs.push_back(x._coeffs[i] * y._coeffs[j]);
                result._vars.push_back(x._vars[i]);
                result._vars[result._varIndex].insert(result._vars[result._varIndex].end(), y._vars[j].begin(),
                                                      y._vars[j].end());

                result.simplify();
                result._varIndex++;
            }
        }
        if (x._coeffs[i] * y._constant != 0.0)
        {
            result._vars.push_back(x._vars[i]);
            result._coeffs.push_back(x._coeffs[i] * y._constant);
            result.simplify();
            result._varIndex++;
        }
    }
    for (int j = 0; j < y._varIndex; j++)
    {
        if (x._constant * y._coeffs[j] != 0.0)
        {
            result._coeffs.push_back(x._constant * y._coeffs[j]);
            result._vars.push_back(y._vars[j]);
            result.simplify();
            result._varIndex++;
        }
    }
    result._constant = x._constant * y._constant;
    return result;
}

template <typename T>
SLRExpr<T> operator*(const SLRExpr<T> &inExpr, const double &k)
{
    SLRExpr<T> outPut(inExpr);
    if (k == 0)
    {
        outPut._coeffs.clear();
        outPut._vars.clear();
        outPut._varIndex = 0;
    }
    else
        {
        for (auto &coeff : outPut._coeffs)
            coeff *= k;
    }
    return (outPut);
}

template <typename T>
SLRExpr<T> operator*(const double &k, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> outPut(inExpr);
    if (k == 0)
    {
        outPut._coeffs.clear();
        outPut._vars.clear();
        outPut._varIndex = 0;
    }
    else
    {
        for (auto &coeff : outPut._coeffs)
            coeff *= k;
    }
    return (outPut);
}

//-----------------
//        /
//-----------------

template <typename T>
SLRExpr<T> operator/(const double &k, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> outPut(inExpr);
    for (auto &coeff : outPut._coeffs)
        coeff /= k;
    return (outPut);
}

template <typename T>
SLRExpr<T> operator/(const SLRExpr<T> &inExpr, const double &k)
{
    SLRExpr<T> outPut(inExpr);
    for (auto &coeff : outPut._coeffs)
        coeff /= k;
    return (outPut);
}

//-----------------
//        +
//-----------------

template <typename T>
SLRExpr<T> operator+(const double &constant, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> expr(inExpr);
    expr._constant += constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator+(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T>  outPut(x);
    outPut += y;
    return outPut;
}

template <typename T>
SLRExpr<T> operator+(const SLRExpr<T> &x, const double &constant)
{
    SLRExpr<T> expr(x);
    expr._constant += constant;
    return (expr);
}

//-----------------
//        -
//-----------------

template <typename T>
SLRExpr<T> operator-(const double &constant, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> expr(inExpr);
    expr = -expr;
    expr._constant = constant + expr._constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T>  outPut(x);
    outPut -= y;
    return outPut;
}

template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &inExpr)
{
    SLRExpr<T> expr(inExpr);
    for (auto &coeff : expr._coeffs)
        coeff *= -1;
    expr._constant *= -1;
    return expr;
}

template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &inExpr, const double &constant)
{
    SLRExpr<T> expr(inExpr);
    expr._constant -= constant;
    return expr;
}

//------------------
// change Expression
//------------------

template <typename T>
void SLRExpr<T>::operator+=(const SLRExpr<T> &expr)
{
    for (int i = 0; i < expr._varIndex; i++)
    {
        if (expr._coeffs[i] != 0.0)
        {
            _coeffs.push_back(expr._coeffs[i]);
            _vars.push_back(expr._vars[i]);
            simplify();
            _varIndex++;
        }
    }
    _constant += expr._constant;
}

template <typename T>
void SLRExpr<T>::operator-=(const SLRExpr<T> &expr)
{
    SLRExpr<T> inExpr(expr);
    inExpr = -inExpr;
    *this += inExpr;
}

template <typename T>
void SLRExpr<T>::operator*=(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff *= k;
}

template <typename T>
void SLRExpr<T>::operator/=(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff /= k;
}



// simplify expression
// ex : 2x + 2x will be 4x
template <typename T>
void    SLRExpr<T>::simplify()
{
    // tmp remove to win time
    for (int i = _varIndex - 1; i >= 0; i--)
    {
        if (_vars[_varIndex].size() == _vars[i].size())
        {
            int tmp = 0;
            for (tmp = 0; tmp < _vars[i].size() &&
                    _vars[i][tmp] == _vars[_varIndex][tmp]; tmp++);
            if (tmp == _vars[i].size())
            {
                _coeffs[i] += _coeffs[_varIndex];
                _vars.erase(_vars.begin() + _varIndex);
                _coeffs.erase(_coeffs.begin() + _varIndex);
                _varIndex--;
                if (_coeffs[i] == 0.0)
                {
                    _coeffs.erase(_coeffs.begin() + i);
                    _vars.erase(_vars.begin() + i);
                    _varIndex--;
                }
                return ;
            }
        }
    }
}

