cmake_minimum_required(VERSION 3.28)
project(TSP_DA_2024)

set(CMAKE_CXX_STANDARD 14)

include_directories(classes)

add_executable(TSP_DA_2024
        classes/Dataset.cpp
        classes/Dataset.h
        classes/Graph.h
        classes/Parser.cpp
        classes/Parser.h
        main.cpp
        classes/Graph.cpp
        classes/TSP.h
        classes/TSP.cpp
        classes/Triangular.cpp
        classes/Triangular.h
        classes/MutablePriorityQueue.h
        classes/Heuristic.cpp
        classes/Heuristic.h
        classes/Prim.cpp
        classes/Prim.h)
