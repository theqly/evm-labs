cmake_minimum_required(VERSION 3.5.1)
project(lab6 CXX)
set(SRC src/main.cpp)
set(CMAKE_CXX_FLAGS "-O1")

add_executable(${PROJECT_NAME} ${SRC})
