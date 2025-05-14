cmake_minimum_required(VERSION 3.10)
project(tsp_assignment2)
set(CMAKE_CXX_STANDARD 17)

# include directories
include_directories(
    common/include
    held_karp/include
    christofides/include
)

# held_karp 실행 파일
add_executable(held_karp_exec
    held_karp/main.cpp
    held_karp/src/held_karp.cpp
    common/src/tsp_loader.cpp
    common/src/util.cpp
)
target_compile_options(held_karp_exec PUBLIC -Wall -Werror)

# Christofides 실행 파일
add_executable(christofides_exec
    christofides/main.cpp
    christofides/src/christofides.cpp
    common/src/tsp_loader.cpp
    common/src/util.cpp
)
target_compile_options(christofides_exec PUBLIC -Wall -Werror)
