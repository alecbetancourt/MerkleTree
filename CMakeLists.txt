cmake_minimum_required(VERSION 3.10)   # CMake version check
project(MerkleTree)               # Create project "simple_example"
set(CMAKE_C_STANDARD 11)            # Enable c++11 standard

set(SOURCE_FILES merkleTree.c sha1.c sha1.h)            # Add main.cpp file of project root directory as source file
add_executable(MerkleTree ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable