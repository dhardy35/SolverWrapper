//
// Created by adrien_bedel on 09/09/19.
//

#include <ConstraintExpression.h>
#include <Expression.h>
#include "Model.h"

template <typename T>
void SLRModel<T>::printExpression(const SLRConstrExpr<T> &constrExpr) const
{
    std::cout << "Constraint : " << std::endl << " - ";
    printExpression(constrExpr._expr);
    std::cout << " - Sign       : " << constrExpr._sign << "=";
    std::cout << std::endl << " - Constraint : " << constrExpr._constr << std::endl;
}

template <typename T>
SLRVar<T>    SLRModel<T>::getVarByName(const std::string &name)
{
    auto idx = std::find(_varsVector.begin(), _varsVector.end(), name);
    if (idx != _varsVector.end())
        return (*idx);
    throw SLRException(030306, "SLRModel::getVarByName", "Variable name not known");
}

template <typename T>
bool        SLRModel<T>::hasSolution() const
{
    return (_solutionState >= 0);
}

template <typename T>
double      SLRModel<T>::getObjectiveError(const SLRExpr<T> &expr) const
{
    double error = 0.0;
    for (int i = 0; i < expr._varIndex; ++i)
    {
        if (expr._vars[i].size() == 2)
        {
            error += expr._vars[i][0].get() * expr._vars[i][1].get() * expr._coeffs[i];
        }
        else if (expr._vars[i].size() == 1)
        {
            error += expr._vars[i][0].get() * expr._coeffs[i];
        }
    }
    error += expr._constant;
    return error;
}


#ifdef GRB

// set always env as true, which means env is empty
template <typename T>
SLRModel<T>::SLRModel() : _solutionState(0), _nbVar(0)
{
    _env.start();
    _model = std::make_shared<GRBModel>(_env);
}

template <typename T>
GRBQuadExpr      SLRModel<T>::SLRExprToGRBQuadExpr(const SLRExpr<T> &expr)
{
    GRBQuadExpr finalExpr = 0.0;
    for (int i = 0; i < expr._varIndex; i++)
    {
        if (expr._vars[i].size() == 2)
        {
            finalExpr += _vars[std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][0]))] * _vars[std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][1]))] * expr._coeffs[i];
        }
        else
        {
            finalExpr += _vars[std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][0]))]  * expr._coeffs[i];
        }
    }
    finalExpr += expr._constant;
    return (finalExpr);
}

template <typename T>
GRBLinExpr      SLRModel<T>::SLRExprToGRBLineExpr(const SLRExpr<T> &expr)
{
    GRBLinExpr finalExpr;
    for (int i = 0; i < expr._vars.size(); i++)
    {
        if (expr._vars[i].size() == 2)
        {
            throw SLRException(030602, "SLRModel::SLRExprToGRBLineExpr", "only linear constraints are allowed");
        }
        else
        {
            finalExpr += _vars[std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][0]))]  * expr._coeffs[i];
        }
    }
    finalExpr += expr._constant;
    return (finalExpr);
}

template <typename T>
void     SLRModel<T>::setObjective(const SLRExpr<T> &expr, int goal)
{
    std::cout << expr._varIndex << " " << expr._vars.size() << std::endl;
    GRBQuadExpr grbExpr = SLRExprToGRBQuadExpr(expr);
    std::cout << grbExpr.size() << " " << expr._varIndex << " " << expr._vars.size() << std::endl;
    _model->setObjective(grbExpr, goal);
}

template <typename T>
void     SLRModel<T>::addConstr(const SLRConstrExpr<T> &constrExpr, const std::string &name)
{
    GRBLinExpr grbExprRight = SLRExprToGRBLineExpr(constrExpr._exprRight);
    GRBLinExpr grbExprLeft = SLRExprToGRBLineExpr(constrExpr._exprLeft);
    _model->addConstr(grbExprLeft, constrExpr._sign, grbExprRight, name);
}

template <typename T>
void    SLRModel<T>::optimize()
{
    // temporary not doing anything
/*
    for (int i = 0; i < _varsVector.size(); i++)
    {
        std::cout << _varsVector[i].getSolution() << std::endl;
        _vars[i].set(GRB_DoubleAttr_Start, _varsVector[i].getSolution());
    }*/

    _model->optimize();
    _solutionState = _model->get(GRB_IntAttr_SolCount);
    for (int i = 0;_solutionState > 0 && i < _vars.size(); i++)
    {
        _varsVector[i].set(_vars[i].get(GRB_DoubleAttr_X));
    }
}

