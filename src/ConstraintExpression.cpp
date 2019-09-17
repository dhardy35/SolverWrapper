//
// Created by adrien_bedel on 10/09/19.
//

#include "ConstraintExpression.h"

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight, const char &sign) : _sign(sign), _expr(exprLeft)
{
    // get constraint from expression's constants
    _constr = exprRight._constant - exprLeft._constant;
    _expr._constant = 0;
    int k;
    bool    found;
    // we try to find similarities in the expression
    // ex : 2x == 3x + 1 will be -x == 1
    for (int i = 0; i <= exprRight._varIndex; i++)
    {
        found = false;
        for (int j = 0; j <= _expr._varIndex && !found; j++)
        {
            if (exprRight._vars[i].size() == _expr._vars[j].size())
            {
                for (k = 0; k < exprRight._vars[i].size() &&
                            exprRight._vars[i][k] == _expr._vars[j][k]; k++);
                if (k == _expr._vars[j].size())
                {
                    _expr._coeffs[j] -= exprRight._coeffs[i];
                    found = true;
                }
            }
        }
        // if the left expression doesn't have a part that the right expression has
        // we transfer it
        // ex : 3x == 3y + 1 will be 3x - 3y == 1
        if (!found)
        {
            if (exprRight._vars[i].size() == 2)
                _expr = _expr + -exprRight._coeffs[i] * exprRight._vars[i][0] * exprRight._vars[i][1];
            else
                _expr = _expr + -exprRight._coeffs[i] * exprRight._vars[i][0];
        }
    }
}

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const SLRExpr<T> &exprLeft, const double &constr, const char &sign) : _sign(sign), _expr(exprLeft)
{
    // get constraint from expression's constants
    _constr = constr - exprLeft._constant;
    _expr._constant = 0;
}


template <typename T>
SLRConstrExpr<T> operator<=(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(exprLeft, exprRight, SLR_LESS_EQUAL));}

template <typename T>
SLRConstrExpr<T> operator>=(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(exprLeft, exprRight, SLR_GREATER_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator==(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(exprLeft, exprRight, SLR_EQUAL));}




template <typename T>
SLRConstrExpr<T> operator<=(const double &constr, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(exprRight, constr, SLR_GREATER_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator>=(const double &constr, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(exprRight, constr, SLR_LESS_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator==(const double &constr, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(exprRight, constr, SLR_EQUAL));}




template <typename T>
SLRConstrExpr<T> operator<=(const SLRExpr<T> &exprLeft, const double &constr)
{ return (SLRConstrExpr<T>(exprLeft, constr, SLR_LESS_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator>=(const SLRExpr<T> &exprLeft, const double &constr)
{ return (SLRConstrExpr<T>(exprLeft, constr, SLR_GREATER_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator==(const SLRExpr<T> &exprLeft, const double &constr)
{ return (SLRConstrExpr<T>(exprLeft, constr, SLR_EQUAL));}
