cmake_minimum_required(VERSION 3.9)
project(BigLib)

set(CMAKE_CXX_STANDARD 11)

add_executable(BigLib main.cpp big_n.cpp big_q.cpp big_z.cpp include include/big_p.h big_p.cpp test.cpp test.h)