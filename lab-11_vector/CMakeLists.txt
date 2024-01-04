cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME lab-11_vector)
set(COMMON_SOURCES src/main.cpp include/my_vector.hpp include/my_vector_impl.hpp)

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES src/main.cpp ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
target_include_directories(${X_PROJECT_NAME} PRIVATE include)
