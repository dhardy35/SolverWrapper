//
// Created by adrien_bedel on 09/09/19.
//

#ifndef SOLVEUR_EXPRESSION_H
#define SOLVEUR_EXPRESSION_H

#include "Variable.h"
#include "Model.h"

template <typename T> class SLRExpr;


template <typename T> SLRExpr<T> operator*(const SLRVar<T> &x, const SLRVar<T> &y);
template <typename T> SLRExpr<T> operator*(const double &, const SLRVar<T> &);
template <typename T> SLRExpr<T> operator*(const SLRVar<T> &, const double &);
template <typename T> SLRExpr<T> operator+(const double &, SLRExpr<T> );
template <typename T> SLRExpr<T> operator+(const SLRVar<T> &, SLRExpr<T> );
template <typename T> SLRExpr<T> operator+(const SLRVar<T> &, const SLRVar<T> &);

template <typename T>
class SLRExpr
{
private:
    double                              _constant;
    std::vector<double>                 _coeffs;
    std::vector<std::vector<SLRVar<T>>> _vars;
    std::vector<SLRVar<T>>              _var;
    unsigned int                        _varIndex;

    SLRExpr(const SLRVar<T> &);
    SLRExpr(const SLRVar<T> &, const double &);
    SLRExpr(const SLRVar<T> &, const SLRVar<T> &);
    void    simplify();

public:

    friend class SLRModel<T>;

    SLRExpr() = delete;

    friend SLRExpr<T> operator*<>(const SLRVar<T> &, const SLRVar<T> &);
    friend SLRExpr<T> operator*<>(const double &, const SLRVar<T> &);
    friend SLRExpr<T> operator*<>(const SLRVar<T> &, const double &);
    friend SLRExpr<T> operator+<>(const double &, SLRExpr<T> );
    friend SLRExpr<T> operator+<>(const SLRVar<T> &, SLRExpr<T> );
    friend SLRExpr<T> operator+<>(const SLRVar<T> &, const SLRVar<T> &);
    SLRExpr<T> operator*(const double &);
    SLRExpr<T> operator*(const SLRVar<T> &);
    SLRExpr<T> operator+(const double &);
    SLRExpr<T> operator+(const SLRVar<T> &);
    SLRExpr<T> operator+(const SLRExpr<T> &);

};



#include "Expression.cpp"


#endif //SOLVEUR_EXPRESSION_H
