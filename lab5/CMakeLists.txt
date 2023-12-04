cmake_minimum_required(VERSION 3.5.1)
project(lab5 CXX)
set(SRC src/cache.cpp)
set(CMAKE_CXX_FLAGS "-O1")

add_executable(${PROJECT_NAME} ${SRC})