template <typename T>
SLRVar<T>   SLRModel<T>::addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
{
    std::string validName = name;
    if (name == "")
        validName = "myVar_" + std::to_string(_nbVar);

    SLRVar<T> variable(lowerBound, upperBound, solution, validName);
    _varsVector.push_back(variable);
    _nbVar++;

    if (std::is_same<T, bool>::value)
        _vars.push_back(_model->addVar(lowerBound, upperBound, solution, GRB_BINARY, name));
    else if (std::is_same<T, int>::value)
        _vars.push_back(_model->addVar(lowerBound, upperBound, solution, GRB_INTEGER, name));
    else if (std::is_same<T, float>::value || std::is_same<T, double>::value)
        _vars.push_back(_model->addVar(lowerBound, upperBound, solution, GRB_CONTINUOUS, name));
    else
        throw SLRException(031005, "Model::addVar", "Unknown type");
    return (variable);
}

template <typename T>
void        SLRModel<T>::update()
{
    _model->update();
}

template <typename T>
void        SLRModel<T>::set(GRB_IntParam flag, int todo)
{
    if (flag == GRB_IntParam_Threads)
        _model->set(GRB_IntParam_Threads, todo);
    else if (flag == GRB_IntParam_Presolve)
        _model->set(GRB_IntParam_Presolve, todo);
}

template <typename T>
void        SLRModel<T>::set(GRB_DoubleParam flag, float todo)
{
    if (flag == GRB_DoubleParam_TimeLimit)
        _model->set(GRB_DoubleParam_TimeLimit, todo);
}

template <typename T>
void        SLRModel<T>::printDebug(const bool &state)
{
    _model->set(GRB_IntParam_OutputFlag, state);
}


template <typename T>
void    SLRModel<T>::printResult()
{
    for (auto const &var : _vars)
    {
        std::cout << var.get(GRB_StringAttr_VarName) << " "
                  << var.get(GRB_DoubleAttr_X) << std::endl;
    }
}


#elif OSQP

template <typename T>
SLRModel<T>::SLRModel() : _nbVar(0), _nbConstr(0), _solutionState(0), _constant(0.f)
{
    _quadricNb = 0;
    _isObjectivSet = false;
}

template <typename T>
SLRVar<T>   SLRModel<T>::addVar(const T &lowerBound, const T &upperBound, const T &solution, const std::string &name)
{
    std::string validName = name;
    if (name == "")
        validName = "myVar_" + std::to_string(_nbVar);

    SLRVar<T> variable(lowerBound, upperBound, solution, validName);
    _varsVector.push_back(variable);
    _nbVar++;

    return (variable);
}

template <typename T>
void SLRModel<T>::updateVariableConstraints()
{

    for (auto const &var : _varsVector)
    {
        std::vector<double> constrCoeff(_nbVar, 0.0);
        _lowerBound.push_back(var.getLowerBound());
        _upperBound.push_back(var.getUpperBound());
        constrCoeff[std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), var))] = 1.0;
        _constrCoeffs.push_back(constrCoeff);
        _nbConstr++;
    }
}

template <typename T>
void SLRModel<T>::setObjective(const SLRExpr<T> &expr, int goal)
{
    _isObjectivSet = true;
    std::vector<std::vector<double>> fullMatrix(_nbVar, std::vector<double>(_nbVar, 0.0));

    updateVariableConstraints();

    _objLinearCoeffs = std::vector<double>(_nbVar, 0.0);
    long firstVarIndex;
    long secondVarIndex;
    for (int i = 0; i < expr._vars.size(); i++)
    {
        firstVarIndex = std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][0]));
        if (expr._vars[i].size() == 2)
        {
            secondVarIndex = std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][1]));
            fullMatrix[std::min(firstVarIndex, secondVarIndex)][std::max(firstVarIndex, secondVarIndex)] += expr._coeffs[i];
            _quadricNb++;
        }
        else if (expr._vars[i].size() == 1)
        {
            _objLinearCoeffs[firstVarIndex] += expr._coeffs[i];
        }
    }

    _quadricNb = 0;
    for (int i = 0; i < _nbVar; i++)
    {
        for (int j = 0; j < _nbVar; j++)
        {
            if (fullMatrix[j][i] != 0.0)
            {
                _quadricNb++;
            }
       }
    }
    std::cout << "qua = " << _quadricNb << std::endl;
    _objQuadricCoeffs = std::vector<double>(_quadricNb, 0.0);
    _objCoeffsRaws = std::vector<c_int>(_quadricNb, 0);
    _objCoeffsColumns = std::vector<c_int>(_nbVar + 1, 0);

    _quadricNb = 0;
    for (int i = 0; i < _nbVar; i++)
    {
        for (int j = 0; j < _nbVar; j++)
        {
            if (fullMatrix[j][i] != 0.0)
            {
                if (j == i)
                    fullMatrix[j][i] *= 2.0;
                _objQuadricCoeffs[_quadricNb] = fullMatrix[j][i];
                _objCoeffsRaws[_quadricNb] = j;
                _objCoeffsColumns[i + 1]++;
                _quadricNb++;
            }
        }
    }
    _objCoeffsColumns[0] = 0;
    for (int i = 1; i < _nbVar + 1; i++)
    {
        _objCoeffsColumns[i] += _objCoeffsColumns[i - 1];
    }
    _constant = expr._constant;
}

