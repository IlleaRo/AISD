cmake_minimum_required(VERSION 3.28)
project(RGR)

set(CMAKE_CXX_STANDARD 17)

add_executable(RGR main.cpp
        graphs/graph.h graphs/vertex.h graphs/edge.h
        graphs/forms.h)
