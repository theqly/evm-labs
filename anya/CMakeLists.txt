cmake_minimum_required(VERSION 3.5.1)
project(anya CXX)

set(CMAKE_CXX_STANDARD 11)

set(SRC anya.cpp)

add_executable(${PROJECT_NAME} ${SRC})

