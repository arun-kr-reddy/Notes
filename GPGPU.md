# GPGPU
- [Introduction](#introduction)
  - [Misc](#misc)

## Links <!-- omit from toc -->
- [CUDA Traning (Playlist)](https://www.youtube.com/playlist?list=PL6RdenZrxrw-zNX7uuGppWETdxt_JxdMj)
- [LeetGPU](https://leetgpu.com/challenges)

## To Do <!-- omit from toc -->
- [Easy Introduction to CUDA C and C++](https://developer.nvidia.com/blog/easy-introduction-cuda-c-and-c/)
- [llama.cpp CUDA kernels](https://github.com/ggml-org/llama.cpp/tree/master/ggml/src/ggml-cuda)
- [google highway](https://github.com/google/highway)
- [CUDA Resources](https://www.reddit.com/r/CUDA/comments/1m6ii0h/beginner_trying_to_learn_cuda_for_parallel/)

## Introduction
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

### Misc
- **Amdahl's Law:**
  - parallel processing performance gain is limited by part of program that must run serially
  - *example:* if 10% of program is serial, then maximum gain (`N = inf`) is 10x
  - `speedup = time_original / time_new`  
    assume `time_original` is 100%, *i.e.* 1  
    time_new is made up of serial & parallel part  
    serial part unchanged `(100% - P)`, *i.e.* `(1 - P)`  
    parallel part split across `N` processors, so `P/N`  
    ![](./Media/Amdahl's%20Law.png)
- **POD Data Type:**