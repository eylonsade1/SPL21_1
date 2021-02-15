# cmake_minimum_required(VERSION <specify CMake version here>)
project(SPL1)

set(CMAKE_CXX_STANDARD 11)

add_executable(SPL1 src/main.cpp include/Session.h include/Graph.h include/Agent.h include/Tree.h include/Agent.h include/json.hpp src/Session.cpp src/Graph.cpp src/Agent.cpp src/Tree.cpp)