//
// Created by adrien_bedel on 09/09/19.
//

#include <vector>
#include <iostream>
#include "Expression.h"
#include "ConstraintExpression.h"

#ifndef GRB
#ifndef OSQP
#error compile selecting one solver, i.e. include in compiler parameters: -DOSQP or -DGRB
#endif
#endif


int main()
{
    try
    {
        SLRModel<double> model;

        SLRVar<double> x = model.addVar(0.0, 1.7, 0.0, "x");
        SLRVar<double> y = model.addVar(0.6, 0.7, 0.0, "y");
        SLRVar<double> z = model.addVar(-1.0, -0.7, 0.0, "z");
        SLRExpr<double> le;
        SLRExpr<double> l;
        le = 2 * x * 2 * x - 3 * 3 * x * y;
        le /= 2.f;
        l = z * z * 2 * 2;
        le -= l;
        model.setObjective(le, SLR_MINIMIZE);
        //model.addConstr(x + -2 >= -2 + -1 * z + -2 * y, "c1");
        model.addConstr(x + y + z >= 1, "c0");
        //model.addConstr(x + 2 * y + z + 1 == 10, "c1");
        model.optimize();
        model.printResult();
    }
    catch (const SLRException &e)
    {
        std::cerr << e.fullErrorInfos() << std::endl;
    }
    return 0;
}

