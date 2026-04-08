# Parallel Computing
- [Introduction](#introduction)

## Links <!-- omit from toc -->
- [Parallel Computing (Stanford, 2023)](https://www.youtube.com/playlist?list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp)

## To Do <!-- omit from toc -->

## Introduction
- **Parallel Computer:** collection of processing elements that cooperate to solve problems quickly
- **Fast != Efficient:**
  - just because program runs faster on parallel computer, doesn't mean its using the hardware efficiently
  - *example:* 2x speedup with 10 processors
  - achieving efficient processing almost always comes down to accessing data efficiently
- **Superscalar Execution:**
  - processor automatically finds independent instructions to run in parallel on multiple execution units
  - performance speedup tends to flatten after ~4 IPC is reached
- **Why Parallelism:**
  - earlier single-threaded performance doubling every ~18 months
  - smaller transistors allowed for higher clock and more transistors in same area (superscalar execution)
  - clock increases ==> volatage increases, power is freq * voltage^2, so it increases by power of 3
  - no further benefit from ILP after 4 IPC
  - so architects adding more execution units and specialized units (image processing, neural processing)
- **Stall:**
  - processor cannot run the next instruction because future instructions depend on previous instruction that is not yet complete
  - accessing memory major source of stalls
    ```cpp
    ld r0 mem[r2]
    ld r1 mem[r3]
    add r0, r0, r1 // needs data from [r2] & [r3]
    ```
- **Cache:**
  - on-chip storage that maintains a copy of a subset of values in memory
  - if address is "in cache", it can be loaded/stored more quickly that if it only resided in memory
