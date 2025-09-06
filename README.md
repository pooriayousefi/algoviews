# AlgoViews

[![Build Status](https://github.com/pooriayousefi/algoviews/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/algoviews/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 header-only library providing composable algorithm views for data processing, analysis, and visualization. AlgoViews offers efficient, type-safe utilities for sorting, searching, matrix operations, and data size analysis.

## 🚀 Features

- **Header-Only**: Zero-compilation dependency, just include and use
- **Modern C++20**: Extensive use of concepts, ranges, and template metaprogramming
- **Composable Views**: Chain operations for complex data processing pipelines
- **Type Safety**: Compile-time validation with C++20 concepts
- **High Performance**: Template specialization and compile-time optimizations
- **Cross-Platform**: Works on Linux (g++), macOS (clang++), and Windows (MSVC)

## 🎯 Quick Start

```cpp
#include "sort_view.hpp"
#include "search_view.hpp"
#include "matrix_view.hpp"
#include "size_of_data.hpp"

#include <vector>
#include <iostream>

int main() {
    // Data size analysis
    std::string text = "Hello, AlgoViews!";
    std::cout << "Text size: " << size_of::data_in_bytes(text) << " bytes\n";
    
    // Sorting views
    std::vector<int> data{5, 2, 8, 1, 9, 3};
    auto sorted_view = sort_view::create(data);
    
    // Search operations
    auto search_result = search_view::binary_search(sorted_view, 5);
    if (search_result.found) {
        std::cout << "Found 5 at index: " << search_result.index << std::endl;
    }
    
    return 0;
}
```

## 📚 Module Reference

### `sort_view.hpp` - Sorting Views
Efficient sorting algorithms with view-based interface.

### `search_view.hpp` - Search Operations  
High-performance search algorithms with result metadata.

### `matrix_view.hpp` - Matrix Operations
Efficient matrix operations with lazy evaluation.

### `size_of_data.hpp` - Data Size Analysis
Memory usage analysis for various data types.

### `iterate.hpp` - Enhanced Iteration
Advanced iteration utilities with functional programming support.

### `concepts.hpp` - Type Constraints
C++20 concepts for algorithm constraints and type safety.

## 🏗️ Building from Source

```bash
# Clone repository
git clone https://github.com/pooriayousefi/algoviews.git
cd algoviews

# Build with default settings
cmake --preset=default
cmake --build build/default

# Run the demo
./build/default/algoviews_demo
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/algoviews](https://github.com/pooriayousefi/algoviews)
