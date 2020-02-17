# SolverWrapper
A Solver wrapper to switch between Gurobi and OSQP  

# RFC  
Error Code is build in three parts :  
Class Number + Solver Number + Error Number  
ex :   
    2            01                03           ->   20103  
    
Class Numbers:
1 = ConstraintExpression
2 = Expression
3 = Model
4 = SLRException
5 = Variable

Solver Numbers:
00 = works for every solver
01 = Gurobi Solver
02 = OSQP Solver

Error Numbers :   
01 = Variable name not known  
02 = only linear constraints are allowed  
03 = Unknown type   
04 = osqp_setup failed   
05 = Time limit must be positive  
