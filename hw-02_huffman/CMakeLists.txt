cmake_minimum_required(VERSION 3.16)

set(X_PROJECT_NAME hw-02_huffman)
set(COMMON_SOURCES
        "include/huffman_tree.h" src/huffman_tree.cpp "include/util.h" src/util.cpp "include/huffman_archiver.h"
        src/huffman_archiver.cpp "include/huffman_unarchiver.h" src/huffman_unarchiver.cpp)

set(TEST_SOURCES "test/doctest.h" "test/huffman_unarchiver_test.cpp" "test/huffman_archiver_test.cpp"
        "test/huffman_archiver_test.cpp" "test/test.cpp" "test/util_test.cpp" )

project(${X_PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror)

set(MAIN_SOURCES src/main.cpp ${COMMON_SOURCES})
set(TEST_SOURCES "test/test.cpp" ${TEST_SOURCES} ${COMMON_SOURCES})

add_executable(${X_PROJECT_NAME} ${MAIN_SOURCES})
add_executable(${X_PROJECT_NAME}_test ${TEST_SOURCES})

target_include_directories(${X_PROJECT_NAME} PRIVATE "include")
target_include_directories(${X_PROJECT_NAME}_test PRIVATE "include")