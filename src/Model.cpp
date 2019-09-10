//
// Created by adrien_bedel on 09/09/19.
//

#include "Model.h"
#include "Expression.h"

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

    __varsVector.push_back(variable);

    return (variable);
}

#ifdef GRB
template <typename T>
void SLRModel<T>::setObjective(const SLRExpr<T> &expr, int goal)
{
    std::cout << "GurobiSolver" << std::endl;
}
#elif OSQP
template <typename T>
void SLRModel<T>::setObjective(const SLRExpr<T> &expr, int goal)
{
    std::cout << "OSQPSolver" << std::endl;
}
#endif