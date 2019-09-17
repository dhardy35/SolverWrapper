# SolverWrapper
A wrapper to switch between Gurobi and OSQP  

# RFC  
Error Code is build in three parts :  
Class Number + Function Number + Error Number  
ex :   
    02            12                03           ->   021203  
    
    
Error Numbers :   
01 = memory alloc failed  
02 = only linear constraints are allowed  
03 = three dimensional is not allowed  
04 = osqp_setup failed  
