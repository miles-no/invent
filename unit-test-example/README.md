# Clean affinity

A minimalistic project with the attempt to isolate a "small chunk" of Absolut code (regarding the affinity) and write
simple unit tests for it.

The project contains proof-of-concept unit tests using two different
frameworks: [CppUnit](https://github.com/cppunit/cppunit)
and [Catch2](https://github.com/catchorg/Catch2/).

## Requirements

You should be able to build the project using the following tools:

* [CMake](https://cmake.org/) - version 3.30 used during development, but an older version probably will work just fine.
* A C++ compiler with C++11 support
* [Make](https://cplusplus.com/articles/jTbCpfjN/)

No external libraries are required.

## Build

The project is configured using CMake. To build the project, run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## Run

Inside the `build` directory, run the following command:

* To run the CppUnit tests: `./run_tests_cppunit`
* To run the Catch2 tests: `./run_tests_catch2`
