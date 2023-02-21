cmake_minimum_required(VERSION 3.20)

project(MonteCarlo)

include_directories(${PROJECT_SOURCE_DIR}, Examples)
add_executable(MonteCarloSimulation main.cpp ReadProgram.cpp UserDisplay.cpp WriteProgram.cpp)
