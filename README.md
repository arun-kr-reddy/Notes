# Notes <!-- omit from toc -->
- [Algorithms](./Algorithms.md)
- [C++](./C++.md)
- [Life](./Life.md)
- [Tools](./Tools.md)

# Plan <!-- omit from toc -->
- [Plan](#plan)
- [C++](#c)
- [DSA](#dsa)
- [Performance](#performance)
- [Scratch](#scratch)

## Plan
-  
  | #       | DSA                              | Domain                             | Extra                                                                                    |
  | ------- | -------------------------------- | ---------------------------------- | ---------------------------------------------------------------------------------------- |
  | 1       | array & hashing                  | PC basics (lec 1-3)                |                                                                                          |
  | 2       | two pointers & stack             | PC parallel programming (lec 4-7)  |                                                                                          |
  | 3       | sliding window                   | PC data parallel (lec 8-10)        | cache locality (row vs column major perf)                                                |
  | 4       | binary search & linked list      | PC cache (lec 11-12)               | implement matrix multiplication, then with tiling                                        |
  | 5 (OoO) | trees (& maybe tries)            | PC FG sync + DSL (lec 13-15)       | node based tree vs B Tree vs array based (heap)                                          |
  | 6 (OoO) | heap & backtracking              | PC trans mem + finale (lec 16-19)  |                                                                                          |
  | 7       | graphs                           | CUDA basics (lec 1-4)              | implement BFS in CUDA                                                                    |
  | 8       | 1D DP                            | CUDA mem & concurrency (lec 5-7)   |                                                                                          |
  | 9       | 2D DP                            | CUDA prof & cooperation (lec 8-11) | use NSight to profile earlier implementation                                             |
  | 10      | intervals & greedy               | CUDA debug & graphs (lec 12-13)    |                                                                                          |
  | 11      | bit manipulation & math/geometry | OS revision                        | paging, context switching cost, user vs kernel space, false sharing                      |
  | 12      | advanced graphs                  | System Design for Performance      | SoC components,  designing for low latency vs high throughput, load balancing strategies |

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
- [Hwu GPGPU Lectures](https://www.youtube.com/playlist?list=PLRRuQYjFhpmvu5ODQoY2l7D0ADgWEcYAX)
- [LeetGPU](https://leetgpu.com/challenges)
- [GPU MLOps Talks (YT Channel)](https://www.youtube.com/@GPUMODE/videos) ([slides](https://github.com/gpu-mode/lectures))
- [llama.cpp CUDA kernels (Github)](https://github.com/ggml-org/llama.cpp/tree/master/ggml/src/ggml-cuda)
- SIMD Thinking [1](https://www.youtube.com/watch?v=qejTqnxQRcw) & [2](https://www.youtube.com/watch?v=qXleSwCCEvY)

## Scratch
- [Deep Learning Systems (YT Playlist)](https://www.youtube.com/playlist?list=PLGzYMymX8amNyGPuJ35YWdq59eQ5jYCZ1)
- [Operating Systems (YT Playlist)](https://www.youtube.com/playlist?list=PLF2K2xZjNEf97A_uBCwEl61sdxWVP7VWC)
- [Compilers (YT Playlist)](https://www.youtube.com/playlist?list=PLTsf9UeqkRebOYdw4uqSN0ugRShSmHrzH)
- [Machine Learning (YT Playlist)](https://www.youtube.com/playlist?list=PLoROMvodv4rNH7qL6-efu_q2_bPuy0adh)
- [Performance Engineering (YT Playlist)](https://www.youtube.com/playlist?list=PLUl4u3cNGP63VIBQVWguXxZZi0566y7Wf)