template <typename T>
void         SLRModel<T>::addConstr(const SLRConstrExpr<T> &constrExpr, const std::string &name)
{
    // only linear constraints
    std::vector<double> constrCoeff(_nbVar, 0.0);
    auto expr = constrExpr._exprLeft - constrExpr._exprRight;
    double constant = -expr._constant;
    for (int i = 0; i < expr._vars.size(); i++)
    {
        if (expr._vars[i].size() > 1)
            throw SLRException(031502, "SLRModel::addConstr", "only linear constraints are allowed");
        constrCoeff[std::distance(_varsVector.begin(), std::find(_varsVector.begin(), _varsVector.end(), expr._vars[i][0]))] += expr._coeffs[i];
    }
    _constrCoeffs.push_back(constrCoeff);
    if (constrExpr._sign == SLR_EQUAL)
    {
        _lowerBound.push_back(constant);
        _upperBound.push_back(constant);
    }
    else if (constrExpr._sign == SLR_LESS_EQUAL)
    {
        _lowerBound.push_back(std::numeric_limits<double>::lowest());
        _upperBound.push_back(constant);
    }
    else if (constrExpr._sign == SLR_GREATER_EQUAL)
    {
        _lowerBound.push_back(constant);
        _upperBound.push_back(std::numeric_limits<double>::max());
    }
    _nbConstr++;
}

template <typename T>
void    SLRModel<T>::printOSQPVariables(OSQPData &data)
{
    std::cout << "Begin ----------" << std::endl;
    std::cout << data.m << std::endl;
    std::cout << data.n << std::endl;
    std::cout <<  data.A->nzmax<< std::endl << "x = ";

    for (int i = 0; i < data.A->nzmax; i++)
        std::cout << data.A->x[i] << " ";
    std::cout << std::endl << "i = ";
    for (int i = 0; i < data.A->nzmax; i++)
        std::cout << data.A->i[i]<< " ";
    std::cout << std::endl << "p = ";
    for (int i = 0; i < data.n + 1; i++)
        std::cout << data.A->p[i] << " ";
    std::cout << std::endl << "l = ";
    for (int i = 0; i < data.m; i++)
        std::cout << data.l[i] << " ";
    std::cout << std::endl << "u = ";
    for (int i = 0; i < data.m; i++)
        std::cout << data.u[i] << " ";

    std::cout << std::endl;
    std::cout << "A.NZ = " << data.A->nz << std::endl;
    std::cout << "A.N = " << data.A->n << std::endl;
    std::cout << "A.M = " << data.A->m << std::endl;
    std::cout <<  data.P->nzmax<< std::endl << "x = ";

    for (int i = 0; i < data.P->nzmax; i++)
        std::cout << data.P->x[i] << " ";
    std::cout << std::endl << "i = ";
    for (int i = 0; i < data.P->nzmax; i++)
        std::cout << data.P->i[i] << " ";
    std::cout << std::endl << "p = ";
    for (int i = 0; i < data.n + 1; i++)
        std::cout << data.P->p[i] << " ";
    std::cout << std::endl << "q = ";
    for (int i = 0; i < data.n; i++)
        std::cout << data.q[i] << " ";
       std::cout << std::endl;
    std::cout << "P.NZ = " << data.P->nz << std::endl;
    std::cout << "P.N = " << data.P->n << std::endl;
    std::cout << "P.M = " << data.P->m << std::endl;
    std::cout << "End ----------" << std::endl;

}

