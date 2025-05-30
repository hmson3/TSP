cmake_minimum_required(VERSION 3.10)
project(tsp_assignment2)
set(CMAKE_CXX_STANDARD 17)

# include directories
include_directories(
    common/include
    held_karp/include
    christofides_greedy/include
    christofides_2approx/include
)

# held_karp 실행 파일
add_executable(held_karp_exec
    held_karp/main.cpp
    held_karp/src/held_karp.cpp
    common/src/tsp_loader.cpp
    common/src/util.cpp
)
target_compile_options(held_karp_exec PUBLIC -Wall -Werror)

# Christofides_gree 실행 파일
add_executable(christofides_greedy_exec
    christofides_greedy/main.cpp
    christofides_greedy/src/christofides.cpp
    common/src/tsp_loader.cpp
    common/src/util.cpp
)
target_compile_options(christofides_greedy_exec PUBLIC -Wall -Werror)

# Christofides_2app 실행 파일
add_executable(christofides_2approx_exec
    christofides_2approx/main.cpp
    christofides_2approx/src/christofides.cpp
    common/src/tsp_loader.cpp
    common/src/util.cpp
)
target_compile_options(christofides_2approx_exec PUBLIC -Wall -Werror)

# my_tsp 실행 파일
add_executable(my_tsp_exec
    my_tsp/main.cpp
    my_tsp/src/my_tsp.cpp
    common/src/tsp_loader.cpp
    common/src/util.cpp
)
target_compile_options(my_tsp_exec PUBLIC -Wall -Werror)