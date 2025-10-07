# C++
- [Standard Template Library](#standard-template-library)

## Plan <!-- omit from toc -->
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

## Standard Template Library
- ```mermaid
  graph TD
    e1[Element 1]
    e2[Element 2]
    e3[Element 3]
    en[Element n]

    algo[Algorithm]

    range[Iterator Range]

    subgraph Container
    e1 --> e2
    e2 --> e3
    e3 -..-> en
    end

    e1 -.-> range
    en -.-> range
    range --> algo
  ```
- **Containers:**
  - essentially data structures that stores templated elements
- **Algorithms:**
  - functions that operate on elements stored in containers using iterator range
- **Iterators:**
  - general way to access elements in containers

### Containers
- **Sequence Containers:**
  - element position dictated by user
- **Associative Containers:**
  - elements stored in a way that allows fast look-up

#### String
- basically `basic_string<char>`
  - also supports other element sizes (for unicodes)
- ```cpp
  #include <string>
  std::string str; // std::string str("hello world");

  char c = str.at(i); // get element (with bounds checking)
  str = another_str;  // copy assign
  str += another_str; // append operator
  str.erase(itr);     // remove element (character)
  str.push_back(val); // add element at the end, pop_back(), alternate to `emplace_back`

  size_t size = str.size();         // num elements
  size_t capacity = str.capacity(); // num elements (+ 1 for end) in currently allocated mem
  str.reserve(size);                // reserve memory, optional arg for initializing new elements
  str.shrink_to_fit();              // dealloc unused memory
  str.clear();                      // clear string

  char *data = str.data();          // underlying C array (null terminated)
  if (str.find(substr) != str.npos) // index of first substring occurence
  str.swap(another_str);            // swap string contents
  ```

#### Array
- fized-size array allocated on stack
- commonly used APIs like `size()`, `at()`, etc are `constexpr`
- ```cpp
  #include <array>
  std::array<T, SIZE_MAX> arr; // std::array<uint32_t, 3> arr{1, 2, 3};

  arr.fill(value) // assign value to all elements

  // =, empty, size, data, at(i), clear, swap
  ```

## Misc
- C-style arrays decay to pointer when passed to function
- when to use curly brace initializer & when to use parantheses?
  ```cpp
  std::string str("hello world");
  std::array<uint32_t, 3> arr{1, 2, 3};
  ```