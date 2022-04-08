cmake_minimum_required(VERSION 3.10)
project(test_env)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXECUTABLE_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH
    ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "-Wall -g -Wno-unused-variable -Wno-unused-function")

add_library(
    sort STATIC

    src/sort.cpp
)

add_library(
    tree STATIC

    src/tree.cpp
)

add_executable(
    test_sort

    src/test_sort.cpp
)

add_executable(
    test_tree

    src/test_tree.cpp
)

target_link_libraries(
    test_sort

    sort
)

target_link_libraries(
    test_tree

    tree
)

target_compile_options(
    test_sort

    PRIVATE
    -g
)

target_compile_options(
    test_tree

    PRIVATE
    -g
)
