cmake_minimum_required(VERSION 3.20)
project(aisd2_tester CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(tester tester.cpp ../bst.h)
