//
// Created by adrien_bedel on 09/09/19.
// class 02
//

#ifndef SOLVEUR_EXPRESSION_H
#define SOLVEUR_EXPRESSION_H

#include "Variable.h"
#include "Model.h"

template <typename T> SLRExpr<T> operator*(const SLRVar<T> &x, const SLRVar<T> &y);
template <typename T> SLRExpr<T> operator*(const double &, const SLRVar<T> &);
template <typename T> SLRExpr<T> operator*(const SLRVar<T> &, const double &);

template <typename T> SLRExpr<T> operator*(const SLRExpr<T> &, const double &);
template <typename T> SLRExpr<T> operator*(const double &, const SLRExpr<T> &);
template <typename T> SLRExpr<T> operator/(const SLRExpr<T> &, const double &);
template <typename T> SLRExpr<T> operator/(const double &, const SLRExpr<T> &);

template <typename T> SLRExpr<T> operator+(const double &, SLRExpr<T> );
template <typename T> SLRExpr<T> operator+(const SLRVar<T> &, SLRExpr<T> );
template <typename T> SLRExpr<T> operator+(const SLRVar<T> &, const SLRVar<T> &);
template <typename T> SLRExpr<T> operator+(const SLRVar<T> &, const double &);

template <typename T> SLRExpr<T> operator-(const double &, SLRExpr<T> );
template <typename T> SLRExpr<T> operator-(const SLRVar<T> &, SLRExpr<T> );
template <typename T> SLRExpr<T> operator-(const SLRVar<T> &, const SLRVar<T> &);
template <typename T> SLRExpr<T> operator-(const SLRVar<T> &, const double &);




//  _vars store the variables like it is in the equation
//  ex : 2xx + -3xy + yy + x + y
//  will be store in a double vector this way :
//  x  x  y  x  y
//  x  y  y
//  and the coeffs will be in _coeffs in the same order :
//  2 -3  1  1  1
//  Also, variables will be stored in the alphabetical order inside a column:
//  ex : 2yx + x will be :
//  x  x    and not  y  x
//  y                x
template <typename T>
class SLRExpr
{
private:
    double                              _constant;
    std::vector<double>                 _coeffs;
    std::vector<std::vector<SLRVar<T>>> _vars;
    int                                 _varIndex;

    SLRExpr(const SLRVar<T> &);
    SLRExpr(const SLRVar<T> &, const double &);
    SLRExpr(const SLRVar<T> &, const SLRVar<T> &);
    void    simplify();

public:

    friend class SLRModel<T>;
    friend class SLRConstrExpr<T>;

    SLRExpr();

    friend SLRExpr<T> operator*<>(const SLRVar<T> &, const SLRVar<T> &);
    friend SLRExpr<T> operator*<>(const double &, const SLRVar<T> &);
    friend SLRExpr<T> operator*<>(const SLRVar<T> &, const double &);

    friend SLRExpr<T> operator*<>(const SLRExpr<T> &, const double &);
    friend SLRExpr<T> operator*<>(const double &, const SLRExpr<T> &);
    friend SLRExpr<T> operator/<>(const SLRExpr<T> &, const double &);
    friend SLRExpr<T> operator/<>(const double &, const SLRExpr<T> &);

    friend SLRExpr<T> operator+<>(const double &, SLRExpr<T> );
    friend SLRExpr<T> operator+<>(const SLRVar<T> &, SLRExpr<T> );
    friend SLRExpr<T> operator+<>(const SLRVar<T> &, const SLRVar<T> &);
    friend SLRExpr<T> operator+<>(const SLRVar<T> &, const double &);

    friend SLRExpr<T> operator-<>(const double &, SLRExpr<T> );
    friend SLRExpr<T> operator-<>(const SLRVar<T> &, SLRExpr<T> );
    friend SLRExpr<T> operator-<>(const SLRVar<T> &, const SLRVar<T> &);
    friend SLRExpr<T> operator-<>(const SLRVar<T> &, const double &);

    SLRExpr<T> operator*(const SLRExpr<T> &);
    SLRExpr<T> operator*(const double &);
    SLRExpr<T> operator/(const double &);
    SLRExpr<T> operator*(const SLRVar<T> &);

    SLRExpr<T> operator+(const double &);
    SLRExpr<T> operator+(const SLRVar<T> &);
    SLRExpr<T> operator+(const SLRExpr<T> &);
    SLRExpr<T> operator+=(const SLRExpr<T> &);
    SLRExpr<T> operator*=(const double &);

    SLRExpr<T> operator-(const double &);
    SLRExpr<T> operator-(const SLRVar<T> &);
    SLRExpr<T> operator-(const SLRExpr<T> &);
    SLRExpr<T> operator-=(const SLRExpr<T> &);
    SLRExpr<T> operator/=(const double &);

};



#include "Expression.cpp"


#endif //SOLVEUR_EXPRESSION_H
