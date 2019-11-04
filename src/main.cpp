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

int main() {
    /*float m[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    float A[3] = {1, 0.5, 0};
    float B[3] = {0, 1, 0};
    float C[3] = {0, 0, 1};

    SLRModel<double> model;

    //model.printDebug(false);

    SLRVar<double> M[9];

    for (int i = 0; i < 9; i++) {
        M[i] = model.addVar(-1000.0f, 1000.0f, m[i]);
    }
    model.addConstr(M[0] * A[0] + M[1] * B[0] + M[2] * C[0] == 1.);
    model.addConstr(M[0] * A[1] + M[1] * B[1] + M[2] * C[1] == 0.);
    model.addConstr(M[0] * A[2] + M[1] * B[2] + M[2] * C[2] == 0.);

    model.addConstr(M[3] * A[0] + M[4] * B[0] + M[5] * C[0] == 0.);
    model.addConstr(M[3] * A[1] + M[4] * B[1] + M[5] * C[1] == 1.);
    model.addConstr(M[3] * A[2] + M[4] * B[2] + M[5] * C[2] == 0.);

    model.addConstr(M[6] * A[0] + M[7] * B[0] + M[8] * C[0] == 0.);
    model.addConstr(M[6] * A[1] + M[7] * B[1] + M[8] * C[1] == 0.);
    model.addConstr(M[6] * A[2] + M[7] * B[2] + M[8] * C[2] == 1.);

    model.optimize();

    for (int i = 0; i < 9; i++) {
        m[i] = M[i].getSolution();
        std::cout << m[i] << " ";
    }
    std::cout << std::endl;*/

        // Create an environment
    try {


        // Create an empty model
        SLRModel<double> model;

        // Create variables
        std::vector<SLRVar<double>> vars;
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
        for (auto &var : vars)
            std::cout << var.get() << std::endl;
    }
    catch (const SLRException &e)
    {
            std::cerr << e.getMessage() << std::endl;
    }


        /*
        x = model.getVarByName("x");
        y = model.getVarByName("y");
        z = model.getVarByName("z");
        SLRExpr<double> expr;
        expr -= 0.5 / (x + y - 2 * z) + 4;
        expr += (z * z + 2) * (y * y - 1);
        // Set objective: maximize x + y + 2 z
        model.setObjective(expr, SLR_MAXIMIZE);

        // Add constraint: x + 2 y + 3 z <= 4
        model.addConstr(4 - x - 2 * y >= 3 * z, "c0");

        // Add constraint: x + y >= 1
        model.addConstr(x + y >= 1, "c1");

        // Optimize model
        model.optimize();

        model.printResult();
    std::cout << model._varsVector[0].get() << " "
     << model._varsVector[1].get() << " "
    << model._varsVector[2].get() << " " << std::endl;
         */
        /*}
        catch (const GRBException &e)
        {
            std::cerr << e.getMessage() << std::endl;
        }*/

        /*try
        {
            SLRModel<double> model;

            SLRVar<double> x = model.addVar(0.0, 1.0, 0.0, "x");
            SLRVar<double> y = model.addVar(0.0, 1.0, 0.0, "y");
            SLRVar<double> z = model.addVar(0.0, 1.0, 0.0, "z");
            x = model.getVarByName("x");
            y = model.getVarByName("y");
            z = model.getVarByName("z");
            SLRExpr<double> expr;
            SLRExpr<double> member1;
            SLRExpr<double> member2;
            SLRExpr<double> member3;
            SLRExpr<double> member4;
            member1 = x + y;
            member3 = x + y;
            member2 = y + z ;
            member4 = y + z ;
            expr += member1 * member3;

            model.setObjective(expr, SLR_MAXIMIZE);
            model.addConstr(x + 2 * y + 3 * z <= 4, "c0");
            model.addConstr(x + y >= 1, "c1");
            model.optimize();
            model.printResult();
        }
        catch (const GRBException &e)
        {
            std::cerr << e.getMessage() << std::endl;
        }
        return 0;*/
}

