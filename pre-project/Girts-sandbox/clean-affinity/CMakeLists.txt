cmake_minimum_required(VERSION 3.28)
project(clean_affinity)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(run_tests
        src/proteins.cpp
        src/compact.cpp
        src/lattice.cpp
        src/run_tests.cpp
        src/fastaffinity.cpp
        include/fastaffinity.hpp
        include/pose.hpp
        include/proteins.hpp
        include/compact.hpp
        include/lattice.hpp
        include/residue.hpp
)

add_executable(run_catch2_tests
        src/run_catch2_tests.cpp
        src/catch2.cpp
        src/proteins.cpp
        src/compact.cpp
        src/lattice.cpp
        include/catch2.hpp
)
