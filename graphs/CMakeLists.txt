cmake_minimum_required(VERSION 3.13)
project(johnson_algo CXX)

include_directories(algos)

add_executable(
    main
    main.cpp
    algos/graph.cpp
    algos/algos.cpp
)
