//
// Created by adrien_bedel on 10/09/19.
//

#include "ConstraintExpression.h"

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight, const char &sign) : _sign(sign)
{
    // get constraint from expression's constants
    _exprRight = exprRight;
    _exprLeft = exprLeft;
}

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const SLRExpr<T> &exprLeft, const double &constr, const char &sign) : _sign(sign)
{
    // get constraint from expression's constants
    _exprRight = constr;
    _exprLeft = exprLeft;
}

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const double &constr, const SLRExpr<T> &exprRight, const char &sign) : _sign(sign)
{
    // get constraint from expression's constants
    _exprRight = exprRight;
    _exprLeft = constr;
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
{ return (SLRConstrExpr<T>(constr, exprRight, SLR_LESS_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator>=(const double &constr, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(constr, exprRight, SLR_GREATER_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator==(const double &constr, const SLRExpr<T> &exprRight)
{ return (SLRConstrExpr<T>(constr, exprRight, SLR_EQUAL));}




template <typename T>
SLRConstrExpr<T> operator<=(const SLRExpr<T> &exprLeft, const double &constr)
{ return (SLRConstrExpr<T>(exprLeft, constr, SLR_LESS_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator>=(const SLRExpr<T> &exprLeft, const double &constr)
{ return (SLRConstrExpr<T>(exprLeft, constr, SLR_GREATER_EQUAL));}


template <typename T>
SLRConstrExpr<T> operator==(const SLRExpr<T> &exprLeft, const double &constr)
{ return (SLRConstrExpr<T>(exprLeft, constr, SLR_EQUAL));}
