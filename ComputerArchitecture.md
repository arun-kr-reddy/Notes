# Computer Architecture
- [Introduction](#introduction)
- [Instruction Set Architecture](#instruction-set-architecture)
- [Parallel Computing](#parallel-computing)
- [Misc](#misc)
- [Scratch](#scratch)

## Links <!-- omit from toc -->
- [Design of Digital Circuits (ETH, 2018)](https://www.youtube.com/playlist?list=PL5Q2soXY2Zi_QedyPWtRmFUJ2F8DdYP7l)
- [Parallel Computing (Stanford, 2023)](https://www.youtube.com/playlist?list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp)

## To Do <!-- omit from toc -->

## Introduction
- **Abstraction:** higher level only needs to know about interface to lower level, not how its implemented
- **Moore's law:**
  - observation of historical trend that transistor density doubles approximately every two years
  - smaller transistors allowed higher clock speed and more complex instruction-level-parallelism features
  - clock `f ∝ V` volatage and power `p = f * V^2`, so `p ∝ f^3`
  - practically general-purpose instruction streams (due to data dependencies & branches) rarely sustain more than 4 instructions-per-cycle
  - so now focus on parallelism (multi-core) and specialization (NPUs, ISPs)
- **Iron Law of Performance:** `num_instructions * cycles_per_instruction x clock_cycle_time` gives time taken to execute a program

## Instruction Set Architecture
- **Von-Neumann Model:** instruction & data kept in same memory and share a single bus  
  **Harvard Model:** having separate instruction & data memory and buses, can fetch instruction & data at the same time  
  modern processors use both Von-Neumann (RAM holds everything) and Harvard (separate I & D caches)
- **Data-Flow Model:**
  - instruction fetched & executed only when its input operands are ready
  - no instruction pointer required
- **Register:**
  - high speed internal storage to hold operands & results from the ALU
  - typically one register contains one word
  - **Register File/Set:** set of registers that can be manipulated by instructions  
    *example:* ARMv7-A has `32 x 32bit` registers
- **Special Purpose Registers:**
  - **Stack Pointer (`SP`):** address of top of the stack
  - **Link Register (`LR`):** return address
  - **Instruction Register (`IR`):** current instruction
  - **Program Counter (`PC`) / Instruction Pointer (`IP`):** address of next instruction to be fetched
  - **Program Status Register (`PSR`):** zero (`Z`), negative (`N`), carry (`C`), overflow (`V`)
  - **Memory Address Register (`MAR`):** address to read/write
  - **Memory Data/Buffer Register (`MDR`/`MBR`):** data coming from read or to be written
    - to read data: source address --> `MAR`, then wait for data --> `MDR`
    - to write data: destination address --> `MAR` and data --> `MDR`, then trigger "write enable" signal
- **Instruction Set Architecture (ISA):**
  - abstract interface that defines how software interacts with the hardware
  - specifies memory organization, register set and instruction set (opcodes, data types & addressing modes)
  - **Instruction:** fundamental unit of execution, made up of opcode & operands
  - ISA can have large or small set of opcodes
    - CISC: do more per instruction, but needs complex hardware
    - RISC: simpler & faster instructions, but shifts burden of optimization to compiler
  - **Semantic Gap:** how closely instructions map to high-level language constructs  
    *example:* instructions that work on matrix direcly lead to smaller semantic gap
- **Instruction Cycle:**
  - sequence of steps that instruction goes through to be executed
  - not all six steps are required for each instruction  
    *example:* `ADD R0, R1, R2` doesn't need to evaluate address
  - **Fetch:** obtain instruction from memory (via `PC`) and load it into `IR`
  - **Decode:** translate the opcode to detemine the operation
  - **Evaluate Address:** computes memory locations of operands
  - **Fetch Operands:** retreive operands from registers or memory
  - **Execute:** perform actual computation or logic
  - **Store Result:** write outpuit to destination
- **Micro-Architecture:**
  - hardware-specific implementation of ISA, which keeps improving while maintaining constant ISA interface  
    *example:* `add` instruction vs underlying adder implementation
  - hardware may execute instructions in any order, final results visible according to ISA semantics
  - enables hardware features like pipelining, speculative execution, OoO execution without any SW changes
- **Architectural State:**
  - specific hardware components that represent current state of a program as defined by ISA
  - **example:** `PC`, register file, memory
-  
  | Single Cycle Machine                        | Multi-Cycle Machine                                              |
  | ------------------------------------------- | ---------------------------------------------------------------- |
  | exactly 1 clock cycle per instruction       | multiple cycles as needed                                        |
  | architectural state updated after execution | internal state during processing, architectural state at the end |
  | cycle time dictated by slowest instruction  | need extra registers to store intermediate results               |

## Parallel Computing
- **Parallel Computer:** collection of processing elements that cooperate to solve problems quickly
- **Fast != Efficient:**
  - just because program runs faster on parallel computer, doesn't mean its using the hardware efficiently
  - *example:* 2x speedup with 10 processors
  - achieving efficient processing almost always comes down to accessing data efficiently
- **Superscalar Execution:**
  - processor automatically finds independent instructions to run in parallel on multiple execution units
  - performance speedup tends to flatten after ~4 IPC is reached
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
- to prevent SIMD stall, add more execution contexts so more threads can run on same HW
- 1 (8-wide) instruction per clock, 1 thread at a time, but 100% utilization (some runnable thread always present)  
  but extra chip area, higher throughput at cost of higher per thread latency
- ratio of ALU cycles to MemOps cycles determines how much multi-threading to reach 100% utilization  
  example: 2 images
- example: Kaby Lake:
  - multiple fetch decode to stuff instr to all vector & scalar ALU blocks
- GPU: extreme throughput-oriented processors
  - streaming multi-processor (SM): equivalent to core
  - warp: execution contexts

[CONTINUE](https://youtu.be/F4bVSyz_jxo?list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp&t=1622)

## Misc
- **Meltdown & Spectre:**
  - speculative execution leaves traces of data in cache
  - malicious program can inspect cache contents to infer secret data
- **Rowhammer:**
  - repeatedly accessing a DRAM row enough times drains charge in adjacent rows
  - this electrical interference can be used to predictably induce bit flips
  - > it's like breaking into an apartment by repeatedly slamming a neighbor's door until vibrations open the door you were after

## Scratch
- **Time Division Multiplexing:** method of sharing a single resource (like core, bus) by assigning each task a fixed non-overlapping time-slot for exclusive access