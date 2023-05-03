cmake_minimum_required(VERSION 3.20)
project(play_with_algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(play_with_algo UF.h UnionFind1.cpp UnionFind2.cpp UnionFind3.cpp UnionFind4.cpp main.cpp)
