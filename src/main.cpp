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

        SLRVar<double> x = model.addVar(0.0, 1.0, 0.0, "x");
        SLRVar<double> y = model.addVar(0.0, 1.0, 0.0, "y");
        SLRVar<double> z = model.addVar(0.0, 1.0, 0.0, "z");
        SLRExpr<double> expr;
        SLRExpr<double> member1;
        SLRExpr<double> member2;
        SLRExpr<double> member3;

        member1 = x * x;
        member2 = z * y * 2 * 3;
        member3 = 2 * z * z * -1;
        expr = expr + member1;
        expr = expr + member2;
        expr = expr + member3;
        //expr = expr - y;
        expr *= 1;

        model.setObjective(expr, SLR_MAXIMIZE);
        model.addConstr(x + 2 * y + 3 * z <= 4, "c0");
        model.addConstr(x + y >= 1, "c1");
        model.optimize();
        model.printResult();
    }
    catch (const SLRException &e)
    {
        std::cerr << e.fullErrorInfos() << std::endl;
    }
    return 0;
}

