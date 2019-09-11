//
// Created by adrien_bedel on 09/09/19.
//

#include "/home/adrien/Downloads/gurobi811/linux64/include/gurobi_c++.h"
#include "osqp.h"
#include <iostream>
#include "Expression.h"
#include "ConstraintExpression.h"

#ifndef GRB
#ifndef OSQP
#error compile selecting one solver, i.e. include in compiler parameters: -DOSQP or -DGRB
#endif
#endif


int main() {
    GRBEnv env = GRBEnv();
    OSQPWorkspace *work;

    SLRModel<float> model;

    SLRVar<float> x = model.addVar(0.0, 1.0, 0.0, "x");
    SLRVar<float> y = model.addVar(0.0, 1.0, 0.0, "y");

    model.setObjective(4 * x * x + 2 * x * y + 2 * y * y + x + y, SLR_MINIMIZE);
    model.addConstr(x + y == 1, "c0");


    return 0;
}

