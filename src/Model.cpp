//
// Created by adrien_bedel on 09/09/19.
//

#include <ConstraintExpression.h>
#include "Model.h"


template <typename T>
SLRModel<T>::SLRModel() : _nbVar(0)
{
#ifdef OSQP
    _quadricNb = 0;
#endif
}

template <typename T>
void SLRModel<T>::printExpression(const SLRExpr<T> &expr) const
{
    std::cout << "Expression : ";
    for (int i = 0; i <= expr._varIndex; i++)
    {
        if (expr._coeffs[i] != 1)
            std::cout << expr._coeffs[i];
        for (int j = 0; j < expr._vars[i].size(); j++)
        {
            std::cout << expr._vars[i][j].getName();
        }
        std::cout << " ";
        if (i != expr._varIndex)
            std::cout << "+";
        std::cout << " ";
    }
    if (expr._constant != 0)
        std::cout << "+ " << expr._constant;
    std::cout << std::endl;
}

template <typename T>
void SLRModel<T>::printExpression(const SLRConstrExpr<T> &constrExpr) const
{
    std::cout << "Constraint : " << std::endl << " - ";
    printExpression(constrExpr._expr);
    std::cout << " - Sign       : ";
    if (constrExpr._sign == INF)
        std::cout << "<=";
    else if (constrExpr._sign == SUP)
        std::cout << ">=";
    else if (constrExpr._sign == EQUAL)
        std::cout << "==";
    std::cout << std::endl << " - Constraint : " << constrExpr._constr << std::endl;
}

template <typename T>
SLRVar<T>   SLRModel<T>::addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
{
    SLRVar<T>   variable(lowerBound, upperBound, solution, name);

    _varsVector.push_back(variable);
    _nbVar++;

    return (variable);
}

template <typename T>
void SLRModel<T>::updateVariableConstraints()
{

    for (auto const &var : _varsVector)
    {
        std::vector<double> constrCoeff(_nbVar, 0);
        _lowerBound.push_back(var.getLowerBound());
        _upperBound.push_back(var.getUpperBound());
        constrCoeff[var[_varsVector]] = 1;
        _constrCoeffs.push_back(constrCoeff);
    }
}


#ifdef GRB
template <typename T>
int SLRModel<T>::setObjective(const SLRExpr<T> &expr, int goal)
{
    std::cout << "GurobiSolver" << std::endl;
}
#elif OSQP
template <typename T>
int SLRModel<T>::setObjective(const SLRExpr<T> &expr, int goal)
{
    double   fullMatrix[_nbVar][_nbVar] = {0};

    updateVariableConstraints();
    _linearCoeffs = (c_float *)malloc(sizeof(c_float) * _nbVar);
    for (int i = 0; i < expr._vars.size(); i++)
    {
        if (expr._vars[i].size() == 2)
        {
            fullMatrix[expr._vars[i][0][_varsVector]][expr._vars[i][1][_varsVector]] = expr._coeffs[i];
            _quadricNb++;
        }
        else
        {
            _linearCoeffs[expr._vars[i][0][_varsVector]] = expr._coeffs[i];
        }
    }
    _quadricCoeffs = (c_float *)malloc(sizeof(c_float) * _quadricNb);
    _coeffsRaws = (c_int *)malloc(sizeof(c_int) * _quadricNb);
    _coeffsColumns = (c_int *)malloc(sizeof(c_int) * (_nbVar + 1));

    memset(_coeffsColumns, 0, sizeof (c_int) * _quadricNb);
    _quadricNb = 0;
    for (int i = 0; i < _nbVar; i++)
    {
        for (int j = 0; j < _nbVar; j++)
        {
            if (fullMatrix[j][i] != 0)
            {
                if (i != j)
                    fullMatrix[j][i] /= 2.f;
                _quadricCoeffs[_quadricNb] = fullMatrix[j][i];
                _coeffsRaws[_quadricNb] = j;
                _coeffsColumns[i + 1]++;
                _quadricNb++;
            }
        }
    }
    _coeffsColumns[0] = 0;
    for (int i = 1; i < _quadricNb; i++)
    {
        _coeffsColumns[i] += _coeffsColumns[i - 1];
    }

    printExpression(expr);
    return (1);
}

