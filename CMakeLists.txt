cmake_minimum_required(VERSION 3.9)
project(BigLib)

set(CMAKE_CXX_STANDARD 11)

add_executable(BigLib main.cpp modules/big_n.cpp modules/big_q.cpp modules/big_z.cpp modules/big_p.cpp include test.cpp test.h)