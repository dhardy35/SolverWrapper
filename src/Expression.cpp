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
SLRExpr<T>::SLRExpr(const SLRVar<T> &x) : _varIndex(0), _constant(0)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    _varIndex++;
}
/*
template <class T>
SLRExpr<T>::SLRExpr(const SLRExpr<T> &x, const double &coeff) : _varIndex(0), _constant(0)
{
    _coeffs.push_back(coeff);
    _vars.push_back(std::vector<SLRExpr<T>>());
    _vars.at(_varIndex).push_back(x);
}*/
/*
template <class T>
SLRExpr<T>::SLRExpr(const SLRExpr<T> &x, const SLRExpr<T> &y) : _varIndex(0), _constant(0)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRExpr<T>>());
    _vars.at(_varIndex).push_back(x);
    // sort in alphabetical order
    if (x < y)
        _vars.at(_varIndex).push_back(y);
    else
        _vars.at(_varIndex).insert(_vars.at(_varIndex).begin(), y);
}*/

template <typename T>
SLRExpr<T> operator*(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T> outPut(x);
    for (int i = 0; i < outPut._vars.size(); i++)
    {
        for (int j = 0; j < y._vars.size(); j++)
        {
            outPut._coeffs[i] *= y._coeffs[j];
            outPut._vars[i].push_back(y._vars[j][0]);
            if (y._vars[j].size() == 2)
                outPut._vars[i].push_back(y._vars[j][1]);
            //simplify();
        }
    }
    return outPut;
}

template <typename T>
SLRExpr<T> operator*(const double &k, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> outPut(inExpr);
    for (auto &coeff : outPut._coeffs)
        coeff *= k;
    return (outPut);
}

template <typename T>
SLRExpr<T> operator*(const SLRExpr<T> &inExpr, const double &k)
{
    SLRExpr<T> outPut(inExpr);
    for (auto &coeff : outPut._coeffs)
        coeff *= k;
    return (outPut);
}

template <typename T>
SLRExpr<T> operator+(const double &constant, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> expr(inExpr);
    expr = expr + constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator+(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T>  outPut(x);
    outPut._varIndex += y._varIndex;
    outPut._coeffs.insert(outPut._coeffs.end(), y._coeffs.begin(), y._coeffs.end());
    outPut._vars.insert(outPut._vars.end(), y._vars.begin(), y._vars.end());
    return outPut;
}
/*
template <typename T>
SLRExpr<T> operator+(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T> expr(x);
    expr = expr + y;
    return (expr);
}*/

template <typename T>
SLRExpr<T> operator+(const SLRExpr<T> &x, const double &constant)
{
    SLRExpr<T> expr(x);
    expr = expr + constant;
    return (expr);
}

template <typename T>
SLRExpr<T> operator-(const double &constant, const SLRExpr<T> &inExpr)
{
    SLRExpr<T> expr(inExpr);
    expr = expr - constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T>  outPut(x);
    SLRExpr<T>  inExpr(y);
    outPut._varIndex += inExpr._varIndex;
    for (auto &coeff : inExpr._coeffs)
        coeff *= -1;
    outPut._coeffs.insert(outPut._coeffs.end(), inExpr._coeffs.begin(), inExpr._coeffs.end());
    outPut._vars.insert(outPut._vars.end(), inExpr._vars.begin(), inExpr._vars.end());
}

template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &inExpr)
{
    SLRExpr<T> expr(inExpr);
    for (auto &coeff : expr._coeffs)
        coeff *= -1;
    return expr;
}
/*
template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &x, const SLRExpr<T> &y)
{
    SLRExpr<T> expr(x);
    expr = expr - y;
    return (expr);
}*/

template <typename T>
SLRExpr<T> operator-(const SLRExpr<T> &inExpr, const double &constant)
{
    SLRExpr<T> expr(inExpr);
    expr = expr - constant;
    return expr;
}
/*
template <typename T>
SLRExpr<T> operator*(const SLRExpr<T> &expr, const double &k)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
        coeff *= k;
    return (ex);
}*/
/*
template <typename T>
SLRExpr<T> operator*(const double &k, const SLRExpr<T> &expr)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
        coeff *= k;
    return (ex);
}*/
/*
template <typename T>
SLRExpr<T> operator/(const SLRExpr<T> &expr, const double &k)
{
    SLRExpr<T> ex = expr;
    for (auto &coeff : ex._coeffs)
        coeff /= k;
    return (ex);
}*/

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