template <typename T>
void    SLRModel<T>::fillData()
{
    unsigned int nonZeroCoeffNb = 0;
    for (int i = 0; i < _constrCoeffs.size(); i++)
    {
        for (int j = 0; j < _constrCoeffs[i].size(); j++)
        {
            if (_constrCoeffs[i][j] != 0.0)
                nonZeroCoeffNb++;
        }
    }
    _constrLinearCoeffs = std::vector<double>(nonZeroCoeffNb, 0.0);
    _constrCoeffsRaws = std::vector<c_int>(nonZeroCoeffNb, 0);
    _constrCoeffsColumns = std::vector<c_int>(_nbVar + 1, 0);

    nonZeroCoeffNb = 0;
    for (int i = 0; i < _constrCoeffs[0].size(); i++)
    {
        for (int j = 0; j < _constrCoeffs.size(); j++)
        {
            if (_constrCoeffs[j][i] != 0.0)
            {
                _constrLinearCoeffs[nonZeroCoeffNb] = _constrCoeffs[j][i];
                _constrCoeffsRaws[nonZeroCoeffNb] = j;
                _constrCoeffsColumns[i + 1]++;
                nonZeroCoeffNb++;
            }
        }
    }
    for (int i = 1; i < _nbVar + 1; i++)
    {
        _constrCoeffsColumns[i] += _constrCoeffsColumns[i - 1];
    }

    _data.m = _nbConstr;
    _data.n = _nbVar;
    _data.A = csc_matrix(_nbConstr, _nbVar, nonZeroCoeffNb, _constrLinearCoeffs.data(), _constrCoeffsRaws.data(), _constrCoeffsColumns.data());
    _data.l = _lowerBound.data();
    _data.u = _upperBound.data();
    _data.P = csc_matrix(_nbVar, _nbVar, _quadricNb, _objQuadricCoeffs.data(), _objCoeffsRaws.data(), _objCoeffsColumns.data());
    _data.q = _objLinearCoeffs.data();
}

template <typename T>
void    SLRModel<T>::optimize()
{
    if (_isObjectivSet == false)
    {
        SLRExpr<T> expr = 0.0;
        for (const auto &var : _varsVector)
            expr += var;
        setObjective(expr, SLR_MINIMIZE);
    }

    fillData();
    osqp_set_default_settings(&_settings);

    //_settings.scaling = 0;
    //_settings.polish = 1;
    //_settings.max_iter = 10000;
    _settings.verbose = 0;
    //_settings.linsys_solver = MKL_PARDISO_SOLVER;
    _settings.warm_start = 1;
    //_settings.alpha = 1;

    if (osqp_setup(&_work, &_data, &_settings) != 0)
        throw SLRException(31804, "SLRModel::optimize", "osqp_setup failed");

    _x.clear();
    for (const auto & v : _varsVector)
    {
        _x.push_back(v.get());
    }
    osqp_warm_start_x(_work, _x.data());
    osqp_solve(_work);

    _solutionState = (int)_work->info->status_val;
    std::cout << "result = " << _work->info->obj_val << std::endl;
    std::cout << "------- " << _work->info->status << " ------------" << std::endl;

    for (int i = 0; (_solutionState == 1 || _solutionState == 2 || _solutionState == -2) && i < _data.n; i++)
    {
        _varsVector[i].set(_work->solution[0].x[i]);
    }
    _lowerBound.clear();
    _upperBound.clear();
    _constrCoeffs.clear();
    _objQuadricCoeffs.clear();
    _objLinearCoeffs.clear();
    _objCoeffsRaws.clear();
    _objCoeffsColumns.clear();
    _constrLinearCoeffs.clear();
    _constrCoeffsRaws.clear();
    _constrCoeffsColumns.clear();
    _quadricNb = 0;
    _nbConstr = 0;
    _data = OSQPData();
    _settings = OSQPSettings();
    _work = new OSQPWorkspace();
}

template <typename T>
void    SLRModel<T>::printResult()
{
    /*for (int i = 0; i < _data.n; i++)
        std::cout << _work->solution[0].x[i] << " ";
    std::cout << std::endl;*/
}

template <typename T>
void        SLRModel<T>::printDebug(const bool &state)
{
    // todo
}


template <typename T>
void        SLRModel<T>::update()
{
    // todo
}

template <typename T>
SLRModel<T>::~SLRModel()
{
    /*free(_work);
    free(_data.A);
    free(_data.P);*/
}

#endif
