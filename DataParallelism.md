# Data Parallelism
- [Introduction](#introduction)
- [`std::simd`](#stdsimd)
  - [Examples](#examples)
- [CUDA](#cuda)
- [Doubts](#doubts)

## Links <!-- omit from toc -->
- [`std::simd` Talk](https://www.youtube.com/watch?v=LAJ_hywLtMA)
- [CUDA Training (ORNL, 2020)](https://www.youtube.com/playlist?list=PL6RdenZrxrw-zNX7uuGppWETdxt_JxdMj)
- [LeetGPU](https://leetgpu.com/challenges)

## To Do <!-- omit from toc -->
- [Linaro NEON I](https://www.youtube.com/watch?v=NYFzidaS3Z4&pp=ygUIQVJNIG5lb24%3D)
- [Linaro NEON II](https://www.youtube.com/watch?v=ixuDntaSnHI&pp=ygUIQVJNIG5lb24%3D)
- [x86 Assembly & SIMD](https://www.youtube.com/watch?v=L2Qu9rk05rE)
- process both paths (masking)
- [CppArm Meetup (SIMD & Perf Talks)](https://www.youtube.com/@ArmeniaCPPTalks/videos)
- [Ash Vardanian Talks](https://ashvardanian.com/talks/)
- [Easy Introduction to CUDA C and C++](https://developer.nvidia.com/blog/easy-introduction-cuda-c-and-c/)
- [llama.cpp CUDA kernels](https://github.com/ggml-org/llama.cpp/tree/master/ggml/src/ggml-cuda)
- [google highway](https://github.com/google/highway)
- [CUDA Resources](https://www.reddit.com/r/CUDA/comments/1m6ii0h/beginner_trying_to_learn_cuda_for_parallel/)

## Introduction
- **Alignment:**
  - memory data addresses must be divisible by vector width (in bytes)
  - use `alignas(SIZE)`
    ```cpp
    alignas(64) int counterA; // new cache line
    alignas(64) int counterB; // next cache line
    ```
  - for un-aligned data:
    - use un-aligned load instruction (if available)
    - aligned data in vector, unaligned indexes in scalar
    - memcpy into aligned buffer before loading to vector register
  - **Amdahl's Law:**
    - parallel processing performance gain is limited by part of program that must run serially
    - *example:* if 10% of program is serial, then maximum gain (`N = inf`) is 10x
    - `speedup = time_original / time_new`  
      assume `time_original` is 100%, *i.e.* 1  
      time_new is made up of serial & parallel part  
      serial part unchanged `(100% - P)`, *i.e.* `(1 - P)`  
      parallel part split across `N` processors, so `P/N`  
      ![](./Media/Amdahl's%20Law.png)

## `std::simd`
- **`std::simd<T>`:**
  - represents single vector register
  - `simd<T>::size()` is (constexpr) number of lanes for given type
  - `simd<T>::size() * sizeof(T)` equals hardware vector register size
  - 
    ```cpp
    simd<int> x0;     // uninitialized: | ? | ? | ? |...
    simd<int> x1{};   // value-init:    | 0 | 0 | 0 |...
    simd<int> x2 = 1; // broadcast:     | 1 | 1 | 1 |...
    simd<int> x3(it); // load:          | it[0] | it[1] | it[2] |...
    simd<int> x4([](int i) { return i; }); // generator: | 0 | 1 | 2 |...
    ```
  - `copy_from()` to load contiguous memory (`copy_to()`)
- **`simd_mask<T>`:**
  - element-wise `bool` vector that comparison operators output
  - use `simd_select(mask, if_true, if_false)` for branchless conditional logic
    ```cpp
    simd_mask<T> x_smaller = (x < y);
    // x = (x < y) ? y : x;
    x = simd_select(x_smaller, y, x);
    // OR
    x = simd_select(x < y, y, x);
    ```
- **Reductions:**
  - vector space to scalar space
  - `simd_mask` --> `bool`
    |                                                    |                                 |
    | -------------------------------------------------- | ------------------------------- |
    | `all_of(mask)`, `any_of(mask)`, `none_of(mask)`    | return `bool`                   |
    | `reduce_count(mask)`                               | count `true` lanes              |
    | `reduce_min_index(mask)`, `reduce_max_index(mask)` | index of first/last `true` lane |
  - `simd` --> `T`
    |                                        |                               |
    | -------------------------------------- | ----------------------------- |
    | `reduce(simd)`                         | accumulation                  |
    | `reduce_min(simd)`, `reduce_max(simd)` | min/max value among all lanes |
- **Parallelism:**
  - `std::simd<T>` is data-level parallelism (*i.e.* SIMD)
  - `std::simd<T, std::simd<T> * N>` is instruction-level parallelism along with DLP (*i.e.* `N`*SIMD)
  - ILP forces compiler to generate multiple independent instructions (similar to unrolling)
- ***Example:* ARGB --> Grayscale:**
  - assume 32bit `0xAARRGGBB` image
  - since 8bit per channel, `uint8*uint8` needs `uint16` and `uint16+uint16` needs `uint17`, so 32bit output
  - 
    ```cpp
    using Pixel = uint32_t;
    using Image = std::vector<Pixel>;
    using PixelV = std::simd<Pixel, std::simd<Pixel>::size() * ILP>;

    void to_gray(Image &img) {
      // loop incrementing by ILP * SIMD
      for (auto it = img.begin(); it < img.end(); it += PixelV::size()) {
        PixelV p(it); // loads | it[0] | it[1] |...

        const PixelV a = p >> 24; // each lane 32bits
        const PixelV r = (p >> 16) & 0xFF;
        const PixelV g = (p >> 8) & 0xFF;
        const PixelV b = p & 0xFF;

        // gray = (11 * red + 16 * green + 5 * blue) / 32
        const auto gray = (r * 11 + g * 16 + b * 5) >> 5;
        p = gray | (gray << 8) | (gray << 16) | (a << 24);
        p.copy_to(it);
      }
    }
    ```

### Examples
- **Increase  Brightness:**
  - assume 8bit pixels
  - before saturation `uint8+uint8` needs `uint9`, so `uint16` intermediate
  - 
    ```cpp
    vector_u8 pixels = v_load(image_ptr);
    constexpr uint8_t offset_val = 20;

    vector_u16 pixels_u16 = v_cast_u16(pixels);
    vector_u16 offset_u16 = v_broadcast(offset_val);
    vector_u16 saturatio_u16 = v_broadcast(UINT8_MAX);

    pixels_u16 += offset_u16;
    vector_mask clamped =
        v_select(pixels_u16 > saturatio_u16, saturatio_u16, pixels_u16);

    pixels = v_cast_u8(clamped);
    v_store(image_ptr, pixels);
    ```
- **Horizontal Add:**
  - assuming 8 lanes
  - 
    ```cpp
    vector_t input = {a, b, c, d, e, f, g, h};
    vector_t shifted;

    shifted = v_shuffle_right(input, 4); // {e, f, g, h, ...}
    input = input + shifted;             // {a+e, b+f, c+g, d+h, ...}

    shifted = v_shuffle_right(input, 2 elements); // {c+g, d+h,...}
    input = input + shifted;                      // {a+e+c+g, b+f+d+h, ...}

    shifted = v_shuffle_right(input, 1 element); // {b+f+d+h, ...}
    input = input + shifted;                     // {a+e+c+g+b+f+d+h, ...}

    scalar_t result = input[0];
    ```

## CUDA
- **C**ompute **U**nified **D**evice **A**rchitecture
- device (GPU) runs parallel compute-intensive functions, host (CPU) runs rest of the sequential code
- **Compilation:**
  - `nvcc` separates source code into host & device components
  - device functions processed by Nvidia compiler
  - host functions by standard host compiler (GCC, Clang)
  - `nvcc` also harmonizes POD types with host, *i.e.* `sizeof(int)` same across host & device
    - hence not all host compilers supported
- **Device Code:**
  - `__global__` indicates function is visible to host
    ```cpp
    __global__ void foo(void) {}
    ```
  - `foo<<<gridDim, blockDim, ...>>>();` triple angle braces mark device kernel launch
    - executed `gridDim * blockDim` times
    - grid made up of blocks (`gridDim`), blocks made up of threads (`blockDim`)
    - both support upto three dimensions
      ```cpp
      // Gx, Gy, Gz are total work to be done in respective dimensions
      dim3 blockDim(Lx, Ly, Lz);
      dim3 gridDim(Gx / Lx, Gy / Ly, Gz / Lz);

      foo<<<gridDim, blockDim, ...>>>(...);
      ```
    - each invocation can use built-in variables `blockIdx.{x,y,z}` & `threadIdx.{x,y,z}` to get its block & thread index
    - `blockDim.{x,y,z}` & `gridDim.{x,y,z}` can be used on the device side
  - for handling device memory:
    - `cudaMalloc(void** ptr, size)`
    - `cudaFree(T* ptr)`
    - `cudaMemcpy(T* dest, T* src, size, DIRECTION)`
    - `cudaMemset(T* ptr, uint8_t val, size)`
- **Why Threads:** can communicate & synchronize (unlike blocks)
- ***Example:* Vector Add:**
  ```cpp
  __global__ void add(int *in1; int *in2, int *out) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    out[idx] = in1[idx] + in2[idx];
  }

  int main(void) {
    int *in1, *in2, *out;       // host copies of buffers
    int *d_in1, *d_in2, *d_out; // device copies of buffers

    // alloc memory
    constexpr N = 512;
    constexpr NUM_THREADS_PER_BLOCK = 32;
    size_t size = N * sizeof(int);

    cudaMalloc((void **)&d_in1, size);
    cudaMalloc((void **)&d_in2, size);
    cudaMalloc((void **)&d_out, size);

    in1 = (int *)malloc(size);
    in2 = (int *)malloc(size);
    out = (int *)malloc(size);

    // fill host buffers
    // ...

    // copy input buffers to device
    cudaMemcpy(d_in1, in1, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_in2, in2, size, cudaMemcpyHostToDevice);

    // launch kernel
    add<<<N / NUM_THREADS_PER_BLOCK, NUM_THREADS_PER_BLOCK>>>(d_in1, d_in2,
                                                              d_out);

    // coy output buffers to host
    cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);

    // cleanup
    free(in1);
    free(in2);
    free(out);
    cudaFree(d_in1);
    cudaFree(d_in2);
    cudaFree(d_out);

    return 0;
  }
  ```
- **Handling Remainders:**
  ```cpp
  __global__ void add(int *in1; int *in2, int *out, int n) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (index < n)
      out[idx] = in1[idx] + in2[idx];
  }

  // ceil gridDim
  add<<<(N + M - 1) / M, M>>>(d_in1, d_in2, d_out, N);
  ```

## Doubts
- scatter-gather operations???
- std::static_simd_cast
- remainder handling using simd_mask
- stdx::element_aligned vs vector_aligned
- POD Data Type