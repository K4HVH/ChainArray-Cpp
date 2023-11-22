# ChainArray Template Class

The `ChainArray` template class allows you to create a range of values by chaining through the elements of a given array. It generates a sequence of values by iterating through the array for a specified number of iterations, starting from a specified offset. This documentation provides an overview of the class, its constructors, and how to use it.

## Table of Contents
- [Introduction](#introduction)
- [Class Definition](#class-definition)
- [Constructors](#constructors)
- [Usage](#usage)
- [Updates](#updates)
- [Example](#example)

## Introduction

The `ChainArray` template class provides a flexible way to iterate through the elements of an array for a specified number of iterations, starting from a specified offset. It can be useful when you want to produce a sequence of values or perform operations on the elements of an array in a chained manner with a specific starting point.

## Class Definition

```cpp
template<typename T>
class ChainArray {
public:
    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        explicit iterator(const ChainArray& ca, const std::vector<T>& values, size_t currentIteration)
            : ca(ca), values(values), currentIteration(currentIteration) {}

        T operator*() const {
            return values[currentIteration];
        }

        iterator& operator++() {
            ++currentIteration;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return currentIteration != other.currentIteration;
        }

    private:
        const ChainArray& ca;
        const std::vector<T>& values;
        size_t currentIteration;

        friend class ChainArray;  // Allow ChainArray to access private members
    };

    // Constructor with array input, iterations, and starting offset
    ChainArray(const std::vector<T>& values, size_t iterations, size_t offset = 0)
        : values(values), iterations(iterations), offset(std::min(offset, values.size() - 1)) {}

    iterator begin() const {
        return iterator(*this, values, offset);
    }

    iterator end() const {
        iterator iter(*this, values, std::min(offset + iterations, values.size()));
        return iter;
    }

private:
    std::vector<T> values;
    size_t iterations;
    size_t offset;
};
```

## Constructors

### `ChainArray(const std::vector<T>& values, size_t iterations, size_t offset = 0)`

Creates a `ChainArray` object with the specified vector of values and the number of iterations, and the starting offset.

- `values` (std::vector<T>): The vector containing the elements to be iterated through.
- `iterations` (size_t): The number of iterations to perform over the input array.
- `offset` (size_t, optional, default: 0): The starting offset within the input array.

## Usage

To use the `ChainArray` class, follow these steps:

1. Include the necessary header files.
   
```cpp
#include <vector>
#include "ChainArray.hpp" // Include the header file containing the ChainArray template class.
```

2. Create a `ChainArray` object by specifying the vector of values, the number of iterations, and the starting offset.

3. Use iterators to loop through the generated sequence.

4. Perform desired operations with the generated values.

## Updates

### Update v1.1 (2023-11-23)
- `Enhancement`: Implemented the offset parameter. This allows from the output to be started from a certain position within the array.
- `Bug Fix`: Fixed a possible issue with overflow

## Example

Here's an example demonstrating how to use the `ChainArray` class:

```cpp
#include <iostream>
#include <vector>
#include "ChainRange.hpp"

int main() {
    // Create an array of values to be used.
    std::vector<int> values = {20, 3, 12, 30, 15};
    size_t iterations = 3;
    size_t offset = 1;

    // Create a ChainArray object that generates values from the values array, and iterating the first 3 times.
    ChainArray<int> range(values, iterations, offset);

    // Loop through the range and print each value.
    for (int value : range) {
        std::cout << value << " ";
    }

    std::cout << std::endl;

    return 0;
}
```

Output:
```
3 12 30
```

In this example, we created a `ChainArray` object that iterates through the elements of values for 3 iterations, starting from the second element. We then used a for loop to iterate through the generated sequence and printed each value.
