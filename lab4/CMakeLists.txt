cmake_minimum_required(VERSION 3.5.1)
project(lab4 CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC src/main.cpp src/matrix.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(lab4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

