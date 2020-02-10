//
// Created by adrien_bedel on 09/09/19.
//

#include <vector>
#include <iostream>
#include "Model.h"
#ifndef GRB
#ifndef OSQP
#error compile selecting one solver, i.e. include in compiler parameters: -DOSQP or -DGRB
#endif
#endif
#define SIZE 20

int main()
{
    try {
        // Create an empty model
        SLRModel<double> model;

        // Create variables
        std::vector<SLRVar<double>> vars;
        model.printDebug(false);
        for (int i = 0; i < SIZE; i++)
        {
            vars.push_back(model.addVar(0.0, 10.0, 0.0, "x" + std::to_string(i)));
        }
        SLRExpr<double> expr = 10.f;
        for (int i = 1; i < SIZE; i++)
        {
            expr += (vars[i] - vars[i - 1]) * (vars[i] - vars[i - 1]);
        }
        model.setObjective(expr, SLR_MINIMIZE);
        model.addConstr(vars[0] >= 8.0, "c0");
        model.addConstr(vars[SIZE - 1] <= 2.0, "c0");
        model.optimize();
        std::cout << model.getObjectiveError(expr) << std::endl;
        for (auto &var : vars)
            std::cout << var.get() << std::endl;
    }
    catch (const SLRException &e)
    {
        std::cerr << e.getMessage() << std::endl;
    }
}

