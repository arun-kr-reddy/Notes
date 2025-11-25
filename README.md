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
- **Weekly:**
  |     |                                   |                                  |
  | --- | --------------------------------- | -------------------------------- |
  | 1*  | array & hashing, bit manipulation | PaCo: basics (1-3)               |
  | 2   | two pointers, stack               | PaCo: parallel programming (4-7) |
  | 3*  | linked list                       | PaCo: data parallel (8-10)       |
  | 4*  | binary search, sliding window     | PaCo: cache (11-12)              |
  | 5*  | trees, tries                      | PaCo: FG sync, DSL (13-15)       |
  | 6   | heap, greedy                      | PaCo: trans mem + finale (16-19) |
  | 7   | backtracking                      | CUDA: basics (1-4)               |
  | 8   | graphs                            | CUDA: mem & concurrency (5-7)    |
  | 9   | advanced graphs, intervals        | CUDA: prof & cooperation (8-11)  |
  | 10  | 1D DP                             | CUDA: debug & graphs (12-13)     |
  | 11  | 2D DP                             | DSP (Hexagon, HVX + NEON)        |
  | 12  | math/geometry                     | SoC Components                   |
- **CS149:**
  - Latency vs. Bandwidth: The fundamental equation of performance. Little's Law.
  - Multi-Threading Implementations: Fine-grained vs. Coarse-grained multi-threading. Simultaneous Multi-Threading (Hyperthreading).\
  - SIMD / Vectorization: Explicit vector instructions (AVX/NEON) vs. Implicit (SIMT on GPU). Predication (masking).
  - Memory Hierarchy:
    - Spatial vs. Temporal Locality.
    - Cache Coherence Protocols (MESI/MSI).
    - False Sharing (and how to fix it with padding).
    - Memory Consistency Models: Sequential Consistency vs. Relaxed/Weak Consistency (Total Store Ordering).
    - Work Distribution: Static assignment vs. Dynamic load balancing (Work Stealing queues).
  - Advanced / Differentiator Topics:
    - Interconnects: Ring, Mesh, Crossbar topologies (basic trade-offs).
    - Snooping vs. Directory-based Coherence: Scalability limits of multi-core.
    - Arithmetic Intensity: The Roofline Model (Compute-bound vs. Memory-bound).
- **CUDA:**
  - Thread Hierarchy: Grids, Blocks, Warps, Threads. Mapping 1D/2D/3D problems to them.
  - Memory Types:
    - Global Memory: Coalesced access patterns (SoA vs. AoS).
    - Shared Memory: Bank conflicts (strided access), padding, using it as a user-managed cache.
    - Registers: Register pressure and how it limits occupancy.
    - Constant/Texture Memory: Read-only caches.
  - Warp Execution: Warp divergence (control flow divergence) and masking.
  - Optimization Techniques:
    - Latency Hiding: Occupancy (active warps per scheduler).
    - Tiling: Loading data into Shared Memory to reuse it (Matrix Multiplication example).
    - Reductions: Parallel reduction trees, avoiding warp divergence in the final stages.
    - Streams & Events: Overlapping Compute (Kernel) with Transfer (Memcpy). Host-Device concurrency.
  - Atomics: Compare-and-Swap (CAS), atomicAdd. Performance cost of atomics.
- **OS:**
  - Process & Thread Management:
    - Context Switching: What actually gets saved/restored? What is the CPU cycle cost?
    - Scheduling: Preemptive vs. Cooperative. Priority Inversion. Processor Affinity (pinning threads to cores).
    - User vs. Kernel Space: The cost of a system call (ring transition). User-level threads (Green threads/Fibers).
  - Memory Management:
    - Virtual Memory: Page Tables, TLB (Translation Lookaside Buffer).
    - Page Faults: Major vs. Minor faults. The cost of a disk swap.
    - Huge Pages: Why they improve performance (reducing TLB misses).
    - Memory Allocators: malloc internals (freelists, arenas). Why standard malloc is slow in multi-threaded apps (lock contention).
  - Concurrency Primitives:
    - Locks: Mutex vs. Spinlock (when to use which?). Read-Write locks.
    - Condition Variables: The "Lost Wakeup" problem.
    - Deadlocks: 4 necessary conditions. Prevention vs. Avoidance.
