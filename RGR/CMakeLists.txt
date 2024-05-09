cmake_minimum_required(VERSION 3.22)
project(RGR)

set(CMAKE_CXX_STANDARD 17)

add_executable(RGR main.cpp
        graph/graph.h graph/parts/vertex.h graph/parts/edge.h
        graph/forms/forms.h
        graph/iterators/iterators.h
        ui/menu.cpp
        tasks/non-weighted.h
        tasks/weighted.h)
