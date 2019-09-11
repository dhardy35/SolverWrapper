//
// Created by adrien_bedel on 10/09/19.
//

#ifndef SOLVEUR_CONSTRAINTEXPRESSION_H
#define SOLVEUR_CONSTRAINTEXPRESSION_H

#include "Expression.h"


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
    ConstrSign _sign;
    SLRExpr<T>  _expr;
    double       _constr;

public:
    SLRConstrExpr() = delete;
    SLRConstrExpr(const SLRExpr<T> &, const SLRExpr<T> &, const ConstrSign &);
    SLRConstrExpr(const SLRExpr<T> &, const double &, const ConstrSign &);

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