/*
template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const SLRExpr<T> &expr)
{
    SLRExpr<T> x(*this);
    for (int i = 0; i < x._vars.size(); i++)
    {
        for (int j = 0; j < expr._vars.size(); j++)
        {
            x._coeffs[i] *= expr._coeffs[j];
            x._vars[i].push_back(expr._vars[j][0]);
            if (expr._vars[j].size() == 2)
                x._vars[i].push_back(expr._vars[j][1]);
            simplify();
        }
    }
    return x;
}


template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const double &k)
{
    SLRExpr<T> outPut(*this);
    for (auto &coeff : outPut._coeffs)
        coeff *= k;
    return outPut;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator/(const double &k)
{
    SLRExpr<T> outPut(*this);
    for (auto &coeff : outPut._coeffs)
        coeff /= k;
    return outPut;
}*/
/*
template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const SLRExpr<T> &x)
{
    SLRExpr<T> outPut(*this);
    int i;
    // add variable in the right alphabetical place
    for (i = 0; i < outPut._vars.at(outPut._varIndex).size()
                && outPut._vars.at(outPut._varIndex)[i] < x; i++) {};
    outPut._vars.at(outPut._varIndex).insert(outPut._vars.at(outPut._varIndex).begin() + i, x);
    if (outPut._vars.at(outPut._varIndex).size() > 2)
        throw SLRException(021203, "SLRExpr::operator*(SLRExpr)", "three dimensional is not allowed");

    return outPut;
}*/
/*
template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const double &constant)
{
    SLRExpr<T> outPut(*this);
    outPut._constant = constant;
    return outPut;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const SLRExpr<T> &x)
{
    SLRExpr<T> outPut(*this);
    outPut._varIndex++;
    outPut._coeffs.push_back(1);
    outPut._vars.push_back(std::vector<SLRExpr<T>>());
    outPut._vars.at(outPut._varIndex).push_back(x);
    simplify();
    return outPut;
}*/
/*
// fuse two expressions
template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const SLRExpr<T> &expr)
{
    SLRExpr<T> outPut(*this);
    return outPut += expr;
}*/

template <typename T>
void SLRExpr<T>::operator+=(const SLRExpr<T> &expr)
{
    _varIndex += expr._varIndex;
    _coeffs.insert(_coeffs.end(), expr._coeffs.begin(), expr._coeffs.end());
    _vars.insert(_vars.end(), expr._vars.begin(), expr._vars.end());
    //simplify();
}

template <typename T>
void SLRExpr<T>::operator-=(const SLRExpr<T> &expr)
{
    SLRExpr<T> inExpr(expr);
    _varIndex += inExpr._varIndex;
    for (auto &coeff : inExpr._coeffs)
        coeff *= -1;
    _coeffs.insert(_coeffs.end(), inExpr._coeffs.begin(), inExpr._coeffs.end());
    _vars.insert(_vars.end(), inExpr._vars.begin(), inExpr._vars.end());
    //simplify();
}

template <typename T>
void SLRExpr<T>::operator*=(const double &k)
{
    for (auto &coeff : _coeffs)
        coeff *= k;
}
/*
template <typename T>
SLRExpr<T> SLRExpr<T>::operator-(const double &constant)
{
    SLRExpr<T> outPut(*this);
    outPut._constant = -constant;
    return outPut;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator-(const SLRExpr<T> &x)
{
    SLRExpr<T> outPut(*this);
    outPut._varIndex++;
    outPut._coeffs.push_back(-1);
    outPut._vars.push_back(std::vector<SLRExpr<T>>());
    outPut._vars.at(outPut._varIndex).push_back(x);
    simplify();
    return outPut;
}*/
/*
// fuse two expressions
template <typename T>
SLRExpr<T> SLRExpr<T>::operator-(const SLRExpr<T> &expr)
{
    SLRExpr<T> outPut(*this);
    outPut._varIndex++;
    outPut._coeffs.insert(outPut._coeffs.end(), expr._coeffs.begin(), expr._coeffs.end());
    outPut._vars.insert(outPut._vars.end(), expr._vars.begin(), expr._vars.end());
    for (int i = 0; i <= expr._varIndex; i++)
        outPut._coeffs[outPut._varIndex + i] *= -1;
    outPut._varIndex += expr._varIndex;
    simplify();
    return outPut;
}*/
/*
template <typename T>
SLRExpr<T> SLRExpr<T>::operator-=(const SLRExpr<T> &expr)
{
    return *this - expr;
}*/

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
    /*for (int i = 0; i < _varIndex; i++)
    {
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
    }*/
}

