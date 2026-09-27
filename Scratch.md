# Scratch
- [Lectures List](#lectures-list)
- [NeetCode 150](#neetcode-150)
- [Domain Specific](#domain-specific)
- [C/C++ Checklist](#cc-checklist)
- [File Structure](#file-structure)

## Lectures List

### To Do
- [Tushar Gautam GPU videos](https://www.youtube.com/playlist?list=PLU0zjpa44nPXddA_hWV1U8oO7AevFgXnT)
- [DSA Graph Theory Visualizations](https://www.youtube.com/playlist?list=PLpXOY-RxVRTPPVLBP6-sz6CMWxhtrI-v_)

### Good To Have
- [Compilers](https://www.youtube.com/playlist?list=PLTsf9UeqkRebOYdw4uqSN0ugRShSmHrzH)
- [OLCF CUDA](https://www.youtube.com/playlist?list=PL6RdenZrxrw-zNX7uuGppWETdxt_JxdMj)
- [GPU Mode](https://www.youtube.com/@GPUMODE/videos)

### Archive
- [Deep Learning Systems (GPU implementation of DL algos)](https://www.youtube.com/playlist?list=PLT6QPhVMICSa30axDNX9nljqaTeuftC8t)
- [Machine Learning](https://www.youtube.com/playlist?list=PLoROMvodv4rNH7qL6-efu_q2_bPuy0adh)


## NeetCode 150
- ㅤ
  | Week | Topics                          | #     |
  | ---- | ------------------------------- | ----- |
  | 1    | Arrays & Hashing + Two Pointers | 9+5   |
  | 2    | Sliding Window + Stack          | 6+6   |
  | 3    | Binary Search + Linked List     | 7+7   |
  | 4    | Linked List + Trees             | 4+5   |
  | 5    | Trees                           | 10    |
  | 6    | Tries + Heap + Backtracking     | 3+7+3 |
  | 7    | Backtracking                    | 7     |
  | 8    | Graphs + Bit Manip              | 7+4   |
  | 9    | Graphs + Bit Manip              | 6+3   |
  | 10   | Intervals + Greedy              | 6+5   |
  | 11   | Greedy + Math                   | 3+8   |
  | 12   | Adv Graphs                      | 6     |
  | 13   | 1-D DP                          | 6     |
  | 14   | 1-D DP                          | 6     |
  | 15   | 2-D DP                          | 6     |
  | 16   | 2-D DP                          | 5     |

## Domain Specific
- LeetGPU for practice
- [GPUMode GPU Puzzles](https://github.com/srush/gpu-puzzles)
- [Lei Mao Optimization Blogs](https://leimao.github.io/article/CUDA-Matrix-Multiplication-Optimization/)

### Phase 1: Existing Work History Revision (Weeks 1–2)

*Extract and consolidate short technical notes directly from your Qualcomm, Valeo, and embedded history.*

* **Hexagon DSP & HVX Microarchitecture**:
* HVX 1024-bit vector registers (`V64` in 64-byte mode vs. `V128` in 128-byte mode).
* Key HVX intrinsics: sliding/aligning (`Q6_V_valign_VVR`), interleaving/transposing (`Q6_P_vdeal_VV`, `Q6_V_vpack_VV`), vector multiply-accumulate pipelines.
* Vector load alignment penalties: aligned vs. unaligned loads (`vmem` vs. `vmemu`), software alignment buffer management.
* VLIW pipeline packetization: 4-slot execution units, resource conflicts (load/store limits vs. ALU slots), structural hazard stalls.
* Fixed-point numerical formats: Q-format math (Q15, Q31), saturation arithmetic (`Q6_R_add_RR_sat`), rounding shifts, dynamic range preservation.

* **Accelerator Firmware & Memory Systems**:
* DMA engine programming: Descriptor rings, scatter-gather chains, channel contention, interrupt latency vs. polling completion.
* Multi-stage latency hiding: Double-buffering / ping-pong buffers between external DRAM and on-chip SRAM/Tightly Coupled Memory (TCM).
* Cache maintenance & coherency: Explicit cache invalidation, cache flushing (`clean`), memory barriers (`fence`), hardware vs. software-managed cache coherence.
* Concurrency: Thread scheduling overhead, spinlocks vs. mutexes in RTOS, register saving costs during context switching.

* **Halide Compilation Mechanics**:
* Algorithm vs. schedule separation.
* Loop scheduling directives: `split()`, `tile()`, `reorder()`, `fuse()`.
* Compute and storage boundaries: `compute_at()`, `store_at()`, `compute_root()`.
* Vectorization, loop unrolling, and thread parallelization directives.

* **C++ & Heterogeneous Runtimes (OpenCL, NEON, C++26)**:
* `C++26 std::simd` and custom vector wrappers: Abstracting vector widths, native ABI vector register mapping, scalar fallback paths for non-multiple widths.
* ARM NEON intrinsics: 128-bit vector lanes, multi-register de-interleaving loads (`vld2`, `vld4`), accumulator pipelines.
* OpenCL execution runtime: NDRange mapping, work-items/work-groups, local memory allocation, synchronization barriers (`CLK_LOCAL_MEM_FENCE`).
* Toolchains & debug: CMake cross-compilation toolchains, sysroot targeting, Processor-In-the-Loop (PIL) test harnesses, register-level debugging.

### Phase 2: SIMT Hardware Execution, SASS/PTX & Memory Model (Weeks 3–5)

*Target GPU concurrency, memory ordering, and disassembly.*

* **Theory & Prerequisites**:
* Stanford CS 149: GPU Execution Models, Roofline Modeling, Memory Consistency.
* OLCF CUDA Series: Shared Memory, Warp Primitives, Atomics, and Streams.

* **Microarchitecture Concepts**:
* 32-bank shared memory layout, bank conflict mechanics (stride formulas, broadcast modes, XOR swizzling, row padding).
* Global memory coalescing: 32B, 64B, 128B transaction segments; uncoalesced memory stalls.
* Concurrency & Synchronization: SIMT branch divergence and reconvergence stacks, warp shuffles (`__shfl_sync`, `__shfl_down_sync`, `__shfl_xor_sync`), atomics (`atomicAdd`, acquire/release semantics), barriers (`__syncthreads`, `__threadfence_block`).
* Occupancy: Little’s Law ($N = X \times R$), register pressure cliffs, max active warps vs. shared memory usage.

* **Assembly Inspection & Tools**:
* Inspect PTX (`nvcc -ptx`) and SASS assembly (`nvdisasm`, `cuobjdump -sass`): Identify register spilling to local memory, dual-issue instructions, and memory stall dependencies.

* **Hands-on Target**:
* Parallel reduction: Multi-pass shared memory tree reduction vs. single-pass warp-shuffle reduction with atomic grid accumulation. Profile with `ncu`.

### Phase 3: GEMM / GEMV, Roofline & Cache Tiling (Weeks 6–8)

*Master both compute-bound (prefill) and memory-bandwidth-bound (decode) operations.*

* **GEMM Progression**:
1. Naive global memory GEMM.
2. Coalesced reads + Shared memory blocking.
3. 1D register tiling $\to$ 2D register tiling (outer product per thread).
4. Vectorized loads (`float4` / `int4` / `ldmatrix`).
5. Asynchronous data copies (`cp.async`) with multi-stage software pipelining (ping-pong shared memory).
6. **Thread Block Swizzling**: Raster/Hilbert swizzle to maximize L2 cache line reuse on matrix $B$.

* **GEMV (Decode Kernel)**:
* Implement matrix-vector multiplication ($M=1$): Parallelize across matrix rows, vectorized memory loads, warp-level reductions to saturate peak memory bandwidth.

* **Memory-Bound Fused Elementwise**:
* Fast Fused RMSNorm & LayerNorm: Vectorized 128-bit loads hitting $>90\%$ DRAM/HBM bus saturation.
* Numerically stable online softmax (two-pass vs. three-pass).

* **Tooling Standard**:
* Profile every build via `ncu --set full`. Plot operational points on an arithmetic intensity vs. FLOPS Roofline chart.

### Phase 4: Tensor Cores, Attention & Quantization (Weeks 9–12)

*Shift from generic SIMT compute to modern AI silicon execution paths.*

* **Hardware Primitives**:
* Inline PTX for Tensor Cores (`mma.sync` on Ampere); understand `wgmma` / TMA concepts on Hopper.
* CUTLASS 3.x Collective APIs: CuTe layout abstractions (tensors, shapes, strides, coordinate mapping).

* **FlashAttention Forward Pass Implementation**:
* Implement FlashAttention-2 algorithm: Block tiling of $Q, K, V$ in SRAM, online softmax running rescaling factor ($m_i, \ell_i$), avoiding full $N \times N$ matrix materialization in HBM.
* Implement causal masking directly inside the SRAM inner loop.
* Grouped-Query Attention (GQA) support ($H_Q \neq H_{KV}$) inside the tile loader.

* **Quantization & Low-Bit Formats**:
* Mixed precision FP16/BF16 accumulation.
* INT4 / FP8 weight-only dequantization GEMM (W4A16 / Marlin-style weight packing to eliminate dequant overhead).
* Microscaling concepts: FP4 / MXFP6 / MXFP4 scaling block structures used in modern hardware.

### Phase 5: Triton, Serving & Decode Primitives (Weeks 13–15)

*Master frameworks utilized in modern AI infrastructure and inference engines.*

* **OpenAI Triton Specialization**:
* Triton execution model: Block-level abstraction, compiler-managed shared memory allocation, automatic pipelining.
* Implement in Triton:
* Fused RMSNorm + SwiGLU + RoPE (Rotary Position Embeddings).
* Tiled GEMM with autotuning (`@triton.autotune` for `BLOCK_M, N, K`, `num_warps`, `num_stages`).
* FlashAttention-2 forward kernel.

* **LLM Serving / Inference Kernels**:
* **PagedAttention**: Kernel reading fragmented, non-contiguous KV-cache pages (block tables) instead of uniform tensors.
* **FlashDecoding / Split-K**: Parallelize attention over sequence length during generation/decode phase ($M=1$) to saturate GPU compute units.
* Chunked Prefill kernel mechanics (mixing prefill and decode in single batch allocations).

### Phase 6: Production PyTorch, Graphs & Verification (Week 16)

*Integrate custom kernels into high-level runtimes and production graph compilers.*

* **PyTorch C++ / CUDA Binding**:
* Build PyTorch C++ extensions (`torch.utils.cpp_extension`) with direct Dispatcher integration.
* Implement backward pass gradients for custom kernels (RMSNorm backward, GEMM backward).
* Rigorous autograd correctness testing using `torch.autograd.gradcheck`.

* **CUDA Graph Capture & `torch.compile`**:
* CUDA Graph capture integration (`cudaStreamBeginCapture`, replay) to eliminate CPU launch overhead on small kernels.
* Register custom C++ and Triton operators using `@torch.library.custom_op` to ensure compatibility with TorchDynamo and AOTAutograd without breaking graph captures.

* **Testing & Profiling**:
* Run `compute-sanitizer` to catch out-of-bounds shared/global memory accesses, memory leaks, and stream race conditions.
* LeetGPU for timed implementation drills (boundary conditions, tail tiles, non-power-of-2 dimensions).


## C/C++ Checklist

### **1. Memory Layout, Pointers, & Hardware Sympathy**

* **Alignment & Structure Layout**: `alignas`, `alignof`, struct padding/packing rules (`#pragma pack`), 64B/128B cacheline alignment, false sharing mitigation.
* **Aliasing & Type Punning**: Strict aliasing rules, `std::memcpy` bit-cast idioms, `std::bit_cast` (C++20), `__restrict__` pointer qualifiers, `std::assume_aligned` for SIMD code generation.
* **Cache & Memory Hardware**: Software prefetching (`__builtin_prefetch`), non-temporal/streaming stores, `volatile` (hardware MMIO) vs. `std::atomic` (thread concurrency).
* **Numeric Representation**: Two's complement, sign extension, integer promotion, IEEE 754 precision/rounding behavior (denormals, FP16/BF16 bit layouts).
* **Pointer Mechanics & Tensor Indexing**: Pointer arithmetic, row-major vs. column-major memory layouts, arbitrary stride indexing (`ptr + i * stride_0 + j * stride_1`), overloading `operator[]` and `operator()`.
* **Low-Level Allocation**: Bump/arena allocation mechanics, placement `new`, explicit destructor calls (`ptr->~T()`).

### **2. Value Semantics, RAII, & Object Models**

* **Value Categories & Move Semantics**: `std::move`, `std::forward`, universal/forwarding references (`T&&`), xvalue/prvalue/lvalue distinctions, reference collapsing rules.
* **Constructor Dynamics**: Rule of 0/3/5, copy/move elision (RVO/NRVO), `noexcept` move constructors (enabling `std::vector` relocation optimizations).
* **Layout Optimization**: Empty Base Optimization (EBO), `[[no_unique_address]]` (C++20) for zero-overhead stateless allocators/deleters.
* **Smart Pointers**: `std::unique_ptr` with custom stateful/stateless deleters (wrapping `cudaFree`, OS handles, DMA buffers), `std::shared_ptr` control-block allocation overhead (`make_shared` locality vs. weak-reference lifetime extension).
* **Polymorphism Overhead**: Virtual tables (`vptr`/`vtable`), indirect branch misprediction costs, devirtualization limits, and static polymorphism alternatives.

### **3. Templates, NTTP, & Compile-Time Evaluation**

* **Compile-Time Execution**: `constexpr`, `consteval`, `if constexpr` (compile-time branching), `std::is_constant_evaluated()`.
* **NTTP (Non-Type Template Parameters)**: Passing compile-time tile shapes, vector widths, and stride factors via template parameters (`template <size_t TileM, size_t TileK>`).
* **Specialization & SFINAE**: Full and partial template specialization, SFINAE via `std::enable_if_t` and `std::void_t` for legacy codebases (PyTorch/CUTLASS).
* **Variadics & Fold Expressions**: Variadic parameter packs (`Args&&...`), C++17 fold expressions (`(... + args)`).
* **Type Traits & Introspection**: `<type_traits>` (`is_same_v`, `is_trivially_copyable_v`, `is_standard_layout_v`, `is_floating_point_v`).
* **C++20 Concepts**: Constraining template types (`requires` clauses) to enforce memory layouts and numeric traits.
* **Code Bloat Mitigation**: Explicit template instantiations, separating type-independent logic into non-templated helper functions.

### **4. DSA Containers, Slices, & Hash Mechanics**

* **Contiguous Buffers**:
* `std::array`: Fixed-size stack-allocated arrays, zero-cost abstraction over raw arrays.
* `std::vector`: Geometric growth factor, `reserve` vs. `resize`, `shrink_to_fit`, `emplace_back`, iterator invalidation rules during reallocation.
* Non-owning slices: `std::span` (C++20) and `std::string_view` for zero-copy views.

* **DSA-Specific Containers & Custom Hashing**:
* `std::priority_queue` with custom comparators (max-heap, min-heap for Top-K, Dijkstra, Intervals).
* `std::unordered_map` / `std::unordered_set`: Bucket allocation dynamics, load factor, custom hash functors and hash combination (`hash_combine`) for composite keys (`std::pair`, tuples).
* `std::deque`, `std::stack`, `std::queue`: Sliding window, monotonic stacks, BFS traversal.

* **Algorithms**: `std::sort`, `std::lower_bound` / `std::upper_bound`, `std::binary_search`, `std::transform`, `std::accumulate` / `std::reduce`. Writing correct strict-weak-ordering comparators.
* **Vocabulary Types**: `std::optional` (nullable returns without pointer sentinels).

### **5. Atomics, Lock-Free Concurrency, & Host Runtime**

* **Atomic Mechanics & Invariants**:
* `std::atomic<T>`, `std::atomic_ref<T>` (C++20).
* Lock-free verification: `is_lock_free()`, alignment guarantees, hardware double-word CAS (`CMPXCHG16B` / ARM `LDXP`/`STXP`).

* **Compare-And-Swap (CAS) & Lock-Free Patterns**:
* `compare_exchange_weak` (spurious failures, LL/SC loops) vs. `compare_exchange_strong`.
* Lock-free structures: Atomic queues, lock-free free-lists, ABA problem mitigation via tagged pointers.
* Serial aggregation of parallel thread outputs without mutex stalls.

* **Memory Ordering Semantics**:
* `memory_order_relaxed`: Atomicity only, absence of synchronization/ordering constraints.
* `memory_order_acquire` / `memory_order_release`: One-way memory barriers establishing synchronizes-with relationships.
* `memory_order_consume`: Data-dependency ordering.
* `memory_order_acq_rel`: Read-modify-write acting as both acquire and release.
* `memory_order_seq_cst`: Globally consistent sequential order, bus locking overhead.

* **Explicit Barriers & Low-Level Primitives**:
* `std::atomic_thread_fence` vs. compiler barriers (`asm volatile("" ::: "memory")`).
* `std::atomic_flag`: Spinlocks with pause/yield hints (`_mm_pause` / `__yield`).

* **Host Runtime & Async Pipeline Coordination**:
* `std::thread`, `std::mutex`, `std::condition_variable` (predicate-based wait loops to prevent spurious wakeups), `std::unique_lock`, `std::scoped_lock` (deadlock-free multi-lock acquisition).
* Coordinating host worker pools consuming asynchronous GPU stream outputs (`cudaStreamAddCallback`, `cudaLaunchHostFunc`, event synchronization).

### **6. Low-Level Math, Bit Manipulation, & Branchless Idioms**

* **C++20 `<bit>` Library**: `std::popcount`, `std::countl_zero`, `std::countr_zero`, `std::bit_width`, `std::rotl`, `std::rotr`.
* **Bitwise Arithmetic**: Bitmasks, arithmetic shifts, sign-extension tricks, leading/trailing zero manipulation for branchless index mapping.
* **Branchless Mechanics**: Masking conditions (`(cond) * val` or bitwise masks), branch-free clamping (`min`/`max`), sign manipulation.

## File Structure
- ㅤ
  ```
  ├── BigO.md                  (Existing)
  ├── Linear.md                (Existing: Arrays + Hash Tables, or split into Arrays.md & HashTables.md)
  ├── LinkedLists.md
  ├── StacksQueues.md
  ├── Heap.md                  (Binary Heap + Indexed PQ)
  ├── Trees.md                 (Binary Trees & BST)
  ├── BalancedTrees.md         (AVL & Rotations - William Fiset)
  ├── Tries.md
  ├── DisjointSet.md           (Union-Find)
  ├── AdvancedTrees.md         (Segment Tree & Fenwick Tree - William Fiset)
  ├── Graphs.md                (Traversals & Representations)
  ├── TopologicalSort.md
  ├── ShortestPath.md          (Dijkstra, Bellman-Ford, Floyd-Warshall)
  ├── MinimumSpanningTree.md   (Kruskal, Prim)
  ├── AdvancedGraphs.md        (Tarjan SCC/Bridges, Network Flow)
  ├── BinarySearch.md
  ├── DynamicProgramming.md
  ├── BacktrackingGreedy.md
  ├── BitManipulation.md
  └── MathGeometry.md
  ```