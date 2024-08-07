cmake_minimum_required(VERSION 3.28)
project(clean_affinity)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(run_tests
        include/fastaffinity.hpp
        include/pose.hpp
        include/proteins.hpp
        src/proteins.cpp
        include/compact.hpp
        src/compact.cpp
        include/lattice.hpp
        src/lattice.cpp
        include/residue.hpp
        src/run_tests.cpp
        src/fastaffinity.cpp
)
