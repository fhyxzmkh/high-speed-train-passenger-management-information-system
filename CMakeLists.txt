cmake_minimum_required(VERSION 3.29)
project(demo)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo main.cpp menu.cpp myRandom.cpp passenger.cpp train.cpp)