template <typename T>
int         SLRModel<T>::addConstr(const SLRConstrExpr<T> &constrExpr, const std::string &name)
{
    // only linear constraints

    printExpression(constrExpr);
    std::vector<double> constrCoeff(_nbVar, 0);
    for (int i = 0; i < constrExpr._expr._vars.size(); i++)
    {
        constrCoeff[constrExpr._expr._vars[i][0][_varsVector]] = constrExpr._expr._coeffs[i];
    }
    _constrCoeffs.push_back(constrCoeff);
    if (constrExpr._sign == EQUAL)
    {
        _lowerBound.push_back(constrExpr._constr);
        _upperBound.push_back(constrExpr._constr);
    }
    else if (constrExpr._sign == INF)
    {
        _lowerBound.push_back(std::numeric_limits<double>::min());
        _upperBound.push_back(constrExpr._constr);
    }
    else if (constrExpr._sign == SUP)
    {
        _lowerBound.push_back(constrExpr._constr);
        _upperBound.push_back(std::numeric_limits<double>::max());
    }
    return (1);
}

template <typename T>
void    SLRModel<T>::optimize()
{
    c_int nonZeroCoeffNb = 0;
    for (int i = 0; i < _constrCoeffs.size(); i++)
    {
        for (int j = 0; j < _constrCoeffs[i].size(); j++)
        {
            if (_constrCoeffs[i][j] != 0)
                nonZeroCoeffNb++;
        }
    }
    c_float   *nonZeroCoeffs = (c_float*)malloc(sizeof(c_float) * nonZeroCoeffNb);
    c_int   *coeffsRaws = (c_int*)malloc(sizeof(c_int) * nonZeroCoeffNb);
    c_int   *coeffsColumns = (c_int*)malloc(sizeof(c_int) * (_nbVar + 1));

    memset(coeffsColumns, 0, sizeof(c_int) * _nbVar);

    nonZeroCoeffNb = 0;
    for (int i = 0; i < _constrCoeffs[0].size(); i++)
    {
        for (int j = 0; j < _constrCoeffs.size(); j++)
        {
            if (_constrCoeffs[j][i] != 0)
            {
                nonZeroCoeffs[nonZeroCoeffNb] = _constrCoeffs[j][i];
                coeffsRaws[nonZeroCoeffNb] = j;
                coeffsColumns[i + 1]++;
                nonZeroCoeffNb++;
            }
        }
    }
    for (int i = 1; i < _nbVar + 1; i++)
    {
        coeffsColumns[i] += coeffsColumns[i - 1];
    }

    c_float *lowerBound = (c_float *)malloc(sizeof(c_float) * _lowerBound.size());
    c_float *upperBound = (c_float *)malloc(sizeof(c_float) * _upperBound.size());
    std::copy(_lowerBound.begin(), _lowerBound.end(), lowerBound);
    std::copy(_upperBound.begin(), _upperBound.end(), upperBound);

    _data.m = _constrCoeffs.size();
    _data.n = _nbVar;
    _data.A = csc_matrix(_data.m, _nbVar, nonZeroCoeffNb, nonZeroCoeffs, coeffsRaws, coeffsColumns);
    _data.l = lowerBound;
    _data.u = upperBound;
    _data.P = csc_matrix(_nbVar, _nbVar, _quadricNb, _quadricCoeffs, _coeffsRaws, _coeffsColumns);
    _data.q = _linearCoeffs;

    c_int exitflag = 0;
    osqp_set_default_settings(&_settings);
    _settings.alpha = 1.0; // Change alpha parameter
    exitflag = osqp_setup(&_work, &_data, &_settings);
    osqp_solve(_work);
    std::cout << _work->solution[0].x[0] << " " << _work->solution[0].x[1] << std::endl;
    //return exitlag;
}

#endif