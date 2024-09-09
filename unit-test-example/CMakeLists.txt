cmake_minimum_required(VERSION 3.22)
project(clean_affinity)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(run_tests_cppunit
        src/proteins.cpp
        src/compact.cpp
        src/lattice.cpp
        src/run_cppunit_tests.cpp
)

add_executable(run_tests_catch2
        src/run_catch2_tests.cpp
        src/catch2.cpp
        src/proteins.cpp
        src/compact.cpp
        src/lattice.cpp
)
