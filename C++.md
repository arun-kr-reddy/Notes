# C++
- [Doubts](#doubts)

## Links <!-- omit from toc -->
- [Modern C++ (UBonn, 2018)](https://www.youtube.com/playlist?list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C)

## To Do <!-- omit from toc -->
- [C++ Features (by version)](https://github.com/AnthonyCalandra/modern-cpp-features)
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
  - casting: static_cast, dynamic_cast, reinterpret_cast, and const_cast
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
    - struct padding (`alignas`)
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
  - const & constexpr

## Doubts
- C-style arrays decay to pointer when passed to function
- when to use curly brace initializer & when to use parantheses?
  ```cpp
  std::string str("hello world");
  std::array<uint32_t, 3> arr{1, 2, 3};
  ```
- all containers table with `O()` for common operations & when to use
  - in Algorithms?
- `-march=native` enables instruction & micro-architecture features supported by current CPU  
  `-mtune=native` optimizes instruction scheduling, cache behaviour & branch prediction for current CPU
- **Why Little Endian:**
  - x86/x86-64 & modern ARM uses little endian
  - addition starts with LSB, so CPU can fetch it first without knowing full width
  - address remains same regardless of whether its loaded as 8bit, 16bit or 32bit
  - odd-even from first byte
- pre-increment & post-increment overloading
- **False Sharing:** threads modify independent variables that happen to reside on same cache line  
  either pad dummy buffer between active variables or use alignment for active variables
- all operator overloading syntaxes
  ```cpp
  myType &operator++() {}   // pre increment
  myType operator++(int) {} // post increment
  ```
- bitset
- **NaN:**
  - special value used to represent results that are un-defined or in-valid  
    *example:* `0.0 / 0.0`, `inf - inf`, `sqrt(-1)`
  - NaN is not equal to anything, comparison always returns false (including itself)  
    *example:* `nan == nan`, `nan == 5`, `nan < 5`, `nan > 5` returns false
  - calculations involving NaN become NaN  
    *example:* `NaN + 10 --> NaN`, `NaN * 0 --> NaN`