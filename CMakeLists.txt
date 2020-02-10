cmake_minimum_required(VERSION 3.12.1)
project(SolverWrapper)

add_library(${PROJECT_NAME} include/Model.h include/Variable.h include/Expression.h include/ConstraintExpression.h include/SLRException.h src/SLRException.cpp)

#SLR
include_directories(include/)
include_directories(src/)

#OSQP
add_subdirectory(lib/osqp)
target_link_libraries(${PROJECT_NAME} osqp)

if (CURVI_BUILD_WITH_GRB)
    set_property(TARGET SolverWrapper APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES $ENV{GUROBI_HOME}/include)
    target_link_libraries(${PROJECT_NAME} -L/$ENV{GUROBI_HOME}/lib/ -lgurobi_c++ -lgurobi81)
endif(CURVI_BUILD_WITH_GRB)

set(CMAKE_CXX_STANDARD 17 REQUIRED)
