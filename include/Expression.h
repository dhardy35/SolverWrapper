//
// Created by adrien_bedel on 09/09/19.
// class 02
//

#ifndef SOLVEUR_EXPRESSION_H
#define SOLVEUR_EXPRESSION_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "SLRException.h"

/* Constraint senses */

#define SLR_LESS_EQUAL    '<'
#define SLR_GREATER_EQUAL '>'
#define SLR_EQUAL         '='

template <typename T> class SLRExpr;
template <typename T> class SLRVar;
template <typename T> class SLRVarRep;
template <typename T> class SLRModel;
template <typename T> class SLRConstrExpr;

template <typename T> SLRExpr<T> operator*(const SLRExpr<T> &x, const SLRExpr<T> &y);

template <typename T> SLRExpr<T> operator*(const SLRExpr<T> &, const double &);
template <typename T> SLRExpr<T> operator*(const double &, const SLRExpr<T> &);

template <typename T> SLRExpr<T> operator/(const SLRExpr<T> &, const double &);
template <typename T> SLRExpr<T> operator/(const double &, const SLRExpr<T> &);

template <typename T> SLRExpr<T> operator+(const SLRExpr<T> &, const SLRExpr<T> &);
template <typename T> SLRExpr<T> operator+(const SLRExpr<T> &, const double &);
template <typename T> SLRExpr<T> operator+(const double &, const SLRExpr<T> &);

template <typename T> SLRExpr<T> operator-(const SLRExpr<T> &, const SLRExpr<T> &);
template <typename T> SLRExpr<T> operator-(const SLRExpr<T> &, const double &);
template <typename T> SLRExpr<T> operator-(const double &, const SLRExpr<T> &);
template <typename T> SLRExpr<T> operator-(const SLRExpr<T> &);




//  _vars store the variables like it is in the equation
//  ex : 2xx + -3xy + yy + x + y
//  will be store in a double vector this way :
//  x  x  y  x  y
//  x  y  y
//  and the coeffs will be in _coeffSLRExprs in the same order :
//  2 -3  1  1  1
//  Also, variables will be stored in the alphabetical order inside a column:
//  ex : 2yx + x will be :
//  x  x    and not  y  x
//  y                x
template <typename T>
class SLRExpr
{
protected:
    double                               _constant;
    std::vector<double>                  _coeffs;
    std::vector<std::vector<std::shared_ptr<SLRVarRep<T>>>>  _vars;
    int                                  _varIndex;

private:
    //SLRExpr(const SLRVar<T> &);

public:

    friend class SLRModel<T>;
    friend class SLRConstrExpr<T>;

    SLRExpr();
    SLRExpr(const double &);

    friend SLRExpr<T> operator*<>(const SLRExpr<T> &, const SLRExpr<T> &);

    friend SLRExpr<T> operator*<>(const SLRExpr<T> &, const double &);
    friend SLRExpr<T> operator*<>(const double &, const SLRExpr<T> &);

    friend SLRExpr<T> operator/<>(const SLRExpr<T> &, const double &);
    friend SLRExpr<T> operator/<>(const double &, const SLRExpr<T> &);

    friend SLRExpr<T> operator+<>(const SLRExpr<T> &, const SLRExpr<T> &);
    friend SLRExpr<T> operator+<>(const SLRExpr<T> &, const double &);
    friend SLRExpr<T> operator+<>(const double &, const SLRExpr<T> &);

    friend SLRExpr<T> operator-<>(const SLRExpr<T> &, const SLRExpr<T> &);
    friend SLRExpr<T> operator-<>(const SLRExpr<T> &, const double &);
    friend SLRExpr<T> operator-<>(const double &, const SLRExpr<T> &);
    friend SLRExpr<T> operator-<>(const SLRExpr<T> &);

    void    simplify();
    void    printExpression() const;

    void operator+=(const SLRExpr<T> &);
    void operator-=(const SLRExpr<T> &);

    void operator*=(const double &);
    void operator/=(const double &);

};



#include "Expression.cpp"


#endif //SOLVEUR_EXPRESSION_H
