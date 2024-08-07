cmake_minimum_required(VERSION 3.28)
project(cmake_unit_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(cmake_unit_tests
        src/factorial.cpp
        src/factorial_tests.cpp)
