//
// Created by adrien_bedel on 10/09/19.
// class 01
//

#ifndef SOLVEUR_CONSTRAINTEXPRESSION_H
#define SOLVEUR_CONSTRAINTEXPRESSION_H

#include "Expression.h"

template <class T> class SLRConstrExpr;

template <typename T> SLRConstrExpr<T> operator<=(const SLRExpr<T> &, const SLRExpr<T> &);
template <typename T> SLRConstrExpr<T> operator>=(const SLRExpr<T> &, const SLRExpr<T> &);
template <typename T> SLRConstrExpr<T> operator==(const SLRExpr<T> &, const SLRExpr<T> &);

template <typename T> SLRConstrExpr<T> operator<=(const double &, const SLRExpr<T> &);
template <typename T> SLRConstrExpr<T> operator>=(const double &, const SLRExpr<T> &);
template <typename T> SLRConstrExpr<T> operator==(const double &, const SLRExpr<T> &);

template <typename T> SLRConstrExpr<T> operator<=(const SLRExpr<T> &, const double &);
template <typename T> SLRConstrExpr<T> operator>=(const SLRExpr<T> &, const double &);
template <typename T> SLRConstrExpr<T> operator==(const SLRExpr<T> &, const double &);


template <typename T>
class SLRConstrExpr
{
private:
    char         _sign;
    SLRExpr<T>   _expr;
    double       _constr;

public:
    SLRConstrExpr() = delete;
    SLRConstrExpr(const SLRExpr<T> &, const SLRExpr<T> &, const char &);
    SLRConstrExpr(const SLRExpr<T> &, const double &, const char &);

    friend class SLRModel<T>;

    friend SLRConstrExpr<T> operator<=<>(const SLRExpr<T> &, const SLRExpr<T> &);
    friend SLRConstrExpr<T> operator>=<>(const SLRExpr<T> &, const SLRExpr<T> &);
    friend SLRConstrExpr<T> operator==<>(const SLRExpr<T> &, const SLRExpr<T> &);

    friend SLRConstrExpr<T> operator<=<>(const double &, const SLRExpr<T> &);
    friend SLRConstrExpr<T> operator>=<>(const double &, const SLRExpr<T> &);
    friend SLRConstrExpr<T> operator==<>(const double &, const SLRExpr<T> &);

    friend SLRConstrExpr<T> operator<=<>(const SLRExpr<T> &, const double &);
    friend SLRConstrExpr<T> operator>=<>(const SLRExpr<T> &, const double &);
    friend SLRConstrExpr<T> operator==<>(const SLRExpr<T> &, const double &);
};

#include "ConstraintExpression.cpp"

#endif //SOLVEUR_CONSTRAINTEXPRESSION_H
