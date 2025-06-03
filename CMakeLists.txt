
cmake_minimum_required (VERSION 3.18)

project ("SketchSolver")

# Recursively find all source and header files
file(GLOB PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/SketchSolver.h"
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable (SketchSolver "examples/example.cpp" ${PROJECT_SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SketchSolver PROPERTY CXX_STANDARD 20)
endif()
