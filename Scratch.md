# Scratch
- [ILP](#ilp)
  - [Hardware Techniques (Dynamic)](#hardware-techniques-dynamic)
  - [Software Techniques (Static)](#software-techniques-static)
  - [Summary of Techniques](#summary-of-techniques)

## Links <!-- omit from toc -->

## To Do <!-- omit from toc -->
- [Programming Massively Parallel Processors (Playlist)](https://www.youtube.com/playlist?list=PLRRuQYjFhpmvu5ODQoY2l7D0ADgWEcYAX)
- [GPU MLOps Talks](https://www.youtube.com/@GPUMODE/videos) ([slides](https://github.com/gpu-mode/lectures))
- [Performance Engineering of Software Systems (Playlist)](https://www.youtube.com/playlist?list=PLUl4u3cNGP63VIBQVWguXxZZi0566y7Wf)


## ILP
Exploiting **Instruction-Level Parallelism (ILP)** is the art of overlapping the execution of multiple instructions from a single program to speed up processing. Since most programs are written as a sequential list of steps, the hardware and compiler must work together to find "independent" instructions that can run at the same time.

There are two primary ways to exploit ILP: **Hardware (Dynamic)** and **Software (Static)**.

---

### Hardware Techniques (Dynamic)
In modern processors, the hardware makes real-time decisions to execute instructions out of their original order.

* **Pipelining:** The fundamental "assembly line" approach. While one instruction is being executed, the next is being decoded, and the one after that is being fetched.
* **Superscalar Execution:** Equipping the CPU with multiple functional units (ALUs, FPUs) so it can "issue" and execute more than one instruction in a single clock cycle.
* **Out-of-Order (OoO) Execution:** The processor looks ahead in the instruction stream and executes any instruction whose data is ready, even if it appears later in the code.
* **Register Renaming:** To avoid "false dependencies" (where two instructions use the same register name but don't share data), the hardware maps architectural registers (like `R1`) to a larger pool of physical registers.
* **Branch Prediction & Speculative Execution:** The CPU "guesses" which way a branch (like an `if` statement) will go and starts executing instructions on that path before the guess is confirmed. If it's right, performance jumps; if not, it flushes the pipeline and restarts.
* **Scoreboarding and Tomasulo’s Algorithm:** Complex hardware logic used to track data dependencies and manage when instructions are safe to execute.

---

### Software Techniques (Static)
These methods rely on the **compiler** to analyze the code before it ever runs, rearranging instructions to make the hardware's job easier.

* **Instruction Scheduling:** The compiler reorders code to keep the pipeline full. For example, it might move a math operation into the "gap" created while waiting for a slow memory load to finish.
* **Loop Unrolling:** The compiler replicates the body of a loop multiple times. This reduces the number of branch instructions and creates a larger pool of instructions for the hardware to parallelize.
* **Software Pipelining:** A technique where the compiler reorganizes a loop so that one iteration's "load" happens while the previous iteration's "compute" is running, and the iteration before that is "storing" its result.
* **VLIW (Very Long Instruction Word):** Instead of the hardware figuring out what can run in parallel, the compiler bundles multiple independent instructions into one "long" word. The hardware then executes the whole bundle at once.

---

### Summary of Techniques

| Method | Approach | Key Mechanism |
| :--- | :--- | :--- |
| **Dynamic** | Runtime (Hardware) | Uses Reorder Buffers (ROB) and Reservation Stations. |
| **Static** | Compile-time (Software) | Uses dependency analysis and loop transformations. |
| **Speculative** | Guessing | Executes instructions based on predicted branches. |

> **Note:** Exploiting ILP has a "wall." As you try to execute more instructions in parallel, the complexity and power consumption of the hardware increase exponentially, which is why modern chips often shift focus to **Thread-Level Parallelism (TLP)** and multi-core designs.