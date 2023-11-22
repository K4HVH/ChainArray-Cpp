# ChainArray Template Class

The `ChainArray` template class allows you to create a range of values by chaining through the elements of a given array. It generates a sequence of values by iterating through the array for a specified number of iterations. This documentation provides an overview of the class, its constructors, and how to use it.

## Table of Contents
- [Introduction](#introduction)
- [Class Definition](#class-definition)
- [Constructors](#constructors)
- [Usage](#usage)
- [Example](#example)

## Introduction

The `ChainArray` template class provides a flexible way to iterate through the elements of an array for a specified number of iterations. It can be useful when you want to produce a sequence of values or perform operations on the elements of an array in a chained manner.

## Class Definition

```cpp
template<typename T>
class ChainArray {
public:
    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        explicit iterator(const ChainArray& ca, const std::vector<T>& values) : ca(ca), values(values), currentIteration(0) {}

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

    // Constructor with array input
    ChainArray(const std::vector<T>& values, size_t iterations) : values(values), iterations(iterations) {}

    iterator begin() const {
        return iterator(*this, values);
    }

    iterator end() const {
        iterator iter(*this, values);
        // Check if the current iteration exceeds the size of the input array
        iter.currentIteration = std::min(iterations, values.size());
        return iter;
    }

private:
    std::vector<T> values;
    size_t iterations;
};
```

## Constructors

### `ChainArray(const std::vector<T>& values, size_t iterations)`

Creates a `ChainArray` object with the specified vector of values and the number of iterations.

- `values` (std::vector<T>): The vector containing the elements to be iterated through.
- `iterations` (size_t): The number of iterations to perform over the input array.

## Usage

To use the `ChainArray` class, follow these steps:

1. Include the necessary header files.
   
```cpp
#include <vector>
#include "ChainArray.hpp" // Include the header file containing the ChainArray template class.
```

2. Create a `ChainArray` object by specifying the vector of values and the number of iterations.

3. Use iterators to loop through the generated sequence.

4. Perform desired operations with the generated values.

## Example

Here's an example demonstrating how to use the `ChainArray` class:

```cpp
#include <iostream>
#include <vector>
#include "ChainRange.hpp"

int main() {
    // Create an array of values to be used.
    std::vector<int> values = {20, 3, 12, 30};

    // Create a ChainArray object that generates values from the values array, and iterating the first 3 times.
    ChainArray<int> range(values, 3);

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
20 3 12
```

In this example, we created a `ChainArray` object that iterates through the elements of values for 3 iterations. We then used a for loop to iterate through the generated sequence and printed each value.
