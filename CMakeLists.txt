cmake_minimum_required(VERSION 3.0.0)
include(CMakeDependentOption)

project(SolverWrapper)

OPTION(BUILD_WITH_GRB  "Build with GRB (stable solver)" OFF)

set(GRB_VERSION "90" CACHE STRING
  "Gurobi version chosen by the user at CMake configure time")
 
set(GRB_VERSIONS "80;81;90")
 
set_property(CACHE GRB_VERSION PROPERTY STRINGS ${GRB_VERSIONS})

add_library(${PROJECT_NAME} include/Model.h include/Variable.h include/Expression.h include/ConstraintExpression.h include/SLRException.h src/SLRException.cpp)

#SLR
include_directories(include/)
include_directories(src/)
if (WIN32)
	target_link_libraries(${PROJECT_NAME} PUBLIC shlwapi)
endif(WIN32)

#modifying install directories
SET(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_INSTALL_BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin CACHE PATH "forcing install path" FORCE)

#OSQP
add_subdirectory(lib/osqp)
target_link_libraries(${PROJECT_NAME} PUBLIC osqp)

#GUROBI
if (BUILD_WITH_GRB)
	target_compile_options(SolverWrapper PRIVATE -DGRB)
	
	include_directories($ENV{GUROBI_HOME}/include)
	set_property(TARGET SolverWrapper APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES $ENV{GUROBI_HOME}/include)
	
	if(WIN32)
		target_link_libraries(${PROJECT_NAME} 			$ENV{GUROBI_HOME}/lib/gurobi${GRB_VERSION})
		target_link_libraries(${PROJECT_NAME} debug     $ENV{GUROBI_HOME}/lib/gurobi_c++mdd2017)
		target_link_libraries(${PROJECT_NAME} optimized $ENV{GUROBI_HOME}/lib/gurobi_c++md2017)
	else()
		target_link_libraries(${PROJECT_NAME} -L/$ENV{GUROBI_HOME}/lib/ -lgurobi_c++ -lgurobi${GRB_VERSION})	
	endif(WIN32)
	
endif(BUILD_WITH_GRB)

set(CMAKE_CXX_STANDARD 17 REQUIRED)