- **Computer Architecture:**
  - Pipelining: Hazards (Data, Control, Structural). Stalling vs. Forwarding.
  - Branch Prediction: Static vs. Dynamic. Branch Target Buffer (BTB). Why if (sorted_data) is faster.
  - Out-of-Order Execution: Reorder Buffer (ROB), Register Renaming (eliminating false dependencies).
  - Speculative Execution: Basics only (executing instructions before knowing if they are needed).
- **C++ (Low Level):**
  - Memory & Pointers:
    - Pointers vs. References: Assembly-level difference (often none, but semantic difference matters).
    - Stack vs. Heap: Allocation costs. CPU cache implications of linked lists vs. vectors.
    - Move Semantics: std::move, r-value references (&&). Avoiding deep copies.
    - Smart Pointers: std::unique_ptr (zero overhead) vs. std::shared_ptr (atomic reference counting overhead).
  - Modern C++ for Perf:
    - constexpr: Computing at compile time.
    - inline: Hinting the compiler to remove function call overhead.
    - Templates: Code generation. SFINAE (basics).
    - Memory Order: std::memory_order_relaxed, acquire, release. (Critical for lock-free structures).
    - Padding & Alignment: alignas, struct packing. How order of members affects structure size.
- **Data Structures & Algorithms:**
  - Arrays/Vectors: The king of performance (Cache locality).
  - Hash Maps: Handling collisions. Resizing costs.
  - Linked Lists / Trees: Why they are "cache killers" (random memory access).
  - Heaps/Priority Queues: Array-based implementation.
  - Bit Manipulation: XOR, masking, bit-shifting (essential for systems/drivers).
  - Graphs: BFS/DFS. Adjacency Matrix (fast lookup, high memory) vs. Adjacency List (slower lookup, low memory).
- **DSP (Hexagon, HVX + NEON)**
  - Hexagon:
    - VLIW Packets: Understand how to group instructions. Hexagon executes up to 4 instructions per cycle in a "packet".
    - VLIW Latency vs Throughput
  - HVX:
    - Vector Contexts: Hexagon has hardware threading (e.g., 4 threads). HVX contexts are shared; understand temporal multithreading.
    - Sliding Window Optimization: DSPs excel at convolutions. You don't load pixels one by one; you load a "vector" and use specific sliding window instructions (vroi - Vector Rotate) to align data without memory access.
    - Circular Buffering: Hardware support for ring buffers (updating the base pointer automatically). Critical for audio/streaming data.
    - Branchless Programming (select/mux instruction or bitwise masking:)
  - ARM NEON
    - Intrinsics: Know how to read/write vld1q_f32 (Load), vaddq_f32 (Add), vst1q_f32 (Store).
    - Data Layout:
      - SoA vs. AoS: Structure of Arrays (RRRGGGBBB) is much faster for SIMD than Array of Structures (RGBRGBRGB) because you can load contiguous vectors without de-interleaving.
      - De-interleaving Loads: vld3 (Load 3-element structures) separates RGB data into 3 separate registers instantly.
- System Integration (Host <-> Device)
  - Optimizing the kernel is useless if data transfer takes too long.
  - FastRPC (Remote Procedure Call): How the Android CPU talks to the DSP.
  - Critical Concept: Zero-Copy buffers.
    - The Bottleneck: Using malloc on CPU and passing it to DSP forces a memcpy. You must use ION / DMA-BUF allocators so both CPU and DSP share the same physical RAM.
    - Cache Coherency:
    - When the CPU writes data, it sits in the CPU Cache (L2). The DSP reads from DRAM.
- Digital Signal Processing (DSP):
  - Fixed Point Arithmetic: DSPs (and AI accelerators) hate Floating Point.
    - Q-Format: Understand Q1.15 vs Q31.
    - Quantization: Converting float (32-bit) to int8 (8-bit) for 4x throughput.
    - Saturation Arithmetic:
      - Standard C: 255 + 1 = 0 (Overflow wrap-around).
      - DSP/SIMD: 255 + 1 = 255 (Saturating add). Essential for image brightness/audio volume.

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