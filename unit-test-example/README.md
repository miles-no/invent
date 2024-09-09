# Unit-test example

A minimalistic project with the attempt to isolate a "small chunk" of Absolut code (regarding the affinity) and write
simple unit tests for it.

The project contains proof-of-concept unit tests using two different
frameworks: [CppUnit](https://github.com/cppunit/cppunit)
and [Catch2](https://github.com/catchorg/Catch2/).

## Requirements

This project has been tested on the following platforms:

* MacOS 14
* Ubuntu 22.04

You should be able to build the project using the following Unix tools:

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

## Running on Windows

To run the unit tests on Windows, you have several options:
a) Use the WSL (Windows Subsystem for Linux) and run the tests on Ubuntu 22.04. In this case, open the WSL command line
and follow the instructions above.
b) Use Visual Studio. In this case, run the following commands:

```bash
mkdir build
cd build
cmake ..
```
A solution file will be generated inside the `build` directory. Open it with Visual Studio and run the tests there.
