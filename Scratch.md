# Scratch
- [Resources](#resources)
- [NeetCode 150 12-Week Plan](#neetcode-150-12-week-plan)
- [Domain-Specific](#domain-specific)
- [Modern C++](#modern-c)

## Resources
- [GPUMode GPU Puzzles](https://github.com/srush/gpu-puzzles)
- [Lei Mao Optimization Blogs](https://leimao.github.io/article/CUDA-Matrix-Multiplication-Optimization/)
- [Tushar Gautam GPU videos](https://www.youtube.com/playlist?list=PLU0zjpa44nPXddA_hWV1U8oO7AevFgXnT)
- [DSA Graph Theory Visualizations](https://www.youtube.com/playlist?list=PLpXOY-RxVRTPPVLBP6-sz6CMWxhtrI-v_)
- [Compilers](https://www.youtube.com/playlist?list=PLTsf9UeqkRebOYdw4uqSN0ugRShSmHrzH)
- [OLCF CUDA](https://www.youtube.com/playlist?list=PL6RdenZrxrw-zNX7uuGppWETdxt_JxdMj)
- [GPU Mode](https://www.youtube.com/@GPUMODE/videos)
- [Deep Learning Systems (GPU implementation of DL algos)](https://www.youtube.com/playlist?list=PLT6QPhVMICSa30axDNX9nljqaTeuftC8t)
- [Machine Learning](https://www.youtube.com/playlist?list=PLoROMvodv4rNH7qL6-efu_q2_bPuy0adh)

## NeetCode 150 12-Week Plan
- *Workload balanced by cognitive difficulty: ~8.5 to 9.5 hours pure solving + ~1.5 hours review buffer per week.*
  | Week | Topics Covered                                           | E / M / H Split | #   |
  | ---- | -------------------------------------------------------- | --------------- | --- |
  | 1    | Arrays & Hashing (9), Two Pointers (5)                   | 4E / 9M / 1H    | 14  |
  | 2    | Sliding Window (6), Stack (6)                            | 2E / 7M / 3H    | 12  |
  | 3    | Binary Search (7), Bit Manipulation (7)                  | 6E / 7M / 1H    | 14  |
  | 4    | Linked List (11)                                         | 3E / 6M / 2H    | 11  |
  | 5    | Trees (15)                                               | 6E / 7M / 2H    | 15  |
  | 6    | Heap / Priority Queue (7), Intervals (6)                 | 2E / 8M / 3H    | 13  |
  | 7    | Backtracking (10), Tries (3)                             | 0E / 10M / 3H   | 13  |
  | 8    | Graphs (13)                                              | 0E / 12M / 1H   | 13  |
  | 9    | Greedy (8), Math & Geometry Pt. 1: 2D Matrices (4)       | 2E / 10M / 0H   | 12  |
  | 10   | Advanced Graphs (6), Math & Geometry Pt. 2: Numerics (4) | 1E / 6M / 3H    | 10  |
  | 11   | 1-D Dynamic Programming (12)                             | 2E / 10M / 0H   | 12  |
  | 12   | 2-D Dynamic Programming (11)                             | 0E / 7M / 4H    | 11  |

## Domain-Specific

### Stanford CS149
- **Watch Lectures 1–6 (Foundations):**
  - *Lec 1–2:* Multi-core architectures, SIMD vectorization vs. hardware multi-threading.
  - *Lec 3:* ISPC programming model and abstraction layers.
  - *Lec 4–5:* Work distribution, dynamic load balancing, and work-stealing algorithms.
  - *Lec 6:* Locality, communication costs, and arithmetic intensity (FLOPs/Byte).
- **SKIP Lectures 7–8:** GPU Architecture basics (covered with deeper rigor in PMPP).
- **Watch Lectures 9–11 (Massive ROI for Resume):**
  - *Lec 9:* Deep Neural Network evaluation on GPUs (`im2col`, layer fusion, GEMM lowering).
  - *Lec 10:* Hardware Specialization (Design of custom deep-learning ASICs, systolic arrays, SRAM line buffers).
  - *Lec 11:* **Domain-Specific Programming Systems (Halide):** Decoupling algorithm from schedule (`compute_at`, `store_at`, `tile`, `vectorize`, loop sliding).
- **Watch Lectures 13–14 (Hardware-Software Interface):**
  - *Lec 13:* Cache Coherence (MSI/MESI/MOESI snooping vs. directory-based protocols, false sharing).
  - *Lec 14:* Memory Consistency Models (Sequential consistency, relaxed consistency, hardware memory fences).
- **SKIP Lectures 12, 15, 16, 17:** Heterogeneous datacenter interconnects, transactional memory.

### Izzat El Hajj’s PMPP
- **Watch Lectures 3–7 (GPU Micro-architecture):**
  - *Lec 3–4:* Scalable execution, Warp scheduling, SIMT branch divergence, latency hiding.
  - *Lec 5:* Memory hierarchies and Shared Memory / SRAM tiling.
  - *Lec 6:* **DRAM Bandwidth Optimization:** Memory coalescing rules and Shared Memory **Bank Conflicts** (padding techniques).
  - *Lec 7:* Dynamic Occupancy and Profiling (`nvprof` / Nsight Compute roofline).
- **Watch Lectures 8–11 (The "Big 4" Parallel Interview Kernel Patterns):**
  - *Lec 8:* **2D Convolution:** Shared-memory tiling with halo/ghost cell boundary handling.
  - *Lec 9:* **Parallel Reduction:** Eliminating warp divergence and bank conflicts in tree reduction.
  - *Lec 10:* **Parallel Prefix Sum (Scan):** Kogge-Stone (work-inefficient) vs. Brent-Kung (work-efficient) parallel scan.
  - *Lec 11:* **Parallel Histogram:** Shared-memory privatization + atomic contention reduction.
- **Watch Supplementary & Advanced Lectures:**
  - *Supplementary Lecture:* **Advanced Optimizations for Matrix Multiplication:** Register tiling, double-buffering, and outer-product data reuse.
  - *Chapter 14 (Part 1):* **Sparse Matrix Computation:** Compressed Sparse Row (CSR) and ELLPACK formats on vector hardware.
- **SKIP Lectures 12, 13, 15–24:** GPU merge sort, dynamic parallelism, graph algorithms on GPUs, MRI case studies.

### Firmware, SoC Architecture & DMA (Filling the Resume Blind Spot)
- **Cache Coherency across Heterogeneous SoCs:**
  - **Non-coherent DMA vs. CPU Caches:** When the CPU must perform a **Cache Clean/Flush** (write-back dirty L1/L2 lines to DDR *before* an inbound DMA/accelerator read) vs. a **Cache Invalidate** (discard stale L1/L2 lines *before* the CPU reads output written to DDR by an outbound DMA).
- **Memory Pipeline & Zero-Copy Sharing:**
  - **IOMMU / SMMU:** How scatter-gather DMA handles pages that are virtually contiguous in process memory but physically fragmented in DRAM.
  - **Zero-Copy Pipelines:** Buffer sharing across ISP $\rightarrow$ DSP $\rightarrow$ GPU using Linux `DMA-BUF` / Android ION tokens without `memcpy`.
- **Host-to-Accelerator Firmware IPC & Scheduling:**
  - Memory-mapped register architectures: Doorbell registers, circular command-ring descriptors, and completion rings.
  - Interrupt handling: Top-half (fast hardware ACK / clear register) vs. Bottom-half (deferred processing / worker thread dispatch), interrupt coalescing, and hardware watchdog hang recovery.
- **Best Video Resources:**
  - **Channel — *Core Dumped* (YouTube):** Visual deep dives on *Virtual Memory/TLB*, *DMA & Interrupts*, and *Multicore Cache Coherency*.
  - **Embedded Linux Conference (ELC) Talks (YouTube):** *"DMA-BUF: Sharing Buffers Between Devices"* and *"Understanding DMA and Cache Coherency on ARM"*.
  - **Prof. Onur Mutlu (ETH Zürich Computer Architecture on YouTube):** Lectures on *Virtual Memory* and *Main Memory / DRAM Bank Structure*.

### 4. Edge-AI, Halide & Quantization
- **Fixed-Point & Quantization Math (HVX / NEON / DSP Core):**
  - Symmetric vs. Asymmetric `INT8` quantization: Scaling factor ($S$) and Zero-point ($Z$) mapping real values $X = S \times (q - Z)$.
  - Per-channel vs. Per-tensor quantization trade-offs.
  - Dot-product accumulation safety: Widening accumulate (`int8 * int8 -> int16 -> int32` accumulators) + saturating arithmetic with rounding shifts.
- **Roofline Model & Operator Fusion:**
  - Arithmetic Intensity calculation ($\text{FLOPs} / \text{Byte}$).
  - Identifying memory-bandwidth-bound layers (LayerNorm, ReLU, Elementwise Add, Softmax) vs. compute-bound layers (dense GEMM, large-channel Convolutions).
  - Operator Fusion: Combining Conv + Bias + ReLU + Pooling into a single execution pass to keep intermediates in L2/TCM and eliminate DDR round-trips.
- **Halide Whiteboard Mechanics:**
  - Explaining loop nest transforms: `.split()`, `.tile()`, `.vectorize()`, `.parallel()`, `.compute_at()`, and `.store_at()`.
  - The fundamental trade-off: **Locality vs. Redundant Recomputation vs. Parallelism**.
- **Best Video Resources:**
  - **MIT 6.5940: TinyML and Efficient Deep Learning Computing (Prof. Song Han on YouTube):** Lectures 3 & 4 (*Quantization*) and Lectures 10 & 11 (*On-Device Kernel Optimization*).
  - **Talk — Jonathan Ragan-Kelley (YouTube):** *"Halide: Decoupling Algorithms from Schedules"*.
  - **Channel — *GPU MODE* (YouTube):** Lecture 1 (*Roofline Model & Profiling*) and Umar Jamil’s *FlashAttention* breakdown (tiled online-softmax in SRAM).

### 5. The "Systems & Compute Coding 15" Hands-On Drills
- **Memory & Pointer Drills:**
  1. `aligned_malloc(size_t size, size_t alignment)` and `aligned_free(void* ptr)` supporting arbitrary power-of-2 alignments (e.g., 64-byte or 128-byte HVX vectors) by storing the original base pointer offset.
  2. Custom `memmove(void* dest, const void* src, size_t n)`: Safely handling overlapping memory ranges (backward copy vs. forward copy) with word-aligned 64-bit chunk copies.
  3. Fixed-Size Block Memory Pool Allocator: Intrusive free-list over a pre-allocated `uint8_t buffer[N]` providing deterministic $O(1)$ allocations with zero fragmentation.
- **Concurrency & IPC Drills:**
  4. Circular Ring Buffer (Array-backed): Index wrap-around handling, full/empty checks, and overwrite-oldest variant.
  5. Thread-Safe Producer-Consumer Queue: Wrapping a ring buffer with `std::mutex` and `std::condition_variable` (predicated wait to prevent spurious wakeups).
  6. Lock-Free Single-Producer Single-Consumer (SPSC) Queue: Using `std::atomic<size_t>` read/write indices with `memory_order_acquire` and `memory_order_release`.
  7. Software Timer / Callback Scheduler: Min-heap priority queue tracking registered timestamps paired with a worker thread/condition variable dispatching callbacks.
- **Bit Manipulation & Register Drills:**
  8. Arbitrary Bitfield Extractor / Inserter: Read/write `k` bits at bit offset `p` across an unaligned `uint8_t*` byte stream.
  9. Fast Bit Hacks: Branchless power-of-2 check (`(n & (n - 1)) == 0`), rounding up to next power of 2, 32-bit byte-swap, and popcount using SWAR or a 256-entry lookup table.
  10. 64-Bit Bitmap Allocator: Tracking hardware slot availability in $O(1)$ using `uint64_t` bitmasks and compiler built-ins (`__builtin_ctzll`).
- **Compute & Matrix Drills:**
  11. 2D Separable Convolution / Box Filter: Flattened 1D array (`uint8_t* img, int width, int height, int stride`), boundary clamping, handling `stride != width`.
  12. Cache-Friendly Tiled Matrix Transpose: Transposing $N \times M$ matrix using $B \times B$ block sub-tiles to eliminate cache-line thrashing.
  13. Sparse Matrix-Vector Multiplication (SpMV): Compressed Sparse Row (CSR) format representation (`values`, `col_indices`, `row_ptr`) multiplied by a dense vector.

## Modern C++

### 1. STL Internals, Complexity & Cache Locality
- **`std::vector` Architecture & Implementation Drill *(Systems 15)*:**
  - Implement a minimal `Vector<T>` from scratch handling raw heap allocation, geometric reallocation (growth factor 1.5x vs. 2x), placement `new`, and explicit destruction (`T::~T()`).
  - `size()` vs. `capacity()`, `reserve()` vs. `resize()`, `push_back()` vs. `emplace_back()`.
  - Iterator/pointer invalidation rules on reallocations.
  - **The `noexcept` Move Trap:** Why `std::vector` copies instead of moves elements during growth unless the move constructor is marked `noexcept`.
- **Associative Containers & Memory Topology:**
  - `std::unordered_map` internal chaining: Why separate chaining with heap-allocated bucket nodes ruins cache locality through pointer chasing.
  - Knowing when to choose flat open-addressing hash maps (`absl::flat_hash_map`) or a sorted contiguous `std::vector` + `std::lower_bound` ($O(\log N)$ with zero cache misses).
  - `std::deque`: Array of fixed-size memory blocks (provides $O(1)$ head/tail operations without full reallocation, but elements are not contiguous in physical memory).
  - `std::priority_queue`: Binary heap over `std::vector`; understanding why `std::make_heap` runs in $O(N)$ linear time while $N$ insertions take $O(N \log N)$.
- **Modern Non-Owning Views (C++17/20/23):**
  - `std::string` and Short String Optimization (SSO): In-object buffer optimization for strings $\le 15\text{–}22$ bytes.
  - `std::span<T, Extent>`: Safe buffer slicing for SIMD/DSP kernels without pointer decay or heap allocation; static extent (`std::span<float, 128>`) for compile-time size checking and loop unrolling.
  - `std::mdspan` (C++23): Multidimensional array access over flat 1D memory buffers with explicit layouts (`layout_right` row-major, `layout_stride` for row-padded camera/image frames).

### 2. Memory Management, Object Lifetime & RAII
- **Value Categories & Move Semantics:**
  - Distinguishing lvalues, xvalues, and prvalues.
  - Understanding that `std::move` performs zero runtime movement (strictly a compile-time cast to an rvalue reference `static_cast<T&&>`).
  - Perfect forwarding via universal/forwarding references (`T&&`) and reference collapsing rules using `std::forward<T>`.
  - **Rule of 0 / 3 / 5:** Destructors, copy constructors, copy assignment, move constructors, move assignment.
  - Mandatory Copy Elision / RVO / NRVO in C++17+.
- **Smart Pointer Internals & Custom Deleters *(Systems 15)*:**
  - Implement minimal `UniquePtr<T>` and `SharedPtr<T>` classes from scratch.
  - `std::unique_ptr`: Stateless lambda/functor deleters utilizing **Empty Base Optimization (EBO)** so `sizeof(unique_ptr) == 8` bytes (raw pointer size).
  - `std::shared_ptr` & `std::weak_ptr`: Control block layout (strong ref count, weak ref count, allocator, custom deleter). Thread-safety invariants: control block mutations are atomic; pointed-to object mutations are not.
  - `std::make_shared` single-allocation trade-off: Combines control block and object into one heap allocation, but prevents freeing object memory until all `weak_ptr`s reach zero.
- **Low-Level Memory Layout & Hardware Boundaries:**
  - **Placement `new`:** Constructing objects at explicit memory locations (`new (address) T(...)`) and invoking manual destruction (`ptr->~T()`).
  - **Struct Alignment & Padding:** `alignas` / `alignof`, compiler field reordering, and cache-line padding using `alignas(std::hardware_destructive_interference_size)` (64 or 128 bytes) to prevent **false sharing** in multi-threaded firmware.

### 3. Templates, Compile-Time C++ & Zero-Cost Abstractions
- **`C++26 std::simd` & Vector Abstractions:**
  - Explaining how template abstractions wrap HVX/NEON intrinsics without assembly overhead.
  - Vector types parameterized by element type `T` and ABI tag (`simd_abi::native` vs. `fixed_size<N>`).
  - Masked operations (`where(mask, v)`), memory load/store alignment tags (`vector_aligned` vs. `element_aligned`).
- **Compile-Time Branching:**
  - `constexpr` functions vs. `consteval` (C++20 immediate compile-time functions) vs. `constinit`.
  - **`if constexpr` (C++17):** Discarding untaken branches at compile time (essential for architecture-specific code generation without runtime branches).
- **Constraining Interfaces:**
  - **C++20 Concepts and `requires` clauses:** Replacing verbose `std::enable_if` SFINAE templates with constrained types (`template<std::floating_point T>`, `std::is_trivially_copyable_v`).
- **Static vs. Dynamic Polymorphism:**
  - Vtable / vptr performance penalties: Cache misses from function pointer indirection and inhibition of compiler inlining/vectorization in tight loops.
  - **Zero-Cost Static Alternatives:** **CRTP (Curiously Recurring Template Pattern)**, C++23 "deducing `this`", and `std::variant` + `std::visit` for closed type hierarchies without dynamic heap allocations.

### 4. Concurrency, Atomics & The C++ Memory Model
- **`volatile` vs. `std::atomic` (Firmware Baseline):**
  - Why `volatile` has **no thread-safety or atomicity semantics** in C++ (only forces the compiler to re-read/write Memory-Mapped I/O registers instead of optimizing them into CPU registers).
  - Why inter-thread synchronization mandates `std::atomic<T>`.
- **The C++ Memory Model & Orderings:**
  - `memory_order_relaxed`: Atomic read/write operations without synchronization or ordering constraints (ideal for simple performance counters).
  - `memory_order_acquire` & `memory_order_release`: The fundamental synchronization pair used in lock-free single-producer single-consumer ring buffers to prevent memory reordering across boundaries.
  - `memory_order_seq_cst`: Sequentially consistent ordering (default, inserts full hardware fences).
  - **Compare-And-Swap (CAS):** `compare_exchange_weak` (can fail spuriously on Load-Linked/Store-Conditional architectures like ARM/Hexagon, but executes faster in loops) vs. `compare_exchange_strong`.
- **Synchronization & Threading:**
  - Mutex choices: `std::lock_guard` (basic RAII), `std::unique_lock` (deferred locking, CV support), `std::scoped_lock` (C++17 deadlock-free multi-mutex acquisition via deadlock avoidance algorithms).
  - `std::condition_variable`: Mandatory usage of `while (!predicate)` loops to protect against spurious wakeups.

### 5. Undefined Behavior (UB) & Compiler Optimizations
- **The Strict Aliasing Rule & Type Punning:**
  - Why `reinterpret_cast<uint32_t*>(float_ptr)` is Undefined Behavior that breaks under `-O2`/`-O3` compiler optimizations.
  - Standard-compliant zero-overhead type punning via `std::memcpy` (optimized away to a register move) or **C++20 `std::bit_cast<Dest>(src)`**.
- **Integer Arithmetic:**
  - Signed integer overflow is Undefined Behavior (allows compilers to optimize away bounds checks or turn loops into infinite loops); unsigned integer overflow is defined wrap-around ($2^N$).
- **Helping Compilers Vectorize:**
  - Pointer aliasing hazards and how `__restrict` guarantees non-overlapping memory buffers to enable SIMD auto-vectorization.
  - Branch prediction hints using `[[likely]]` / `[[unlikely]]` (C++20).

### 6. Recommended C++ Video Watch-List
1. **STL & Data Structures:** Chandler Carruth — *"Efficiency with Algorithms, Performance with Data Structures"* (CppCon).
2. **Atomics & Memory Model:** Herb Sutter — *"atomic<> Weapons: The C++ Memory Model and Modern Hardware"* (Parts 1 & 2) OR Fedor Pikus — *"C++ Atomics, from Basic to Advanced"*.
3. **Core Modern Idioms:** Search **CppCon "Back to Basics"** and watch:
  - *Move Semantics*
  - *Smart Pointers*
  - *Templates & Concepts*
  - *RAII & Object Lifetime*
4. **SIMD Vectorization:** Matthias Kretz — *"Vectorizing with C++ (`std::simd`)"* (CppCon).