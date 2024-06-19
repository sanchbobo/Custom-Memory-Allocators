# Custom-Memory-Allocators

## Overview
This project provides a custom memory allocator for C++ applications. It includes implementations for linear and free list memory allocation strategies, and an STL allocator adapter to integrate with C++ standard containers.

## Features
- **Linear Allocator**: Efficient for scenarios with a predictable allocation and deallocation pattern.
- **Free List Allocator**: Manages memory dynamically with varying block sizes, suitable for general-purpose use.
- **STL Allocator Adapter**: Allows the custom allocators to be used with standard template library (STL) containers.

## Project Structure
- /include - Contains all header files.
  - Allocator.hpp
  - LinearAllocator.hpp
  - FreeListAllocator.hpp
  - STLAllocatorAdapter.hpp
- /src - Contains implementation files.
  - Allocator.cpp
  - LinearAllocator.cpp
  - FreeListAllocator.cpp
  - main.cpp
- /docs - Documentation for the project.
- /tests - Unit tests for the allocator implementations.

## Getting Started

### Prerequisites
- A modern C++ compiler supporting C++20 (e.g., GCC, Clang)
- CMake (optional for building the project using the provided `CMakeLists.txt`)

### Building the Project
To build the project using CMake:
1. Navigate to the root directory of the project.
2. Run the following commands:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
