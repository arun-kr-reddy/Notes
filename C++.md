# C++ <!-- omit from toc -->
- [Standard Template Library](#standard-template-library)
  - [Containers](#containers)
- [Misc](#misc)

# Plan <!-- omit from toc -->
- [C++ Features (by version)](https://github.com/AnthonyCalandra/modern-cpp-features)
- **Core Language Features:**
  - Object-Oriented Programming:
    - classes & objects
    - encapsulation
    - inheritance
    - polymorphism
    - RAII, rule of 0/3/5
  - Memory:
    - pointers & references
    - dynamic allocations
    - smart pointers
    - misc memory
      - representations
        - sign extension, int promotion
      - fixed vs floating point
      - type qualifiers
      - linkage
      - storage duration
      - storage class
      - endianess
      - memory layout
  - Templates
  - Concurrency
    - threads
    - mutex
    - futures
    - atomics
    - memory ordering
  - Misc:
    - auto
    - ranged for loop
    - bit manipulation
    - lambda
    - move semantics
    - exception & error handling
    - I/O streams
- **STL:**
  - Containers:
    - vector
      - vector of bool
    - string
    - map & unordered map
    - set & unordered set
    - adaptors
  - Algorithms (`<algorithm>`, `<numeric>`):
    - Non-modifying: `std::find`, `std::count`, `std::for_each`, `std::all_of/any_of/none_of`
    - Modifying: `std::transform`, `std::copy`, `std::fill`, `std::replace`, `std::remove`
    - Sorting & searching: `std::sort`, `std::binary_search`, `std::lower_bound/upper_bound`
    - Min/Max: `std::min`, `std::max`, `std::minmax_element`
    - Numeric: `std::accumulate`, `std::reduce`, `std::inner_product`
  - Iterators

# Standard Template Library
- **Containers:**
  - essentially data structures that stores templated elements
- **Algorithms:**
  - functions that operate on elements stored in containers using iterator-range
- **Iterators:**
  - general way to access elements in containers
- 
  ```mermaid
  graph LR
    e0[Element 0]
    e1[Element 1]
    en[Element n]

    algo[Algorithm]

    range[Iterator Range]

    subgraph Container
    e0 --> e1
    e1 -.-> en
    end

    e0 -.start.-> range
    en -.end.-> range
    range --> algo
  ```

## Containers
- **Sequence Containers:**
  - element position dictated by user
- **Associative Containers:**
  - elements stored in a way that allows fast look-up (sorted or hashed)

### String
- basically `basic_string<char>`
  - also supports other element sizes (for unicodes)
- 
  ```cpp
  #include <string>
  std::string str;

  str = another_str;                // copy assign
  char c = str.at(i);               // get element (with bounds checking)
  str += another_str;               // append operator
  str.erase(itr);                   // remove element
  str.push_back(val);               // add element at the end, pop_back()

  size_t size = str.size();         // num elements (excluding NULL)
  size_t capacity = str.capacity(); // max num elements (+ 1) possible in allocated mem
  str.reserve(size);                // reserve memory
  str.shrink_to_fit();              // dealloc unused memory
  str.clear();                      // clear string

  char *data = str.data();          // underlying C array (NULL terminated)
  if (str.find(substr) != str.npos) // index of first substring occurence
  str.swap(another_str);            // swap string contents
  ```

### Array
- fixed-size contiguous array on stack
- commonly used APIs like `size()`, `at()`, etc are `constexpr`
- 
  ```cpp
  #include <array>
  std::array<T, SIZE_MAX> arr;

  arr.fill(value); // assign value to all elements

  // =, at, size, clear, data, swap
  ```

### Vector
- dynamic-size contiguous array on heap
- 
  ```cpp
  #include <vector>
  std::vector<T> vector;

  auto val_itr = insert(itr, val); // insert element

  // =, at, erase, push_back, size, capacity, reserve, shrink_to_fit, clear, data, swap
  ```
- `insert`/`push_back` vs `emplace`/`emplace_back`:

# Misc
- C-style arrays decay to pointer when passed to function
- when to use curly brace initializer & when to use parantheses?
  ```cpp
  std::string str("hello world");
  std::array<uint32_t, 3> arr{1, 2, 3};
  ```