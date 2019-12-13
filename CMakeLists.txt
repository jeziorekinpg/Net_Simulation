cmake_minimum_required(VERSION 3.15)
project(Net_Simulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Net_Simulation package.cpp types.hpp storage_types.hpp package.hpp storage_types.cpp)