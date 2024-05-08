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
        classes/Graph.cpp)
