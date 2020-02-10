cmake_minimum_required(VERSION 2.6)
project(curvislice)

OPTION(CURVI_BUILD_WITH_GRB  "Build with GRB (stable solver)" ON)

add_subdirectory(../ EXCULDE_FROM_ALL)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../include/
                    ${PROJECT_SOURCE_DIR}/../src/)

ADD_EXECUTABLE(curvislice_osqp main.cpp)

if (CURVI_BUILD_WITH_GRB)
    ADD_EXECUTABLE(curvislice_grb main.cpp)
endif(CURVI_BUILD_WITH_GRB)

target_compile_options(curvislice_osqp PRIVATE -DOSQP)

if (CURVI_BUILD_WITH_GRB)
    target_compile_options(curvislice_grb PRIVATE -DGRB)
endif(CURVI_BUILD_WITH_GRB)


if(WIN32)
    # TODO
else()
    target_link_libraries(curvislice_osqp SolverWrapper)

    if (CURVI_BUILD_WITH_GRB)
        target_link_libraries(curvislice_grb SolverWrapper)
    endif(CURVI_BUILD_WITH_GRB)
endif(WIN32)

set_target_properties(curvislice_osqp PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        )
if (CURVI_BUILD_WITH_GRB)
    set_target_properties(curvislice_grb PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )
endif(CURVI_BUILD_WITH_GRB)

