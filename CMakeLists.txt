cmake_minimum_required(VERSION 3.18)
project(IB109 C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_CXX_LINK_EXECUTABLE g++)
SET(CMAKE_CXX_COMPILER g++)

add_executable(IB109 main.c)



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -g")