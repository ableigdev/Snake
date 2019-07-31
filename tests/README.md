# Instruction
This folder contains tests for the snake game.

If you want to build unit tests, you must have to install [Conan](https://conan.io) and [CMake](https://cmake.org/). And also you must have Visual Studio 2017.

## How to build?

In this folder you must follow the next instruction:

    mkdir build && cd build
    conan install .. -s compiler.version=15 -s build_type=Release
    cmake .. -G "Visual Studio 15 Win64" -DCMAKE_BUILD_TYPE=Release
    cmake --build . 