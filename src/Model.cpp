//
// Created by adrien_bedel on 09/09/19.
//

#include <Expression.h>
#include "Model.h"
#include "Expression.h"


template <typename T>
SLRModel<T>::SLRModel() : _nbVar(0)
{
#ifdef OSQP
    _quadricNb = 0;
#endif
}

template <typename T>
void SLRModel<T>::printExpression(const SLRExpr<T> &expr)
{
    std::cout << "Expression is : ";
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
    std::cout << std::endl;
}

template <typename T>
SLRVar<T>   SLRModel<T>::addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
{
    SLRVar<T>   variable(lowerBound, upperBound, solution, name);

    _varsVector.push_back(variable);
    _nbVar++;

    return (variable);
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
    _coeffsPositions = (c_int **)malloc(sizeof(c_int) * 2);
    _coeffsPositions[RAW] = (c_int *)malloc(sizeof(c_int) * _quadricNb);
    _coeffsPositions[RAW] = (c_int *)malloc(sizeof(c_int) * _quadricNb);
    _coeffsPositions[COLUMN] = (c_int *)malloc(sizeof(c_int) * _quadricNb);

    memset(_coeffsPositions[COLUMN], 0, sizeof (_coeffsPositions[COLUMN]) * _quadricNb);
    _quadricNb = 0;
    for (int i = 0; i < _nbVar; i++)
    {
        for (int j = 0; j < _nbVar; j++)
        {
            if (fullMatrix[i][j] != 0)
            {
                if (i != j)
                    fullMatrix[i][j] /= 2.f;
                _quadricCoeffs[_quadricNb] = fullMatrix[i][j];
                _coeffsPositions[RAW][_quadricNb] = i;
                _coeffsPositions[COLUMN][j + 1]++;
                _quadricNb++;
            }
        }
    }
    _coeffsPositions[COLUMN][0] = 0;
    for (int i = 1; i < _quadricNb; i++)
    {
        _coeffsPositions[COLUMN][i] += _coeffsPositions[COLUMN][i - 1];
    }
}

template <typename T>
int         SLRModel<T>::addConstr(const SLRExpr<T> &expr, const std::string &name)
{





    c_float A_x[4] = {1.0, 1.0, 1.0, 1.0, };
    c_int A_nnz = 4;
    c_int A_i[4] = {0, 1, 0, 2, };
    c_int A_p[3] = {0, 2, 4, };
    c_float l[3] = {1.0, 0.0, 0.0, };
    c_float u[3] = {1.0, 0.7, 0.7, };
    c_int n = 2;
    c_int m = 3;

    // Exitflag
    c_int exitflag = 0;

    // Workspace structures
    //OSQPWorkspace *work;
    //OSQPSettings  settings;
    //OSQPData      data;
    _data.m = m;
    _data.n = _nbVar;

    _data.A = csc_matrix(_data.m, _data.n, A_nnz, A_x, A_i, A_p);
    _data.l = l;
    _data.u = u;
    _data.P = csc_matrix(_data.n, _data.n, _quadricNb, _quadricCoeffs, _coeffsPositions[RAW], _coeffsPositions[COLUMN]);
    _data.q = _linearCoeffs;
    std::cout << "n = " << _data.n << std::endl;

    // Define solver settings as default
    osqp_set_default_settings(&_settings);
    _settings.alpha = 1.0; // Change alpha parameter

    // Setup workspace
    exitflag = osqp_setup(&_work, &_data, &_settings);

    // Solve Problem
    osqp_solve(_work);

    std::cout << _work->solution[0].x[0] << " " << _work->solution[0].x[1] << std::endl;
    // Cleanup
    return exitflag;
}

#endif