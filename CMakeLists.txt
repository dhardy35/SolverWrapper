cmake_minimum_required(VERSION 3.12.1)
project(SolverWrapper)

add_library(${PROJECT_NAME} include/Model.h include/Variable.h include/Expression.h include/ConstraintExpression.h include/SLRException.h src/SLRException.cpp)

#SLR
include_directories(include/)
include_directories(src/)

#OSQP
if (CURVI_BUILD_WITH_OSPQ)
    message("osqp")
    add_subdirectory(lib/osqp)
    include_directories(lib/osqp/)
    target_link_libraries(${PROJECT_NAME} osqp)
endif(CURVI_BUILD_WITH_OSPQ)

if (CURVI_BUILD_WITH_GRB)
    message("grb")
    INCLUDE_DIRECTORIES($ENV{GUROBI_HOME}/include)
    link_directories($ENV{GUROBI_HOME}/lib)
    target_link_libraries(${PROJECT_NAME} -L/$ENV{GUROBI_HOME}/lib/ -lgurobi_c++ -lgurobi81)
endif(CURVI_BUILD_WITH_GRB)

set(CMAKE_CXX_STANDARD 17 REQUIRED)
