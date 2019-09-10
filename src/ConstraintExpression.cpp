//
// Created by adrien_bedel on 10/09/19.
//

#include "ConstraintExpression.h"

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight, const ConstrSign &sign) : _sign(sign)
{
    _constr = exprRight._constant - exprLeft._constant;
    
}

template <typename T>
SLRConstrExpr<T>::SLRConstrExpr(const SLRExpr<T> &exprLeft, const double &constr, const ConstrSign &sign) : _sign(sign)
{
    _constr = constr - exprLeft._constant;
    _expr = exprLeft;
}


template <typename T>
SLRConstrExpr<T> operator<=(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight)
: SLRConstrExpr(exprLeft, exprRight, INF) { }

template <typename T>
SLRConstrExpr<T> operator>=(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight)
: SLRConstrExpr(exprLeft, exprRight, SUP) { }


template <typename T>
SLRConstrExpr<T> operator==(const SLRExpr<T> &exprLeft, const SLRExpr<T> &exprRight)
: SLRConstrExpr(exprLeft, exprRight, EQUAL) { }




template <typename T>
SLRConstrExpr<T> operator<=(const double &constr, const SLRExpr<T> &exprRight)
: SLRConstrExpr(exprRight, constr, SUP) { }


template <typename T>
SLRConstrExpr<T> operator>=(const double &constr, const SLRExpr<T> &exprRight)
: SLRConstrExpr(exprRight, constr, INF) { }


template <typename T>
SLRConstrExpr<T> operator==(const double &constr, const SLRExpr<T> &exprRight)
: SLRConstrExpr(exprRight, constr, EQUAL) { }




template <typename T>
SLRConstrExpr<T> operator<=(const SLRExpr<T> &exprLeft, const double &constr)
: SLRConstrExpr(exprLeft, constr, INF) { }


template <typename T>
SLRConstrExpr<T> operator>=(const SLRExpr<T> &exprLeft, const double &constr)
: SLRConstrExpr(exprLeft, constr, SUP) { }


template <typename T>
SLRConstrExpr<T> operator==(const SLRExpr<T> &exprLeft, const double &constr)
: SLRConstrExpr(exprLeft, constr, EQUAL) { }
