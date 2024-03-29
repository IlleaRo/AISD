cmake_minimum_required(VERSION 3.20)
project(aisd2 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(aisd2 tester.cpp ../bst.h)
