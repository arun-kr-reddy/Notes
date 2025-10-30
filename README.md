# Notes <!-- omit from toc -->
- [Algorithms](./Algorithms.md)
- [C++](./C++.md)
- [Life](./Life.md)
- [Tools](./Tools.md)

# Plan <!-- omit from toc -->
- [C++](#c)
- [DSA](#dsa)
- [Performance](#performance)
- [Scratch](#scratch)

## C++
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

## DSA
- sort implementation in C++ STL
- [Practice (NeetCode150)](https://neetcode.io/practice?tab=neetcode150)
- **Method:** ([reddit](https://www.reddit.com/r/cscareerquestions/comments/ot9ssf/comment/h6tx1vx/?utm_source=share&utm_medium=mweb3x&utm_name=mweb3xcss&utm_term=1&utm_content=share_button), [medium](https://medium.com/@rajbopche/my-preparation-for-algo-ds-193c90952d8c))
  - if no progress within first 10min then mark it (for review later), watch video solution & then code it yourself
  - short notes for each problem:
    - approach with pseducode in short
    - new trick/pattern involved
    - time & space complexity
  - give yourself time to forget and retry marked problems after 2 weeks
  - goal is to understand the problem not memorize solution
    - if you can't solve new problems then you are memorizing solutions
  - first time will take multiple months but getting back into it next time will just take weeks

## Performance
- [Parallel Computing](https://www.youtube.com/playlist?list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp) ([Notes](https://gfxcourses.stanford.edu/cs149/fall23/))]
- [OpenCL courses (YT Channel)](https://www.youtube.com/@davidblack-schaffer219/courses)
- [LeetGPU](https://leetgpu.com/challenges)
- [GPU MLOps Talks (YT Channel)](https://www.youtube.com/@GPUMODE/videos) ([slides](https://github.com/gpu-mode/lectures))
- [llama.cpp CUDA kernels (Github)](https://github.com/ggml-org/llama.cpp/tree/master/ggml/src/ggml-cuda)

## Scratch
- [Deep Learning Systems (YT Playlist)](https://www.youtube.com/playlist?list=PLGzYMymX8amNyGPuJ35YWdq59eQ5jYCZ1)
- [Operating Systems (YT Playlist)](https://www.youtube.com/playlist?list=PLF2K2xZjNEf97A_uBCwEl61sdxWVP7VWC)
- [Compilers (YT Playlist)](https://www.youtube.com/playlist?list=PLTsf9UeqkRebOYdw4uqSN0ugRShSmHrzH)
- [Machine Learning (YT Playlist)](https://www.youtube.com/playlist?list=PLoROMvodv4rNH7qL6-efu_q2_bPuy0adh)
- [Performance Engineering (YT Playlist)](https://www.youtube.com/playlist?list=PLUl4u3cNGP63VIBQVWguXxZZi0566y7Wf)