#include "LinearAllocator.hpp"
#include "STLAllocatorAdapter.hpp"
#include <vector>
#include <chrono>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
constexpr std::size_t numElements = 100000; // Number of integers to allocate

int main() {
    char* buffer = new char[numElements * sizeof(int)]; // Allocate buffer
    LinearAllocator linearAllocator(10 * numElements * sizeof(int), buffer);
    STLAllocatorAdapter<int, LinearAllocator> linearAdapter(&linearAllocator);

    auto start = Clock::now();
    {
        std::vector<int, STLAllocatorAdapter<int, LinearAllocator>> myVector(linearAdapter);
        for (size_t i = 0; i < numElements; ++i) {
            myVector.push_back(i);
        }
    }
    auto end = Clock::now();
    std::cout << "Linear Allocator time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    // Repeat for STL Allocator for comparison
 	auto startSTL = Clock::now();
    {
        std::vector<int> myVectorSTL;
        for (size_t i = 0; i < numElements; ++i) {
            myVectorSTL.push_back(i);
        }
    }
    auto endSTL = Clock::now();
    std::cout << "STL Allocator time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endSTL - startSTL).count() << " ms\n";
    delete[] buffer; // Free the allocated buffer
    return 0;
}
