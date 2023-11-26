cmake_minimum_required(VERSION 3.5.1)
project(lab4 C)
set(SRC src/lab4_default.c)

find_package(BLAS REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${BLAS_LIBRARIES})
