cmake_minimum_required(VERSION 3.12.1)
project(SolverWrapper)

add_library(${PROJECT_NAME} include/Model.h include/Variable.h include/Expression.h include/ConstraintExpression.h include/SLRException.h src/SLRException.cpp)

#SLR
include_directories(include/)
include_directories(src/)

#OSQP
find_package(osqp REQUIRED)
include_directories(lib/osqp/)
target_link_libraries(${PROJECT_NAME} libosqp.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

#GUROBI
INCLUDE_DIRECTORIES($ENV{GUROBI_HOME}/include)
link_directories($ENV{GUROBI_HOME}/lib)
target_link_libraries(${PROJECT_NAME} -L/$ENV{GUROBI_HOME}/lib/ -lgurobi_c++ -lgurobi81)

set(CMAKE_CXX_STANDARD 17 REQUIRED)
