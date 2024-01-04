cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME lab-09_figures)
set(COMMON_SOURCES src/Circle.cpp src/Figure.cpp src/Rectangle.cpp src/Scheme.cpp include/Circle.hpp include/Figure.hpp include/Rectangle.hpp include/Scheme.hpp)

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES src/main.cpp ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)