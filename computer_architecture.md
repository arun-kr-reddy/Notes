- [introduction](#introduction)
- [combinational logic](#combinational-logic)
- [sequential logic](#sequential-logic)
- [timing \& verification](#timing--verification)
- [instruction set architecture](#instruction-set-architecture)
- [micro-architecture](#micro-architecture)
- [pipelining](#pipelining)
- [reorder buffer](#reorder-buffer)
- [out-of-order execution](#out-of-order-execution)
- [dataflow execution](#dataflow-execution)
- [superscalar execution](#superscalar-execution)
- [branch prediction](#branch-prediction)
- [very-long instruction word](#very-long-instruction-word)
- [systolic arrays](#systolic-arrays)
- [decoupled access execute](#decoupled-access-execute)
- [single instruction multiple data](#single-instruction-multiple-data)
- [fine-grained multithreading](#fine-grained-multithreading)
- [graphics processing units](#graphics-processing-units)
- [memory organization](#memory-organization)
- [memory hierarchy](#memory-hierarchy)
- [cache](#cache)
- [prefetching](#prefetching)

# links  <!-- omit from toc -->
- [[playlist] design of digital circuits](https://safari.ethz.ch/digitaltechnik/spring2018/doku.php?id=schedule)
- [Hamming code](https://harryli0088.github.io/hamming-code/)
- [ARM assembly](http://www.cburch.com/books/arm/) ([addressing modes](https://roboticelectronics.in/addressing-modes-in-arm/))

# introduction
- **computer architecture:** is the science & art of designing computing platforms (hardware, interface, system SW & programming model)  
**why art?:** we don't know the future applications/users/market
- **abstraction:** higher level only needs to know about the interface to the lower level, not how the lower level is implemented  
**levels of transformation:** improves productivity by creates abstractions, no need to worry about decisions made in underlying levels  
but breaking the abstraction layers and knowing what is underneath enables you to understand & solve problems  
![](./media/computer_architecture/levels_of_transformation.png)
- **meltdown & spectre:** speculative execution is doing something before you know it is needed to improve performance, but it leaves traces of data in processor's cache that was not supposed to be brought/accessed if there was no speculative execution  
a malicious program can inspect the contents of the cache to infer secret data
- **rowhammer:** repeatedly opening & closing a DRAM row (aggressor row) enough times within a refresh interval induces disturbance errors due to charge getting drained out in adjacent rows (victim row) due to electrical interference, this can be used to predictably induce bit flips, example: flip protection bit in page table entries to access a privileged location  
*"it's like breaking into an apartment by repeatedly slamming a neighbor's door until vibrations open the door you were after"*  
a simple hardware failure mechanism is creating a widespread system security vulnerability (Byzantine failure)  
![](./media/computer_architecture/rowhammer.png)
- **memory performance attacks:** in a multi-core system DRAM controller to increase throughput services row-hit memory access first (then service older accesses) so programs with more requests and good memory spatial locality are preferred, malicious streaming (sequential memory access) program used for denial of service attacks  
![](./media/computer_architecture/dram_controller.png)
- **DRAM refresh:** a DRAM cell consists of a capacitor & an access transistor, applying high voltage to wordline (row enable) allows us to read data (capacitor charge as a bit) in the bitline, but capacitor charge leaks over time, memory controller needs to refresh each row periodically to restore charge, increases energy consumption & DRAM bank unavailable while refreshing, but only small % have low retention time (manufacturing process variation) so don't need to refresh every row frequently, once profiling (retention time of all DRAM rows) is done check (Bloom filters) bins to determine refresh rate of a row  
![](./media/computer_architecture/dram_cell.png)
  - **Bloom filter:** memory efficient probabilistic data structure that compactly represents set membership, test set membership using hash functions (unique identifier generator), no false negatives & never overflows (but `num elements ∝ false positives rate`), three supported operations: insert, test & remove all elements, removing one particular element is not easy (can lead to removal of other elements)
- **Hamming code:** powers-of-2 bits are regular parity bits used to track the parity of the other bits whose position have a 1 in the same place, 0th message bit used as overall parity (including regular parity bits), can correct one-bit errors (regular parity incorrect & overall parity incorrect) & detect two-bit errors (regular parity incorrect & overall parity correct)  
**Hamming distance:** number of locations at which two equal-length strings are different  
![](./media/computer_architecture/hamming_code.png)
- **field programable gate array (FPGA):** is a software-reconfigurable hardware substrate (reconfigurable functions, interconnections & I/O), an algorithms can be implemented directly in hardware, faster than general purpose computer & more flexible than application specific integrated chips (ASICs), programmed using hardware description language (HDL) like Verilog & VHDL  
![](./media/computer_architecture/field_programmable_gate_array.png)
- **Moore's law:** number of transistors on an integrated circuit will double every two years, possible by manufacturing smaller structures through precision manufacturing and creating new device technologies, is an observation and projection of historical trend  
![](./media/computer_architecture/moores_law.png)

# combinational logic
- **metal-oxide-semiconductor (MOS) transistor:** controls the flow of current by the application of a voltage to the insulated gate by altering the conductivity between the drain & source, works similar to a wall switch  
![](./media/computer_architecture/mos_transistor.png)  
![](./media/computer_architecture/mos_transistor_working.gif)  
![](./media/computer_architecture/mos_transistor_types.png)
  - **n-type:** acts like a wire when high voltage applied
  - **p-type:** acts like a wire when low/zero voltage applied
- **complementary MOS (CMOS):** use both n-type & p-type transistors to implement logic gates  
p-type transistors are good at pulling up the voltage and n-type pulling down  
example: NAND gate with CMOS, P1 & P2 are in parallel so only must be high to pull up the output and N1 & N2 are connected in series so both must be high to pull down the output  
![](./media/computer_architecture/cmos_nand_1.png)
![](./media/computer_architecture/cmos_nand_2.png)  
generally CMOS gate structure is made up of pull-up & pull-down network, exactly one network should be ON at any given time  
short circuit if both are ON and floating/undefined output if both OFF  
![](./media/computer_architecture/cmos_networks.png)
- **combinational logic:** outputs are strictly dependent on combination of input values that are applied to circuit right now (memoryless)
- **truth table:** what would be the logical output of the circuit for each possible input  
`NAND` & `NOR` are both universal gates (functionally complete) since any other gate can be made simply using either only `NAND` or only `NOR` gates  
![](./media/computer_architecture/truth_table.png)
- **simple equations:**
  - **OR:** (`+`)
  - **AND:** (`.`)
- **complement:** inverse of a variable  
`~A, ~B, ~C`  
**literal:** variable or its complement  
`A, ~A, B, ~B, C, ~C `  
**implicant:** product of literals  
`(A . B . ~C), (~A . C)`  
**minterm:** product that includes all input's literals  
`(A . B . ~C), (~A . ~B . C)`  
**maxterm:** sum that includes all input's literals  
`(A + B + ~C), (~A + ~B + C)`
- **Boolean algebra:** enables us to methodically transform the boolean function (representing combinational logic block) into simpler functions
  - **identities:** `A + 0 = A`, `A . 1 = A`
  - **idempotent:** `A + A = A`, `A . A = A`
  - **complementary:** `A + ~A = 1`, `A . ~A = 0`
  - **involution:** `~(~A) = A`
  - **commutative:** `A + B = B + A`, `A . B = B . A`
  - **associative:** `(A + B) + C = A + (B + C)`, `(A . B) . C = A . (B . C)`
  - **distributive:** ` A + (B . C) = (A + B) . (A + C)`, `A . (B + C) = (A . B) + (A . C)`
  - **simplification theorems:** `A . B + A . ~B = A`, `A + A . B = A`, `(A + ~B) . B = A . B`
  - **duality:** replace `+` ⟷ `.` and `0` ⟷ `1`a
  - **DeMorgan's law:** `~(X + Y) = ~X . ~Y`, `~(X . Y) = ~X + ~Y`  
  can prove useful is we don't have every type of gate or if some type of gate is more desirable (like due to lower latency)
- truth table is a unique signature of a boolean function that can have many alternative gate realizations  
**canonical form:** standard form for a Boolean expression, example: sum of products form  
**minimal form:** most simplified representation of a function, example: using Karnaugh maps  
original boolean expression may not be optimal, so reduce it to a equivalent expression with fewer terms to reduce number of gates/inputs and hence the implementation cost
- **sum of products (SOP) form:** sum of all input variable combinations (minterms) that result in a `1` output, leads to two-level logic (AND of minterm literals ORed), also called minterm expansion
- **uniting theorem:** eliminate input in minterm that can change without changing the output, if an input can change without changing the output then that input value is not needed  
**Gray code:** binary numbering system in which two successive values only differ by one bit, `00` ⟷ `01` ⟷ `11` ⟷ `10` ⟷ `00`  
**Karnaugh maps:** is a pictorial way of minimizing circuits by visualizing opportunities for simplification, numbering scheme along the axis is Gray code, physical adjacency is logical adjacency  
find rectangular groups of power-of-2 number of adjacent `1`s and then eliminate varying inputs from the minterm, adjacencies also wraps around corners & edges (imagine K-map as a sphere)  
`X` (don't care what input value is) can be used as either `1`/`0` for simpler equation  
![](./media/computer_architecture/k_map_adjacency.png)  
![](./media/computer_architecture/k_map.png)
- **decoder:** one of the `2^n` outputs is set to 1 based on  `n` line input pattern that the logic circuit is expected to detect, used for decoding address of a location in memory  
![](./media/computer_architecture/decoder.png)  
decoders can be combined with OR gates to build logic functions  
![](./media/computer_architecture/decoder_usecase.png)
- **multiplexer (selector):** route one of `2^n` inputs to a single output using `n` select/control lines  
![](./media/computer_architecture/multiplexer.png)  
multiplexer can be used as lookup table to perform logic functions  
![](./media/computer_architecture/multiplexer_usecase.png)
- **programmable logic array (PLA):** an array of AND gates followed by OR gates, used to implement combinational logic circuits by connecting output of an AND gate to input of an OR gate if the corresponding minterm is included in SOP, used in FPGAs  
![](./media/computer_architecture/programmable_logic_array.png)
- **example: one-bit addition (full adder):**  
![](./media/computer_architecture/full_adder.png)
- **arithmetic logic unit (ALU):** combines a variety of arithmetic & logical operations into a single unit that performs only one function at a time (using function select lines)  
![](./media/computer_architecture/arithmetic_logic_unit.png)
- **tri-state buffer:** enables gating of different signals onto a wire  
**floating signal (`X`):** signal that is not driven by any circuit, like a open circuit floating wire  
![](./media/computer_architecture/tri_state_buffer.png)  
example: imagine a wire connecting the CPU & memory, at any time either CPU or memory can place a value on the wire but not both, we can have two tri-state one driven by CPU and other memory  
![](./media/computer_architecture/tri_state_buffer_example.png)
- **binary coded decimal:** each decimal is encoded with a fixed number of bits, example: normal vs BCD clock  
![](./media/computer_architecture/binary_coded_decimal.png)

# sequential logic
- **sequential logic:** outputs are determined by previous & current values of inputs (has memory)  
![](./media/computer_architecture/sequential_circuit.png)
- **cross-coupled inverters:** basic sequential logic element with two stable states `Q = 0` & `Q = 1`, not useful without a control mechanism for setting Q  
![](./media/computer_architecture/cross_coupled_inverters.png)
- **R-S latch:** two NAND gates with outputs feeding into each other's input (cross-coupled), data is stored at `Q`, `S` & `R` are control inputs
  - **idle:** `S` & `R`held at `1` so output determined by stored data (previous `Q`)
  - **set:** drive `S` to `0` (keeping `R` at `1`) to change `Q` to `1`
  - **reset:** drive `R` to `0` (keeping `S` at `1`) to change `~Q` to `1`
  - **forbidden:** `S` & `R` should never both be `0` at the same time, then `Q` & `~Q` will be `1` which is not possible  
  **metastability:** if `S` & `R` transition back to `1` at the same time then `Q` & `~Q` will oscillate between `1` & `0` because their final values depend on each other, this eventually settles depending on variation in circuits  
![](./media/computer_architecture/r_s_latch.png)
- **gated D latch:** to guarantee correct operation of R-S latch (`S` & `R` never `0` at the same time) add two more NAND gates  
`Q` takes the value of `D` when `WE` set to `1`  
![](./media/computer_architecture/gated_d_latch.png)
- **register:** structure that holds more than one bit and can be read from & written to, use multiple D-latches with a single `WE` signal for simultaneous writes  
![](./media/computer_architecture/register.png)  
**memory:** is comprised of locations that can be written to or read from  
**address:** unique value to index each location in memory  
**addressability:** the number of bits of information stored in each location, example: byte-addressable & word-addressable  
**address space:** total number of uniquely identifiable locations in memory  
example: memory with 4 locations with 3bits each  
for reading data: address decoder selects one wordline row and output shows up in `D[bit]`  
for writing data: address decoder selects one wordline row and `WE` is `1` input `Di[bit]` written to latches  
![](./media/computer_architecture/memory.png)  
to read location (row) 3  
![](./media/computer_architecture/memory_example.png)
- **state:** of a system is a snapshot of all relevant elements of the system at the moment of the snapshot  
state transitions occur when they occur in an asynchronous machine, state transitions take place after fixed units of time in synchronous machines, most modern machines are synchronous  
**clock:** is a general mechanism that triggers transition from one state to another in a sequential circuit, synchronizes state changes across sequential circuit elements  
combinational logic evaluates for the length of the clock cycle, so clock cycle should be chosen to accommodate maximum combinational circuit delay
- **finite state machines (FSM):** discrete-time model of a stateful system, each state represents a snapshot of the system at a given time, pictorially shows all possible states and how system transitions from one state to another  
at the beginning of the clock cycle, next state is latched into the state register  
![](./media/computer_architecture/finite_state_machine.png)
- **FSM constituents:**
  - **sequential circuits:** for state registers, store current state and load next state at clock edge
  - **combinational circuits:** for next state & output logic, determine the next state and generate the output
- **state register implementation:**
  - need to store data at the beginning of every clock cycle
  - data must be available during the entire clock cycle  
![](./media/computer_architecture/fsm_sequential.png)
- **why not latch:** is we simply wire a clock to `WE` of a latch, when the clock is low `Q` will not take `D`'s value, when the clock is high the latch will propagate `D` to `Q`  
![](./media/computer_architecture/fsm_latch.png)
- **D flip-flop:** is used for implementing state registers, `D` is observable at `Q` only at the beginning of next clock cycle and `Q` is available for the full clock cycle  
clock low ⟶ master sends `D` (`Q` unchanged) ⟶ clock high ⟶ slave latches `D` in `Q`  
so at rising/positive edge of clock `Q` get assigned `D`  
![](./media/computer_architecture/d_flip_flop.png)
- flip-flop is an edge-triggered state element, latch is a level-triggered state element
- **FSM types:**
  - **Moore:** output depends only on current state
  - **Mealy:** output depends on the current state and the inputs  
![](./media/computer_architecture/fsm_types.png)
- **example: snail looking for `1101` pattern:**  
![](./media/computer_architecture/fsm_example.png)
- **FSM state encoding:**
  - **fully encoded:** minimize number of flip-flops (by using `log2(num_states)` bits) but not necessarily output & next state logic, example: `00`, `01`, `10`, `11`
  - **1-hot encoded:** maximize flipflops and minimize next state logic, use `num_states` bits to represent states, example: `0001`, `0010`, `0100`, `1000`
  - **output encoded:** minimize output logic, output can be deduced from state encoding, only works for Moore machines, example: `001` (red), `010` (yellow), `100` (green), `110`(red & yellow)

# timing & verification
- **functional specification:** describes relationship between inputs & outputs  
**timing specification:** describes delay between inputs changing and outputs responding
- **combinational circuit delay:** circuit outputs change some time after the inputs change due to capacitance & resistance in a circuit and finite speed of light (which is not so fast in nanosecond level)  
![](./media/computer_architecture/combinational_circuit_delay.png)
- **contamination delay:** minimum delay  
**propagation delay:** maximum delay  
**cross hatching:** output could be changing (centre part)  
**critical path:** path with longest propagation delay  
![](./media/computer_architecture/delay_types.png)  
**critical path:** longest delay path  
![](./media/computer_architecture/critical_path.png)
- **glitch:** one input transition causes multiple output transitions due to difference in delays in two paths `n1` & `n2`  
![](./media/computer_architecture/timing_glitch.png)
- **sequential circuit timing:** `D` & `Q` in a D flip-flop have their own timing requirement
  - **input:** `D` must be stable when sampled at rising clock edge  
  aperture time is the time around clock edge that data must be stable  
  ![](./media/computer_architecture/sequential_timing_input.png)  
  **metastability:** if `D` is changing when sampled (aperture time) flip-flop output is stuck somewhere between `1` & `0`, output eventually settles non-deterministically  
  ![](./media/computer_architecture/metastability.png)
  - **output:** output `Q` starts changing at contamination delay clock-to-q and ends changing at propagation delay clock-to-q  
  ![](./media/computer_architecture/sequential_timing_output.png)
- **clock skew:** time difference between two clock edges, because clock does not reach all parts of the chip at the same time  
![](./media/computer_architecture/clock_skew.png)  
example: clock skew spatial distribution for Alpha 21264  
![](./media/computer_architecture/clock_skew_example.png)  
to keep skew to minimum intelligent clock network are required across a chip to make sure clock arrives at all locations at roughly the same time  
![](./media/computer_architecture/clock_network.png)

# instruction set architecture
- **von Neumann model:** program stored in memory (unified instruction & data memory), processor fetches then processes instruction sequentially one at a time, easier to debug since you know which instruction will execute  
but pipelining, SIMD, OoO execution, separate data & instruction cache in modern processors are not consistent with von Neumann model  
**Harvard model:** was developed to overcome the bottlenecks of von Neumann model by having separate instruction & data memory & bus  
**data flow model:** instruction fetched and executed only when its operands are ready, no need for a instruction pointer, inherently more parallel  
![](./media/computer_architecture/control_vs_dataflow_example.png)
- **register:** memory is large but slow, so registers ensure fast access to values to be processed in the ALU, typically one register contains one word  
**register file/set:** set of registers that can be manipulated by instructions, example: ARMv7-A has `32 x 32bit` registers
- **special purpose registers:**
  - **stack pointer (`SP`):** address of top of the stack
  - **link register (`LR`):** return address
  - **instruction register (`IR`):** current instruction
  - **program counter (`PC`) / instruction pointer (`IP`):** address of next instruction to execute, incremented by `1` in word-addressable memory and by word-length in byte-addressable memory
  - **program status register (`PSR`):** zero (`Z`), negative (`N`), carry (`C`), overflow (`V`)
  - **memory address register (`MAR`):** address to read/write  
  **memory data/buffer register (`MDR`/`MBR`):** data from read or to write  
  to read data: load `MAR` with the address, then data gets placed in `MDR`  
  to write data: load `MAR` with the address and `MDR` with the data, then activate write enable signal
- **instruction set architecture (ISA):** is the interface between what software commands and what the hardware carries out, specifies memory organization, register set & instruction set (opcodes, data types & addressing modes)  
**instruction:** most basic unit of computer processing, made up of opcode & operands  
if instructions are the words in the language of a computer, then ISA is the vocabulary
- instruction set can have large or small set of opcodes, tradeoffs like hardware complexity vs software complexity and latency of simple vs complex operations are involved  
**complex instruction:** an instruction does a lot of work, example: string copy, vector add  
**simple instruction:** an instruction does little work, it is a primitive using which complex instructions can be built, example: add, XOR, multiply  
complex instructions will have denser encoding (so smaller code size and better memory utilization) and simpler compiler but will have larger chunks of work (limited compiler optimizations) and more complex hardware
- **opcode:** what instruction does, three types:
  - **operate:** execute instructions in the ALU
  - **data movement:** read from or write to memory
  - **control flow:** change the sequence of execution
- **opcode encoding:** defines how instructions are encoded as binary values in the machine code  
![](./media/computer_architecture/opcode_encoding.png)
- **instruction cycle:** sequence of steps/phases that an instruction goes through to be executed, not all instructions requires all six phases (`ADD R0, R1, R2` doesn't need to evaluate the address)  
in a von Neumann machine fetch & fetch operands stage interpret memory as instruction & data respectively, so memory interpretation depends on when that value is fetched in the processing cycle
  - **fetch:** obtain instruction from memory and load it into the `IR`
  - **decode:** identifies the instruction to be processed
  - **evaluate address:** computes the address of memory location of operands
  - **fetch operands:** obtains the source operands, in latest processors fetch is done in parallel to decode
  - **execute:** executes the instruction
  - **store result:** write to the designated destination, once done cycle starts again for a new instruction
- **semantic gap:** how close instructions & data types are to high-level language, complex instructions & data types (like matrix) lead to smaller semantic gap hence better mapping of high programming constructs to hardware but lead to more work for the micro-architect  
![](./media/computer_architecture/semantic_gap.png)  
this tradeoff can be changed by translating from one ISA into a different one, example: Apple Rosetta hardware translator  
![](./media/computer_architecture/semantic_gap_hardware_translator.png)

## assembly programming
- a machine language encodes instructions as sequences of `0`s and `1`s but this encoding is unwieldy for human programmers, so we use an assembly language when we want to dictate the precise instructions that the computer is to perform, an assembler will translate a file containing assembly language code into the corresponding machine language  
for each ISA there must be a different assembly language since the assembly language must correspond to an entirely different set of machine instructions
- **why ARM ISA over IA32 (x86):**
  - assembly language programming is rarely used for more powerful computing systems, but for small devices due to power & price constraints developers still use assembly language to use the resources as efficiently as possible
  - multiple extensions to IA32 lead it to be far more complicated
  - IA32 dates from the 1970s, ARM is more representative of more modern ISA designs
- **immediate:** a constant placed directly in an instruction, it is immediately available to the processor when reading the instruction
- **opcodes:**  
older ARM chips lacks any instructions related to division because designers felt division is rarely necessary to merit wasting transistors on the complex circuit that it requires, but division by powers-of-2 can be done using right shifts  
except `TST`, `TEQ`, `CMP` & `CMN` all arithmetic instructions may modify PSR flags by postfixing `S` to opcode
  ```cpp
  // arithematic
  //; mnemonic dest, src1, src2
  AND regd, rega, argb  //; regd ⟵ rega & argb
  EOR regd, rega, argb  //; regd ⟵ rega ^ argb
  SUB regd, rega, argb  //; regd ⟵ rega - argb
  RSB regd, rega, argb  //; regd ⟵ argb - rega, REVERSE SUB
  ADD regd, rega, argb  //; regd ⟵ rega + argb
  ADC regd, rega, argb  //; regd ⟵ rega + argb + C (carry from PSR)
  SBC regd, rega, argb  //; regd ⟵ rega - argb - !C
  RSC regd, rega, argb  //; regd ⟵ argb - rega - !C
  TST rega, argb        //; set flags for rega & argb, result discarded, TEST
  TEQ rega, argb        //; set flags for rega ^ argb, result discarded, TEST_EQUIVALENCE
  CMP rega, argb        //; set flags for rega - argb, COMPARE
  CMN rega, argb        //; set flags for rega + argb, COMPARE_NEGATIVE
  ORR regd, rega, argb  //; regd ⟵ rega | argb
  BIC regd, rega, argb  //; regd ⟵ rega & ~argb, BIT_CLEAR
  MVN regd, arg         //; regd ⟵ ~argb, MOV_NOT

  // branching
  B   label             //; unconditional branch
  BNE label             //; branch if not equal

  // memory
  MOV rega, arg         //; rega ⟵ arg, used to load from another register or immediate (upto 12bits)
  LDR regd, [rega]      //; regd ⟵ *rega, LOAD_REGISTER, to load from RAM or for large immediate values
  STR regd, [rega]      //; regd ⟶ *rega, STORE_REGISTER
  // LDRB & STRB are 8bit variants
  ```
- **condition codes:** each instruction may incorporate a condition code specifying that the operation should take place only when certain combinations of the flags hold, condition code usually comes at the end of the opcode (precedes the optional `S` on arithmetic instructions)
  ```cpp
  EQ          //; Z               equal
  NE          //; !Z              not equal
  CS/HS       //; C               carry set / unsigned higher or same
  CC/LO       //; !C              carry clear / unsigned lower
  MI          //; N               minus/negative
  PL          //; !N              plus/positive or zero
  VS          //; V               overflow set
  VC          //; !V              overflow clear
  HI          //; C && !Z         unsigned higher
  LS          //; !C || Z         unsigned lower or same
  GE          //; N == V          signed greater than or equal
  LT          //; N != V          signed less than
  GT          //; !Z && (N == V)  signed greater than
  LE          //; Z || (N != V)   signed greater than or equal
  AL/omitted  //; true            always
  ```
- **shift flags:** used with addressing modes  
![](./media/computer_architecture/shift_types.png)
  - **logical shift left (`LSL`):** `a << b`
  - **logical shift right (`LSR`):** `a >> b`
  - **arithmetic shift right (`ASR`):** `a >> b` with sign extension  
  arithmetic shift left is same as logical shift left
  - **rotate right (`ROR`):** circular `a >> b` with wrap around
- **addressing mode:** is the mechanism for specifying where an operand is located, more addressing modes enables better mapping of high-level programming constructs (like pointer arithmetic) to hardware but more work for the micro-architect and more options for the compiler to choose  
![](./media/computer_architecture/addressing_modes.png)
  - **unmodified value:** the register or a value is delivered unchanged, example: `MOV R0, #1234` & `ADD R0, R1, #16`
  - **modified value:** provided value or register is shifted or rotated, example: `MOV R0, R1, LSL #2`
  - **register indirect:** register value is used to provide the address of the memory region to be accessed, example: `LDR R0, [R1]`
  - **relative register:** offset applied to a register value generates the memory address, example: `LDR R0, [R1, #4]`
  - **base indexed:** memory address is produced by adding the values of two registers, example: `LDR R0, [R1, R2]`  
  also supports:
    -  **pre-indexing:** apply the offset before accessing the memory, example: `LDR R0, [R1, #8]!`, first `R1 ⟵ R1 + #8` then load from new `R1`
    -  **post-indexing:** apply the offset after accessing the memory, example: `LDR R0, [R1], #8`, first load from unmodified `R1` then update `R1 ⟵ R1 + #8`
  - **base with scaled register:** memory address is produced by adding a register value to another register that is modified, example: `LDR R0, [R1, R2, LSL #2]`  
  also supports pre & post indexing
- **example: loop in C vs assembly:**
  ```cpp
  // C
  int total;
  int i;

  total = 0;
  for (i = 10; i > 0; i--)
  {
      total += i;
  }

  // assembly
        MOV  R0, #0      //; R0 accumulates total
        MOV  R1, #10     //; R1 counts from 10 down to 1
  again ADD  R0, R0, R1
        SUBS R1, R1, #1
        BNE  again
  halt  B    halt        //; infinite loop to stop computation
  ```
- **example: strcpy in assembly:**
  ```cpp
  strcpy  LDRB R2, [R1], #1  //; R1 is source
          STRB R2, [R0], #1  //; R0 is destination
          TST R2, R2         //; repeat if R2 is nonzero
          BNE strcpy
          END
  ```

# micro-architecture
- **micro-architecture (μArch):** is an implementation of the ISA, to ensure backwards compatibility μArch keeps changing with constant ISA interface, example: `add` instruction vs underlying adder implementation
- ISA specifies how the programmer sees the instructions to be executed but μArch can execute instructions in any order as long as it obeys the semantics specified by the ISA when making instruction results visible to software  
so anything like pipelining, speculative execution, OoO execution can be done in HW without exposure to SW  
- processing an instruction (all 6 stages) should transform architectural (or programmer visible) state (memory, registers & program counter) according to ISA specification  
ISA defines abstractly what `AS'` should be given an instruction & `AS` and there are no intermediate states between `AS` & `AS'` during instruction execution  
μArch implements how `AS` is transformed to `AS'`, but can have multiple programmer-invisible states to optimize the speed of instruction execution  
so we have two choices
    - **single-cycle machines:** each instruction takes single clock cycle, all state updates made at the end of an instruction's execution, but clock cycle time is determined by the slowest instruction (usually memory access) even though many instructions don't need that long  
    everything related to an instruction happens in one clock cycle  
    inefficient design because multiple functional unit copies required, example: same ALU cannot be used for performing arithmetic opcode operation & `PC += 4`  
    ![](./media/computer_architecture/single_cycle_machines.png)
    - **multi-cycle machines:** let instruction processing take as much time it needs, internal state updates can be made during instruction's execution, but architectural state updates only at the end of an instructions execution, will need extra registers to store intermediate results  
    any of the instruction cycle stage can also take multiple cycles  
    latency of one part of instruction processing can be overlapped with another  
    ![](./media/computer_architecture/multi_cycle_machines.png)
- **performance basics:** execution time of
  - **instruction:** `cycles_per_instruction x clock_cycle_time`
  - **program:** `num_instructions x average_CPI x clock_cycle_time`, aka iron law of performance
- **instruction processing needs two components:**
  - **datapath:** hardware elements that deal with & transform data signals, made up of functional unit operating on data, storage units (like registers) and hardware structures (like wires & muxes) that enable flow of data into functional units & registers
  - **control logic:** hardware elements that determine the control signals that specify what datapath elements should do to the data  
in multi cycle machines, control signals needed in the next cycle can be generated in the current cycle
- **μArch design principles:**
  - **critical design path:** decrease the maximum combinational logic delay, break a path in to multiple cycles if it takes too long
  - **common case design:** spend time & resources on where it matters most, similar to Amdahl's law
  - **balanced design:** balance instruction/data flow through hardware components to eliminate bottlenecks

## microprogramming
- **microprogramming:** for a multi cycle μArch instruction processing cycle is divided into states, it sequences from state to state to process an instruction, the behavior of the entire processor can be specified fully by a FSM
- **microinstruction:** control signal associated with the current state  
**microsequencing:** determining the next state and the microinstruction for the next state  
**control store:** stores control signals (microinstructions) for every possible sate (entire FSM)  
**microsequencer:** determines which set of control signals will be used in the next clock cycle (next state)  
the designer can translate any desired operation into a sequence of microinstructions
- **example: MIPS LC-3b control & datapath:** 26 bits passed to data path, 9 bits go back to microsequencer to fetch microinstruction (control signals) for next cycle in parallel  
control signals (microinstruction) for the current state control two things: processing in the data path and generation of control signals for the next cycle, so datapath & microsequencer operate concurrently  
![](./media/computer_architecture/microprogramming.png)
- **advantages of microprogrammed control:**
  - allows a simple design to do powerful computation by controlling the datapath (using a sequencer)
  - enables easy extensibility of the ISA  
  can support a new instruction by changing the microcode  
  can support complex instructions (string copy) as a sequence of simple microinstructions
  - enables update of machine behavior  
  a buggy implementation of an instruction can be fixed by changing the microcode in the field

# pipelining
- **pipelining:** with multi-cycle design some hardware resources are idle during different phases of instruction processing cycle so pipeline the execution ("assembly line processing") of multiple instructions for better hardware utilization & instruction throughput (which increases as number of stages increase)  
![](./media/computer_architecture/pipelining.png)
- **example: multi-stage vs pipelining:** fetch ⟶ decode ⟶ execute ⟶ writeback  
![](./media/computer_architecture/multicycle_vs_pipelining_1.png)  
![](./media/computer_architecture/multicycle_vs_pipelining_2.png)
- **steady state:** when the pipeline is full, throughput will be 1 instruction every cycle
- **ideal pipeline:** increase throughput with little increase in cost
  - same operation is repeated on large number of different instructions
  - no dependencies between instructions
  - processing can be evenly divided into uniform-latency sub-operations (that do not share resources)
- **practical pipeline:**
  - different instructions don't all need the same stages, example: `MOV` during execute stage  
  - need to detect and resolve inter-instruction dependencies to ensure the pipeline provides correct results, can lead to stalls (pipeline stops moving)  
  - some pipe stages are too fast but are forced to take the same clock cycle time (as slowest stage)
- **issues in pipeline design:**
  - balancing work in pipeline stages
  - keeping the pipeline correct, moving & full in the presence of events that disrupt pipeline flow like dependencies, resource contention & long latency (multi-cycle) operations
  - handling exceptions & interrupts
- **dependencies:** dictate ordering requirements between instructions, three types: structural, data & control
- **structural dependency:** happens when instructions in two pipeline stages need the same resource, solutions are:
  - eliminated the cause of contention by duplicating resources (like separate instruction & data caches) or increase its throughput (like multiple ports for memory structures)
  - detect resource contention and stall one of the contending stages
- **data dependency:** current instruction needs previous output  
![](./media/computer_architecture/data_dependency.png)
  - **flow (read after write):** always needs to be obeyed because they constitute true dependency on previous output value
  - **anti (write after read):** exists due to limited number of architectural registers, dependency on a (register) name only not on value
  - **output (write after write):** cause same as anti dependency
- **control dependency:** special case of data dependency on the instruction pointer (`IP`/`PC`), for a control-flow instruction next instruction known only once branch is evaluated
- **detecting data dependencies:** between instructions in a pipelined processor to guarantee correct execution
  - **scoreboarding:** each register in register file has associated valid bit associated with it, an instruction writing to register resets the bit, instruction in decode stage will check if all source & destination register are valid  
  just 1bit per register but need to stall for all dependencies not just flow
  - **combinational dependency check logic:** special logic that checks if any instruction in later stages is supposed to write to any source register of the instruction that is being decoded  
  stalls for flow dependencies only but logic becomes more complex as pipelines gets deeper & wider
- **stall:** make the dependent instruction wait until its source data value is available  
**bubble:** insert `NOP`s instructions to ensure stalled instruction stays in its stage  
**interlocking:** detection of dependence between instructions to guarantee correct execution
- **resolving flow dependencies:**
  - **stall:** till dependent value is updated in register file (HW based interlocking)
  - **compile-time detection & elimination:** insert `NOP`s (bubble) at compile time (SW based interlocking)
  - **data forwarding/bypassing:** data value needed by the consumer instruction can be supplied directly from a later stage in the pipeline (instead of only from the register file), brings a pipeline closer to data flow execution principles  
  ![](./media/computer_architecture/data_forwarding.png)  
  sufficient to resolve raw data dependency but stalling is necessary for memory-execution dependency  
  ![](./media/computer_architecture/data_forwarding_stall.png)
  - **out-of-order execution:** move it out of the way for independent instructions
  - **speculative execution:** predict the needed values then execute speculatively & verify
  - **fine-grained multithreading:** do something else
- **resolving anti & output data dependencies:** always write to the destination only in the last stage and in program order
- **instruction scheduling:** order in which instructions are executed in pipeline
  - **static:** software based instruction scheduling, compiler orders the instruction then hardware executes them in that order, can get runtime information (like instruction latency & branch history) through profiling
  - **dynamic:** hardware based instruction scheduling, hardware can execute instruction out of the compiler-specified order, has extra runtime information like variable length operation latency, memory address, branch history
- **multi-cycle execution:** not all instructions take same amount of time in the execute stage, so we have multiple different functional units that take different number of cycles  
this can let independent instruction start execution on a different functional unit before a previous long-latency instruction finishes execution  
![](./media/computer_architecture/multi_cycle_execution.png)  
but architectural states are not updated in a sequential manner so sequential semantics of von Neumann ISA is not preserved  
example: first instruction throws exception but second instruction is already executed and has modified the architectural state  
![](./media/computer_architecture/multi_cycle_execution_issue.png)
- **exception:** are due to internal problems in execution of the program, handle when detected, example: divide by 0, page fault  
**interrupt:** are due to external events that need to be handled by the processor, handle when convenient except for very high priority ones like power failure, example: keyboard input, system timer expiration  
both require stopping of current program, saving the architectural state and switch to handler (then if possible return back to program execution)
- **retire/commit:** finish execution and update architectural state  
**precise:** all previous instructions should be completely retired and no later instruction should be retired  
**precise exception/interrupt:** architectural state should be consistent (precise) when the exception/interrupt is ready to be handled  
required because von Neumann model ISA specifies it, also aids software debugging by ensuring clean slate between two instruction and enables software traps (software implemented opcodes)
- **handling exceptions in pipelining:** when the oldest instruction ready-to-be-retired is detected to have caused an exception, control logic:
  - ensures architectural state is precise
  - flush younger instruction in the pipeline (to process the exception handler)
  - saves `PC` & registers (as specified by the ISA)
  - redirects the fetch engine to the appropriate exception handling routine
- **example: ensuring precise exceptions in pipelining:** for single-cycle machines instruction boundaries are cycle boundaries anyway  
for multi-cycle machines make each operation take the same amount of time, slowest instruction latency determines all other instructions' latency but worst-case can be very high for memory operations  
![](./media/computer_architecture/precise_exceptions_pipelining.png)

# reorder buffer
- idea is to complete instruction execution out-of-order but reorder them before making results visible to architectural state (rollback on mispredictions), useful for multi-cycle precise exceptions  
![](./media/computer_architecture/reorder_buffer.png)
- **reorder buffer (ROB):** hardware structure that keeps information about all instructions that are decoded but not yet retired, working cycle is:
  - when instruction is decoded, it reserves the next-sequential entry in the ROB
  - when instruction completes, it writes result into ROB entry
  - when instruction oldest in the ROB and has completed without exceptions, its results moved into register file (or memory)
- **ROB entry:** should contain everything to:  
![](./media/computer_architecture/reorder_buffer_entry.png)
  - correctly reorder instructions back into the program order
  - update the architectural state with instruction's results
  - handle an exception/interrupt precisely
  - also needs valid bits to keep track of readiness of the results and to find out if the instruction has completed execution
- execution is simple for independent operations  
![](./media/computer_architecture/reorder_buffer_execution.png)  
but in case of data dependency the value can be in the register file, reorder buffer or bypass path  
![](./media/computer_architecture/reorder_buffer_access.png)
- **simplifying ROB access:** to get rid of (costly) content-addressable memory for ROB we instead use indirection
  - check register file first and check if register valid bit is set, if register invalid then it stores the ID of the reorder buffer entry that contains (or will contain) the value of the register
  - check reorder buffer next
- **register renaming:** mapping of register to ROB entry, register file maps/renames the register to a ROB entry if there is an in-flight instruction writing to that register  
**link instruction dependencies:** whenever an instruction at a particular ROB entry finishes execution it can broadcast its result to every instruction waiting for that ROB entry, name (ROB entry) is used to communicate the data value  
ROB is not constrained by ISA interface (unlike register file), so it can be huge and can have many instructions writing to the same architectural register (eliminates stalls due to false dependencies)
- **dispatch:** act of sending an instruction to a functional unit
- **in-order pipeline with reorder buffer:** in-order dispatch/execution, out-of-order execution and in-order retirement  
![](./media/computer_architecture/reorder_buffer_inorder_pipeline.png)  
  - **decode (D):** access register file or ROB, allocate entry in ROB, check if instruction can execute, if so dispatch instruction
  - **execute (E):** instructions can complete out-of-order
  - **completion (R):** write result to reorder buffer
  - **retirement (W):** check for exceptions

## history buffer
- idea is to update the register file when instruction completes, but undo the updates when an exception occurs, working cycle is:  
![](./media/computer_architecture/history_buffer.png)
 - when instruction is decoded, it reserves an HB entry
 - when instruction completes, it stores the old value of its destination in the HB
 - when instruction is oldest and no exceptions/interrupts, the HB entry discarded
 - when instruction is oldest and an exception needs to be handled, old values in the HB are written back into the architectural state from tail to head
- advantage over ROB is that HB is not on the critical path but increased exception handling latency due to unwinding of history buffer  
but assuming exceptions are rare then HB is better for common case

## future file
- idea is to keep two register files (speculative/future & architectural), future file is used for fast access to latest register values and architectural files is used for state recovery on exceptions  
![](./media/computer_architecture/future_file.png)
  - architectural register file is updated in program order for precise exceptions and a reorder buffer used to ensure in-order updates
  - future register file is updated as soon as an instruction completes, so value is always from the youngest instruction to write the register
- advantage over ROB is no need to read the new values from the ROB (or indirection) but in case of an exception architectural file needs to be copied to future file
- branch mispredictions are much more common than exceptions, so to minimize the performance impact of mispredictions  
**checkpointing:** checkpoint the future file at the time a branch is decoded and keep the checkpointed state updated with results of instructions older than the branch, but upon branch misprediction restore the checkpoint associated with the branch

# out-of-order execution
- **out-of-order (OoO) execution:** (or dynamic instruction scheduling) idea is to move the dependent instructions out of the way of independent ones to ensure that true data dependency does not stall the processor  
dependent instructions are moved to into rest areas and monitor their source values, dispatch/fire the instruction when all source values are available  
instructions dispatched in dataflow (not control flow) order but not exposed to ISA
OoO execution tolerates the latency of multi-cycle operations (like memory) by executing independent operations concurrently
- **reservation stations:** rest areas for dependent instructions or instructions waiting for hardware (adder, multiplier)
- **example: in-order dispatch (ROB) vs out-of-order dispatch:** ROB gets rid of stalls due to false dependencies but a flow dependence still stalls the pipeline which OoO dispatch solves  
example: assume `IMUL` takes 4 cycles and `ADD` takes 1, then first ADD stalls the entire pipeline  
![](./media/computer_architecture/in_order_vs_out_of_order.png)
- **enabling OoO execution:**
  - **link consumer of a value to the producer:** associate a tag (like reservation station ID) with each data value (register renaming)  
  eliminates false dependencies
  - **buffer instructions until they are ready to execute:** insert instruction into reservation stations after renaming  
  enables the pipeline to move for independent operations
  - **keep track of readiness of source values:** broadcast the tag when the value is produced, instructions compare their source tags to the broadcast tag, if it matches then source value ready  
  enables communication of readiness of produced value between instructions
  - **dispatch the instruction to its functional unit when source values ready:** instruction wakes up if all sources are ready, if multiple instructions are awake select one per functional unit  
  enables out-of-order dispatch
- **future/frontend register alias table:** an instruction updates this when it completes execution, if valid bit set data value used, if valid bit reset tag used, used for renaming  
**architectural/backend register alias table:** an instruction updates this when it retires, always updated in program order, used for maintaining precise state  
on an exception: flush pipeline, copy architectural RAT into frontend RAT
- **OoO execution:** is basically Tomasulo's algorithm (out-of-order with register renaming) with precise exceptions, without precise exceptions processor was terrible to debug  
**instruction window:** all decoded but not yet retired instruction, a dataflow graph which is limited to this window (restricted dataflow) is dynamically built (so latency tolerance depends on the window size)  
two humps are reservation station (scheduling window) and reordering (ROB or instruction/active window)  
![](media/computer_architecture/out_of_order_execution.png)
  - **find operand dependencies:** if there is any dependency set tag (register renaming), else use data value directly
  - **scheduling:** buffer instruction (with tag and/or data values) to reservation station, each functional unit has its own reservation station
  - **execute when ready:** wait for data/resource dependencies to resolve
  - **dispatch instruction if source values ready:** output tag is broadcasted when value is produced, each instruction compare their source tags to broadcasted one, instruction wakes up when source values ready
  - **reorder output:** instruction updates output value in frontend RAT, then instruction added to reorder buffer  
  backend RAT will be updated when instruction retires on becoming oldest instruction
- **example: OoO execution:** assume 1 adder & 1 multiplier  
![](./media/computer_architecture/out_of_order_execution_example_1.png)  
at the end of cycle 7  
![](./media/computer_architecture/out_of_order_execution_example_2.png)  
dataflow graph from frontend RAT  
![](./media/computer_architecture/out_of_order_execution_example_3.png)
- **centralized physical register file:** data values stored at a common place (physical register file) that reservation station, frontend & backend RAT will indirect to, eliminates the need to maintain multiple copies of data values, now no need for data broadcast but tag broadcast still needed  
![](./media/computer_architecture/centralized_physical_register_file.png)
- **example: Pentium 4 micro-architecture:** OoO execution with centralized physical register file  
![](./media/computer_architecture/out_of_order_tables_example.png)

## memory dependence handling
- **register vs memory:**
  - register dependencies known statically  
  memory dependencies determined dynamically
  - register state is small  
  memory state is huge
  - register state is not visible to other threads/processors  
  memory state shared
- **memory dependency handling:** memory address is not known until a load/store executes (address computation)
  - renaming memory addresses is difficult (huge memory state)
  - determining dependency/independency of load/store need to be handled after their  partial execution (after address calculation done)
  - when a load has its address ready, there may be older stores with unknown address in the machine  
  similarly with a store having older loads with unknown address
- **memory disambiguation (unknown address) problem:** when a younger load has its address ready before an store's address is known
- **to detect store-load dependence:** a load's dependency status is not known until all previous store addresses are available
  - wait until all previous stores committed, no need to check for address match
  - keep a list of pending stores in a store buffer and check whether load address matches a previous store address
- **scheduling a load instruction:**
  - **conservative:** stall the load until all previous stores have computed their addresses (or even retired), no need for recovery but delays independent loads unnecessarily
  - **aggressive:** assume load is independent of unknown-address stores and schedule the load right away, simple and can be common case but recovery/re-execution of load & dependents on misprediction
  - **intelligent:** predict if the load is dependent on any unknown-address store, more accurate since load store dependencies over time but still recovery on misprediction
- **store-to-load forwarding logic:** cannot update memory out of program order so need to buffer all store & load instructions in instruction window  
modern processors use a load queue (LQ) & a store queue (SQ) for checking whether a load is dependent on a store and for forwarding data to load if it is dependent on a store
  - when a store instruction finishes execution, it writes its address & data to its ROB entry
  - when a load computes its address, it searches SQ (multiple SQ entries for multi-word load) with its address and then receives the value from youngest (closest in queue) older store that wrote to that address

# dataflow execution
- **pure (ISA level) dataflow:** availability of data determines order of execution, a data flow node fires when its sources are ready, programs represented as data flow graphs (of nodes)  
dataflow implementations at the μArch level (while preserving von Neumann model semantics) have been very successful (like OoO execution) but at ISA level have not been successful  
pure dataflow is very good at exploiting irregular parallelism (only real dependencies constrain processing) but no precise state semantics which makes debugging extremely difficult

# superscalar execution
- **superscalar execution:** fetch, decode, execute & retire multiple instructions per cycle, needs multiple copies of hardware resources (`N` wide superscalar means `N` instructions per cycle)
- superscalar execution and out-of-order execution are orthogonal concepts  
can have all four combinations of processors: [in-order, out-of-order] x [scalar, superscalar]
- **dependency checking:** dependencies make it tricky to issue multiple instructions in the same cycle, hardware performs the dependence checking between concurrently-fetched instructions, superscalar has vertical axis (within a pipeline stage) dependency check as well, OoO has only horizontal check (across pipeline stages)
- **example: 2-wide superscalar execution:** ideal case  
![](./media/computer_architecture/superscalar_dependency_example_1.png)  
with dependencies  
![](./media/computer_architecture/superscalar_dependency_example_2.png)
- superscalar execution gives higher instruction throughput but higher complexity for dependence checking as well and for a OoO superscalar processor register renaming also becomes complex

# branch prediction
- ![](media/computer_architecture/branch_types.png)
- **control dependencies handling:** critical to keep pipeline full with correct sequence of dynamic instructions
  - **stall:** the pipeline until we know the next fetch instruction
  - **branch prediction:** try to guess which way a branch will go before it is definitively known, flush pipeline on misprediction
  - **branch delay slot:** employ delayed branching by executing instructions that are independent of branch direction
  - **fine-grained multithreading:** do something else till branch direction known
  - **predicated execution:** eliminate control-flow instructions by converting them into data-flow instructions
  - **multipath execution:** fetch from both possible paths, need to know the addresses of both possible paths
- **branch problem:** control flow instructions (branches) are frequent but next fetch address after a control-flow instruction is not determined after `N` cycles (branch resolution latency) in a pipelined processor  
so if we are fetching `W` instructions per cycle (`W` wide superscalar pipeline) then branch prediction leads to `N x W` wasted instruction slots  
![](media/computer_architecture/branch_prediction.png)
- **branch misprediction penalty:** number of instructions flushed in case of misprediction  
![](./media/computer_architecture/branch_misprediction_penalty.png)
- **simplest branch prediction:** always predict the next sequential instruction is the next instruction to be execution (`PC += 4`)  
to maximize the chances software/compiler (based on profiling) lays out the control flow graph such that likely next instruction is on the not-taken path of a branch  
but most branches are usually loops (branch not-taken only for last iteration)
  ```cpp
  if (error)
  {
      // PC: less likely code
  }
  else
  {
      // PC + 4: most likely code
  }
  ```
- **early branch resolution:** predict the next fetch address (to be used in the next cycle) to avoid misprediction penalty  
target address remains the same for a conditional direct branch across dynamic instances, so store the target address in branch target buffer/cache (BTB) in a previous instance and index it with the `PC`  
![](./media/computer_architecture/enhanced_branch_prediction_1.png)  
use global branch history `XOR`ed (hashed) with `PC` to get better prediction accuracy  
![](./media/computer_architecture/enhanced_branch_prediction_2.png)  
we need three things to be predicted at fetch stage for early branch resolution:
  - **whether fetched instruction is a branch:** if BTB provides a target address for the `PC` then it must be a branch
  - **conditional branch direction:** branch prediction schemes used
  - **branch target address (if taken):** BTB remembers target address computed last time branch was executed
- **branch prediction:** guess which way a branch will go before this is known definitively  
it can be predicted either at compile time (static) or runtime (dynamic):
  - **static prediction schemes:** cannot adapt to dynamic changes in branch behavior, this can be mitigated (but not at a fine granularity) by a dynamic compiler (like java JIT compiler) but it has its own extra overheads
    - **always not-taken:** simple to implement, no need for BTB since no direction prediction (`PC += 4`), low accuracy but compiler can improve it (discussed earlier)
    - **always taken:** no direction prediction but need the BTB here, better accuracy  
    backward branch (target address lower than branch `PC` like loops) are usually taken
    - **backward taken forward not-taken:** predict backward branches as taken, others not-taken  
    this basically tries to distinguish between loop branches & other branches
    - **profile based:** compiler determines likely direction for each branch using a profile run and encodes that direction as a hint bit in the branch instruction format  
    more accurate since it is per branch prediction, but accuracy depends on the representativeness of profile input set
    - **program analysis based:** use heuristics (loosely based rules) based on program analysis to determine statically-predicted direction, heuristics should be representative  
    example: negative integers used as error values in many programs so predict `BLZ` (branch less than zero) as not-taken  
    example: pointer or floating-point comparisons as not-equal
    - **programmer based:** programmer provides the statically-predicted direction using pragmas (convey hints to lower levels of the transformation hierarchy) since you may know your program better than other analysis techniques  
    example: `if(likely(flag)) { ...}` to predict taken  
    example: `#pragma omp parallel` to direct OpenMP that loop can be parallelized
  - **run time (dynamic) prediction schemes:** predict branches based on dynamic information collected at runtime almost always by hardware
    - **one-bit (last-time) predictor:** guess branch will take same direction as its last instance, stored in BTB using a single bit per branch, misprediction when branch changes behavior (like always mispredicts the last & first iteration for loop branches) and changes prediction too quickly (0% accuracy if direction changes every time)
    - **two-bit counter based (bimodal) predictor:** add hysteresis to one-bit predictor so that the prediction does not change on a single different outcome, two bits per branch to track history of predictions using saturating arithmetic (`0`-`3`) counter, needs 2 opposing outcomes to change prediction scheme  
    ![](media/computer_architecture/two_bit_predictor.png)
    - a branch's outcome can be correlated with other branches' outcomes (global branch correlation)  
      ```cpp
      // global branch correlation
      // if first not-taken then second also not-taken
      if (cond1) { ... }
      if (cond1 && cond2) { ... }
      // if first not-taken then second always taken
      if (x < 1) { ... }
      if (x > 1) { ... }
      ```
      **global branch history predictor:** make a prediction based on the outcome of the branch the last time the same global branch history was encountered (associate branch outcomes with global taken/not-taken history of all branches)  
      keep track of the global taken/no-taken history of all branches in global history register (GHR)  
      use GHR to index into a table of 2bit counters (pattern history table (PHT)) that recorded the outcome that was seen for each GHR value in the recent past  
      so use two level of history: GHR and history for that pattern (from PHT)
      ![](media/computer_architecture/global_branch_history_predictor.png)
    - similarly a branch's outcome can be correlated with past outcomes of the same branch (local branch correlation) as well  
    **local branch history predictor:** similar to global branch history but on a per-branch basis  
    use local history registers (LHR) to index into PHT
    - **hybrid branch predictor:** use more than one type of predictor (multiple algorithms) and select the best prediction  
    better accuracy since different predictors are better for different branches  
    reduced warmup time by using faster-warmup predictor until the slower-warmup predictor warms up  
    example: tournament predictor  
    ![](./media/computer_architecture/tournament_predictor.png)
    - **loop branch detector & predictor:** loop iteration count detector/predictor, works well for loops with small number of iterations (where iteration count is predictable)  
    predict taken till loop iteration count is reached  
    ![](./media/computer_architecture/loop_branch_predictor.png)
    - **perceptron branch predictor:** use a perceptron to learn the correlations between branch history register bits and branch outcome  
    **perceptron:** simple binary classifier (modelled on biological neuron) that learns the linear function of how each input affects the output using a set of weights, maps a input vector `X` to a `0` or `1`  
    ![](media/computer_architecture/perceptron.png)
    - **history length based predictor:** different branches require different history lengths for better prediction accuracy, so have multiple PHTs indexed with GHRs with different history lengths and intelligently allocate PHT entries to different branches  
    ![](media/computer_architecture/history_length_based_predictor.png)
- **branch confidence estimation:** estimate how likely is the prediction correct, could be useful in deciding how to speculate like which predictor to choose  
example: keep a record of correct & incorrect outcomes for past N instances of the branch and estimate confidence based on them
- **delayed branching:** delay the execution of a branch by executing later instructions that are always executed regardless of branch direction (delay slots)  
compiler finds delay slot instructions to keep the pipeline full with useful instructions but not easy to fill the delay slots so `NOP` added if compiler cannot find independent instructions  
![](./media/computer_architecture/delayed_branching.png)
- **loop unrolling:** replicate loop body multiple times within an iteration, increases speed (by reducing/eliminating loop control logic) at the potential expense of its binary size (space–time tradeoff)  
it is often counterproductive on modern processors as the increased code size can cause more cache misses
- complex predicates are converted into multiple branches which increases the number of control dependencies  
**predicate combining:** combine predicate operations to feed a single branch instruction instead of having one branch for each  
each predicate stored & operated on using condition registers then a single branch checks the value of combined predicate (using condition registers)
- **predicated execution:** compiler converts control dependency to data dependency to eliminate a branch  
each instruction has a predicate bit set based on predicate computation, only instructions with true predicates are committed (others are turned into `NOP`s)  
enables straight line code by eliminating branches (no misprediction cost so highly efficient) and useful for hard-to-predict branches  
example: remove branch using conditional move (`CMOV`)
  ```cpp
  if (a == 5) { b = 4; } else { b = 3 }
  
  CMPEQ condition, a, 5
  CMOV condition, b, 4
  CMOV !condition, b, 3
  ```
- **example: predicated execution in Intel Itanium:** each instruction can be separately predicated using 64 one-bit predicate registers  
each instruction carries predicate register field (6bit) so an instruction is effectively a `NOP` if its predicate is false  
![](media/computer_architecture/predicated_execution_itanium.png)
- **multipath execution:** execute both paths (if you know the addresses) after a conditional branch  
useful for a hard-to-predict branches (prediction confidence is already low)  
improves performance if misprediction cost greater than useless work but for multiple nested branches paths followed will become exponential and duplicate work if paths merge (same instructions after branch)  
![](./media/computer_architecture/multipath_vs_predicated_execution.png)
- **handling other branch types:**
  - **call:** easy to predict since always taken & single target address  
  call marked in BTB and target predicted by BTB
  - **return:** is a indirect branch that can be called from many points in code, usually a return matches a call so use a stack to predict return addresses (return address stack)  
  when fetching a call: push the return address (next instruction) to stack  
  when fetching return: pop the stack and use the address as its predicted target
  - **indirect:** register-indirect branches can have multiple targets  
  two ideas: predict the previous resolved target (stored in BTB) as the next fetch address or use history based target prediction  
  ![](./media/computer_architecture/indirect_branches.png)  
  ![](./media/computer_architecture/indirect_branch_predictor.png)
- **branch prediction latency:** prediction is latency critical since we need to generate next fetch address for the next cycle  
bigger & more complex predictors are more accurate but slower  
![](./media/computer_architecture/branch_prediction_latency.png)

# very-long instruction word
- **very-long instruction word (VLIW):** consists of multiple independent instructions (`NOP`s if not found) packed/bundled together by the compiler, hardware fetches & executes the instructions in the bundle concurrently  
instructions can be logically unrelated (like `mov` & `add` together) and no need for dependency checking between concurrently-fetched instructions  
recompilation required when execution width (`N`) or instruction latencies or functional units change  
![](media/computer_architecture/very_large_instruction_word.png)  
- **lockstep (all or none) execution:** if any operation in a VLIW instruction (bundle) stalls then all concurrent operations stall  
in a truly VLIW machine, the compiler handles all dependency-related stalls and hardware does not perform dependency checking  
no operation can progress until the longest-latency instruction completes
- in RISC machines compiler does the hardwork to translate high-level language code to simpler instructions, hardware does little translation/decoding  
VLIW philosophy is similar to RISC (simple instructions and hardware), compiler does the hardwork to find instruction level parallelism (ILP), hardware stays as simple & streamlined as possible
- **example: Intel Itanium IA-64:** explicitly parallel instruction computing (EPIC) was not fully VLIW but based on VLIW principles  
instruction bundles can have dependent instructions, a few bits in the instruction format specify explicitly which instructions in the bundle are dependent on which other ones  
useful because it is not easy for compiler to find independent instructions

# systolic arrays
- **systolic array:** replace a single processing element (PE) with a regular array of PEs and carefully orchestrate flow of data between the PEs such that they collectively transform a piece of input data before outputting it to memory 
maximizes computation done on a single piece of data element brought from memory (balanced computation and memory bandwidth)  
similar to blood flow: heart ⟶ many cells ⟶ heart  
![](./media/computer_architecture/systolic_array.png)
- looks like a pipeline, but the array structure can be non-linear & multi-dimensional with PE connections being multi-directional  
also PEs can have local memory and execute kernels rather than a piece of the instruction  
![](./media/computer_architecture/systolic_array_multidimentional.png)
- **example: CNN:** machine learning has hundreds of convolutional layers  
![](./media/computer_architecture/convolutional_neural_network.png)  
convolve input with weights determined based on training on many many images
![](./media/computer_architecture/convolutional_neural_network_matrix_multiplication.png)  
**systolic computation for convolution:** here weights `wi` stay the same and `xi`s & `yi`s move systolically in opposite directions  
needs to be carefully orchestrated such that input to the array (data elements) are interleaved by one cycle and output is buffered every cycle  
  ```cpp
  y1 = (w1 * x1) + (w2 * x2) + (w3 * x3)
  y2 = (w1 * x2) + (w2 * x3) + (w3 * x4)
  y3 = (w1 * x3) + (w2 * x4) + (w3 * x5)
  ```  
  ![](./media/computer_architecture/systolic_computation_convolution.png)
- **systolic array features:**
  - **principled:** efficiently makes use of limited memory bandwidth by using each data item multiple times balancing computation to I/O bandwidth availability
  - **specialized:** computation needs to fit PE functions and organization, not generic for arbitrary operations
- **programmable systolic arrays:** each PE in systolic array can store multiple weights (selected on the fly), eases implementation of usecases like adaptive filtering  
when taken further, each PE can have its own data & instruction memory
- systolic array has lead to ideas like pipelined programs  
**pipeline-parallel programs:** loop iterations are divided into code segments which are executed on different cores  
used in file compression nowadays:  
allocate buffers ⟶ read input file ⟶ compress ⟶ write output file --> deallocate  
![](./media/computer_architecture/pipelined_programs.png)  
- **example: tensor processing unit:** systolic data flow of the matrix multiply unit  
software has the illusion that each 256B input is read at once and they instantly update one location of each of 256 output accumulator RAMs  
multiply-accumulate operation moves through the matrix as a diagonal wave  
![](./media/computer_architecture/tensor_processing_unit.png)

# decoupled access execute
- because Tomasulo's algorithm is too complex to implement  
**decoupled access execute:** decouple operand access and execution via two separate instruction streams that communicate via ISA-visible queues  
![](./media/computer_architecture/decoupled_access_execute.png)  
compiler generates two instruction streams (`A` & `E`), branch instruction requires synchronization between the two  
execute stream can run ahead of the access stream and vice versa (limited out-of-order execution without tagging, renaming, etc complexity)  
example: if `A` is waiting for memory `E` can perform useful work, or if `A` hits in cache it supplies data to lagging `E`  
compiler support required to partition the program and to manage the queues
- **example: DAE code:** compile Livermore loops (parallel computers benchmark) into CRAY-1 and DAE  
![](./media/computer_architecture/decoupled_access_execute_example.png)
- **example: Astronautics ZS-1:** single stream steered into A & E(or X) queues, each queue/pipeline in-order  
![](./media/computer_architecture/decoupled_access_execute_single_stream_example.png)
- **example: DAE in Intel Pentium 4:**  
![](./media/computer_architecture/decoupled_access_execute_pentium4_example.png)

# single instruction multiple data
- **Flynn's taxonomy of computers:**
  - **SISD:** single instruction operates on a single data element, example: single core processor
  - **SIMD:** single instruction operates on multiple data elements, example: array & vector processor
  - **MISD:** multiple instructions operates on a single data element, example: systolic array processor
  - **MIMD:** multiple instructions operates on multiple data elements (multiple instruction streams), example: multi-core processor
- **data parallelism:** concurrency arises from performing the same operation on different pieces of data, is a form of instruction level parallelism where the instruction happens to be the same across data  
contrast with data flow, concurrency arises from executing different operations in parallel in a data driven manner  
contrast with thread parallelism, concurrency arises from executing different threads of control in parallel
- **time-space duality:** single instruction operates on multiple data elements in time or in space  
![](./media/computer_architecture/array_vs_vector_processor.png)
  - **array processor:** instruction operates on multiple data elements at the same time using different spaces (processing elements)  
  example: 4 adders operates on 4 different input pairs concurrently
  - **vector processor:** instruction operates on multiple data elements in consecutive time steps using the same space, pipelined functional units where each stage operates on a different data element
- **vector:** one-dimensional array of numbers  
**stride:** distance in memory between two consecutive elements of a vector
- **vector processor:** is one whose instructions operate on vectors rather than scalar (single data) values, requirements are
  - **vector data registers:** to load/store vectors, each register holds `N` number of `M`-bit values
  - **vector length register (`VLEN`):** to operate on vectors of different lengths, maximum can be `N`
  - **vector stride register (`VSTR`):** can be used to access non-consecutive elements since elements of a vector can be stored apart from each other in memory  
example: set `VSTR = 8` to access `A` ⟶ `A+8` ⟶ `A+16` ⟶ `A+24`
  - **vector mask register (`VMASK`):** indicates which elements of vector to operate on, set by vector test instructions
- **vector instructions allow deeper pipelines:**
  - no intra-vector dependencies so no hardware interlocking needed within a vector
  - no control flow within a vector
  - known stride allows easy address calculation for all elements, even enables prefetching into registers/cache/memory
- **regular parallelism:** tasks are similar and have predictable dependencies, easier for SIMD to exploit, example: matrix multiplication  
**irregular parallelism:** the tasks are dissimilar in a way that creates unpredictable dependencies, example: search key in linked list
- memory (bandwidth) can easily become a bottleneck if:
  - compute/memory operation balance is not maintained
  - data is not mapped appropriately to memory banks
- **vectorizable loops:** a loop is vectorizable if each iteration is independent of any other
- **vector functional units:** use a deep pipeline to execute element operations (so fast clock cycle)  
control of deep pipeline is simple because elements in vector are independent  
![](media/computer_architecture/vector_functional_unit.png)
- **vector chaining:** data forwarding from one vector functional unit to another  
![](./media/computer_architecture/vector_chaining.png)
- **example: CRAY 1 vector machine:** scalar operations limit vector machine performance  
*if you were plowing a field, which would you rather use: two strong oxen or 1024 chickens?*  
here oxe is scalar processing and chicken is vector processing, so a powerful vector machine needs a powerful scalar processor as well  
![](./media/computer_architecture/vector_machine_example.png)
- **loading/storing vectors from/to memory:** elements can be loaded in consecutive cycles if we can start the load of one element per cycle  
if memory access takes more than 1 cycle: bank the memory and interleave the elements across banks  
**memory banking:** memory is divided into banks that can be accessed independently, banks share address & data buses (to minimize cost)  
can start and in parallel complete one bank access per cycle, so can sustain `N` parallel accesses if all `N` go to different banks  
![](./media/computer_architecture/memory_banking.png)
- **vector memory system:**  
![](./media/computer_architecture/vector_memory_system.png)  
we know `next address = previous address + stride`, we can sustain 1 element/cycle throughput if:
  - stride is 1
  - consecutive elements are interleaved across banks  
  if consecutive elements are from the same bank then second element access can be started only after first element access is completed (after bank latency)
  - number of banks is greater than or equal to bank latency  
  starting from `0 + bank_latency` cycle we can get 1 element/cycle, ensures there are enough banks to overlap enough memory operations to cover memory latency
- **example: element-wise average in scalar:**
  ```cpp
  // C
  for (i = 0; i < 50; i++)
  {
      C[i] = (A[i] + B[i]) / 2;
  }

  // scalar ASM
  MOVI R0 = 50          //; 1
  MOVA R1 = A           //; 1
  MOVA R2 = B           //; 1
  MOVA R3 = C           //; 1
  X: LD R4 = MEM[R1++]  //; 11 auto increment addressing
  LD R5 = MEM[R2++]     //; 11
  ADD R6 = R4 + R5      //; 4
  SHFR R7 = R6 >> 1     //; 1
  ST MEM[R3++] = R7     //; 11
  DECBNZ R0, X          //; 2 decrement and branch if NZ
  ```
  number of dynamic operations: `6 x 50 + 4 = 304` operations  
  execution time on in-order processor with 1 bank (load cannot be pipelined): `40 x 50 + 4 = 2004` cycles  
  execution time on in-order processor with 16 bank (> 11 bank latency so first two loads can be pipelined): `30 x 50 + 4 = 1504` cycles
- **example: element-wise average in vector:**
  ```cpp
  // vector ASM
  MOVI VLEN = 50        //; 1
  MOVI VSTR = 1         //; 1
  VLD V0 = A            //; 11 + VLEN - 1
  VLD V1 = B            //; 11 + VLEN – 1
  VADD V2 = V0 + V1     //; 4 + VLEN - 1
  VSHFR V3 = V2 >> 1    //; 1 + VLEN - 1
  VST C = V3            //; 11 + VLEN – 1
  ```
  number of dynamic operations: `7` operations  
  execution time with 16 banks with 1 memory port each (1 memory access at a time) but no chaining (entire vector register needs to be ready before any element can be used):`285` cycles  
  ![](./media/computer_architecture/vector_average_example_1.png)  
  execution time with 16 bank with 1 memory port each with chaining :`182` cycles  
  ![](./media/computer_architecture/vector_average_example_2.png)  
  execution time with 16 bank with 2 load ports and 1 store port each (2 load + 1 store at once) with chaining:`79` cycles  
  ![](./media/computer_architecture/vector_average_example_3.png)
- **vector stripmining:** if number of data elements is larger than `VLEN` then break loops such that each iteration operates on `VLEN` elements in a vector register  
example: for 527 elements and 64-element registers, 8 iterations where `VLEN == 64`, last iteration where `VLEN == 15`
- **scatter/gather operations:** if vector data is not stored in a strided fashion in memory then use indirection to combine/pack elements into vector registers, example: `A[i] = B[i] + C[D[i]]`  
gather is for loading data and scatter is for storing data  
vector load/store can use an index vector which will be added to the base register to generate the addresses  
  ```cpp
  // C
  for (i = 0; i < N; i++)
  {
      A[i] = B[i] + C[D[i]]
  }

  //vector ASM
  LV vD, rD          //; load indices in D vector
  LVI vC, rC, vD     //; load indirect from rC base
  LV vB, rB          //; load B vector
  ADDV.D vA, vB, vC  //; do addition
  SV vA, rA          //; store result
  ```
  ![](./media/computer_architecture/vector_scatter_gather_operations.png)
- **masked operations:** used if some elements should not be executed on based on a dynamically determined condition  
`VMASK` register is a bit mask determining which data element should not be acted upon, this is predicated execution (predicated on mask bit)
  ```cpp
  // C
  for (i = 0; i < N; i++)
  {
      if (A[i] != 0)
      {
          B[i] = A[i] * B[i];
      }
  }

  // vector ASM
  VLD V0 = A
  VLD V1 = B
  VMASK = (V0 != 0)
  VMUL V1 = V0 * V1
  VST B = V1
  ```
- **masked vector instructions implementations:**
  - **simple:** execute all N operations, turn off result writeback according to mask  
  no need to change pipeline but operated on values we don't need  
![](./media/computer_architecture/vector_masked_instruction_simple.png)
  - **density-time:** scan mask vector and only execute elements with non-zero masks  
![](./media/computer_architecture/vector_masked_instruction_density_time.png)
- **matrix storage format:**  
![](./media/computer_architecture/row_column_major.png)
  - **row major:** consecutive elements in a row are laid out consecutively in memory
  - **column major:** consecutive elements in a column are laid out consecutively in memory
- **stride with banking:** we can sustain 1 element/cycle throughput as long as stride & number of banks are co-primes (no common factors except 1) and there are enough banks to cover bank access latency
- **example: matrix multiply:** considering two matrices (`4 x 6`, `6 x 10`) stored in row major format  
assuming we have 10 banks, A0 memory accesses (stride 1) will be from different banks and B0 (stride 10) from same bank, so better data layout can help minimize bank conflicts, example: transpose matrix B to get stride 1  
![](./media/computer_architecture/matrix_multiplication_example.png)
- modern SIMD processors exploit data parallelism in both time & space  
![](./media/computer_architecture/time_space_duality_example.png)
- **vector unit structure:**  
![](./media/computer_architecture/vector_unit_structure.png)
- **vector instruction level parallelism:** overlap execution of multiple vector instructions  
example: machine has 32 elements per vector register and 8 lanes (so need 4 cycles to complete loading entire register), completes 24 operations/cycle when using all three functional codes  
![](./media/computer_architecture/vector_instruction_level_parallelism.png)
- *to program a vector machine, the compiler or hand coder must make the data structures in the code fit nearly exactly the regular structure built in to the hardware. that's hard to do in first place, and just as hard to change. one tweak, and the low-level code has to be rewritten by a very smart and dedicated programmer who knows the hardware and often the subtleties of the application area*  
**automatic code vectorization:** compile-time reordering of operation sequencing, this requires extensive loop dependence analysis  
![](./media/computer_architecture/auto_code_vectorization.png)

# fine-grained multithreading
- **fine-grained multithreading:** hardware has multiple thread contexts (`PC` + registers) and each cycle fetch-engine fetches from a different thread such that no two instructions from a thread are in the pipeline concurrently  
tolerates the control and data dependency latencies by overlapping the latency with useful work from other threads  
improves pipeline utilization by taking advantage of multiple threads  
improves thread-level throughput but sacrifices single thread performance (one instruction fetched every `N` cycles)  
needs extra logic for keeping thread contexts and does not overlap latency if not enough threads to cover the whole pipeline  
![](./media/computer_architecture/fine_grained_multithreading.png)  
![](./media/computer_architecture/fine_grained_multithreading_example.png)

# graphics processing units
- GPU instruction pipeline operates like a SIMD pipeline underneath, but the programming is done using threads (not SIMD instructions)
- **programming model:** how the programmer expresses the code, example: sequential (von Neumann), data parallel (SIMD), multi-threaded (MIMD)  
**execution model:** how the hardware executes the code underneath, example: OoO execution, vector processor, array processor  
execution model can be very different from the programming model, example: von Neumann model implemented by OoO processor
- **single program multiple data (SPMD):** programming model where each thread (processing element) executes the same procedure but on different data elements  
procedures can synchronize at certain points in program using barriers and each program can execute a different control-flow path at runtime  
single instruction multiple thread (SIMT) is Nvidia terminology for SPMD programs
- GPUs are programmed using threads (SPMD) with each thread having its own context, so they can be treated/restarted/executed independently  
**warp (wavefront):** dynamic grouping of threads that execute same instruction (same `PC`) on different data elements, is essentially a SIMD operation formed by hardware & is not exposed to the programmer  
warp is Nvidia terminology and wavefront AMD  
- **SIMD vs SIMT:** single sequential instruction stream of SIMD instructions vs multiple instruction streams of scalar operations  
**advantages of SIMT over SIMD:**
  - **treat each thread separately:** can execute each thread independently on any type of scalar pipeline (FGMT of warps)
  - **group threads into warp flexibly:** can group threads that are supposed to truly execute the same instruction (dynamic warp formation/merging)
- **GPU high-level view:** each scalar pipeline corresponds to one vector lane of an array processor  
![](./media/computer_architecture/gpu_high_level.png)
- **FGMT of warps:** warps can be interleaved on the same pipeline  
![](./media/computer_architecture/gpu_warp_fgmt.png)  
**latency hiding:** interleave warp execution to hide latencies by having one instruction per thread in the pipeline at a time (no HW interlocking), enables long latency tolerance (like cache miss or data load)  
![](./media/computer_architecture/gpu_latency_hiding.png)
- **warp instruction level parallelism:** with no data forwarding, for a given warp we cannot issue next instruction until previous load is done, so next instruction issue will be for a different warp  
![](./media/computer_architecture/warp_intruction_level_parallelism.png)
- **example: vector add:**
  ```cpp
  // C
  for (ii = 0; ii < 100000; ++ii)
  {
      C[ii] = A[ii] + B[ii];
  }

  // CUDA
  __global__ void KernelFunction(…)
  {
      int tid  = blockDim.x * blockIdx.x + threadIdx.x;
      int varA = aa[tid];
      int varB = bb[tid];
      C[tid]   = varA + varB;
  }
  ```
- **SIMD utilization:** fraction of SIMD lanes executing a useful
operation
- **control flow problem:** each thread can have conditional control flow instructions (& paths) but they need to have a common `PC`  
![](./media/computer_architecture/gpu_control_flow_paths.png)  
**branch divergence:** occurs when threads inside warps branch to different execution paths  
can be resolved using masked execution (similar to masked vector operations)  
![](./media/computer_architecture/gpu_control_flow_masked_execution.png)
- executing both paths for all warps reduces SIMD utilization, instead we can find individual threads that are at the same `PC` and group them together into a single warp dynamically, this reduces divergence and improves utilization  
**dynamic warp formation/merging:** dynamically merge threads executing the same instruction after branch divergence by forming new warps from warps that are waiting  
![](./media/computer_architecture/dynamic_warp_merging_1.png)  
enough threads branching to each path enables the creation of full new warps  
![](./media/computer_architecture/dynamic_warp_merging_2.png)
- **example: dynamic warp formation:**  
![](./media/computer_architecture/dynamic_warp_merging_example.png)

# memory organization
- most of the system is dedicated to storing & moving data, yet system is still bottlenecked by memory  
![](./media/computer_architecture/onchip_memory.png)  
important workloads (like AI/ML, genomics, data analytics) are all data intensive, they require rapid & efficient processing of large amounts of data  
we are generating much more data than we can process  
data movement takes order of magnitude more power than arithmetic operation  
![](./media/computer_architecture/memory_power.png)
- **memory abstraction:** physical memory size is much smaller than what the programmer assumes (infinite)  
system software along with hardware cooperatively ensure that this assumption holds by mapping virtual memory address to physical memory  
life is easier for the programmer but more complex system software and hardware architecture (programmer-architect tradeoff)  
a larger level of storage is needed to manage a small amount of physical memory (RAM) automatically, so physical memory has a backing store (disk)
- **ideal memory system:**  
![](./media/computer_architecture/ideal_memory_system.png)
- **memory storage types:**
  - **latches (flip-flops):** very fast & parallel access, very expensive (one bit costs tens of transistors)
  - **static RAM:** relatively fast but one data word access at a time, expensive (6+ transistors)
  - **dynamic RAM:** slower and one data word at a time, cheap (1 transistor & 1 capacitor)  
  but reading destroys content, needs special process for manufacturing (putting capacitor and logic together)
  - **other technologies:** like flash memory, hard disk & tape are much slower to access but non-volatile & very cheap (no transistors directly involved)
- **array organization of memories:** to efficiently store large amounts of data we need:
- **memory array:** store data  
  an `M` bit value can be read/written at each unique `N` bit address and the array will have `2^N` rows and `M` columns, all values can be accessed but only `M` bits at a time  
  example: two-bit address with three-bit data  
  ![](./media/computer_architecture/memory_array.png)
- **address selection logic:** select one row of data  
  storage nodes in one column connected to one bitline, address decoder activates only one wordline, content of one line of storage available at output  
  ![](./media/computer_architecture/memory_address_selection.png)
- **readout circuit:** reads data out  
  access transistors (configured as switches) connect the bit storage to the bitline, access controlled by the wordline  
  ![](./media/computer_architecture/memory_readout_circuit.png)
- a single monolithic large memory array takes too long to access and does not enable multiple accesses in parallel  
**memory interleaving (banking):** divide a large array into smaller arrays that can be accessed independently in same/consecutive cycles (overlapped access)  
example: DRAM interleaving: channel ⟶ rank ⟶ bank ⟶ subarrays ⟶ mats  
![](./media/computer_architecture/memory_interleaving.png)  
for a laptop, channel is a RAM stick, rank is collection of 8 chips (black die) on each side, each chip has 8 banks each  
if each bank gives 1 bit per cycle, total throughput is `8banks x 8chips x 2ranks x 2channels = 256bits or 32bytes`  
![](./media/computer_architecture/dram_stick.png)
- **dynamic random access memory (DRAM):** capacitor charge state indicates stored value  
but capacitor leaks through the RC path so DRAM cell needs to be refreshed frequently  
![](./media/computer_architecture/memory_dram_cell.png)
- **static random access memory (SRAM):** two cross coupled inverters store a single bit, feedback path enables the stored value to persist in the cell  
needs 4 transistors for storage and 2 for access, faster access since no capacitor present  
two bitlines will be complement of each other, if they are same then system will be assume there is a issue with that cell  
![](./media/computer_architecture/memory_sram_cell.png)
- **memory bank read access sequence:**  
![](./media/computer_architecture/memory_bank_access.png)
  - decode row address and drive wordlines
  - most-significant bits drive bitlines (read entire row)
  - amplify row data (capacitor charge)
  - decode column address and select subset of row to send to output
  - pre-charge bitlines for next access (like DRAM refresh)

# memory hierarchy
- ideal memory would have zero access time (latency), infinite capacity, zero cost and infinite bandwidth to support multiple accesses in parallel  
but practically these requirements oppose each other: bigger is slower (longer to determine the location), faster is more expensive (SRAM vs DRAM), higher bandwidth is more expensive (more banks, more ports, higher frequency)
- so both fast & large cannot be achieved with a single level of memory  
**memory hierarchy:** multiple levels of memory which gets progressively bigger & slower as the levels get farther from the processor while ensuring most of the data the processor needs is kept in the faster levels  
fundamental tradeoff is small fast memory vs large slow memory  
**last level cache (LLC):** farthest away cache  
![](./media/computer_architecture/memory_hierarchy.png)
- **locality of reference:** is the tendency of a program to access the same set of memory locations repetitively over a short period of time (like in loops)
  - **temporal:** reuse of specific data within a relatively small time duration, locality in time  
  to exploit: store recently accessed data (in fast memory) in anticipation that the data will be accessed again
  - **spatial:** use of data elements within relatively close storage locations, locality in space (like instruction fetch or traversing an array)  
  to exploit: divide memory into equal size blocks and store the recently accessed block in its entirety

# cache
- **cache:** any structure that memorizes frequently used/produced results to avoid repeating the long-latency operations required to reproduce/fetch the data from scratch, example: web cache  
in processor context it is an automatically managed memory structure based on SRAM that memorizes the most frequently accessed DRAM memory locations to avoid repeatedly paying for DRAM access latency  
- **caching in a pipelined design:** cache needs to be tightly integrated into the pipeline (ideally 1-cycle access to prevent stall)  
but cannot have a large cache in a high frequency pipeline due to longer cycle time (longer search time) so cache hierarchy is used which can be managed:
  - **manual:** programmer manages data movement across cache levels, too painful for programmers on substantial programs  
  example: on-chip scratchpad memory in embedded processors and shared memory in GPUs
  - **automatic:** hardware manages data movement across levels, programmer's life is easier since average programmer doesn't need to know about it  
  example: processor L1/L2/L3 caches
- **block/line:** unit of storage in the cache, memory is logically divided into cache blocks that map to potential locations in the cache
- on a reference:
  - **hit:** if data in cache, then use cached data instead of accessing memory
  - **miss:** if data not in cache, bring block into cache (if full then may have to evict some other block)
- **miss penalty:** time it takes to retrieve a block from lower level of hierarchy
- **cache design decisions:**
  - **placement:** where and how to place/find a block
  - **replacement:** what data to remove to make room
  - **granularity of management:** large or small blocks, maybe sub-blocks
  - **write policy:** what do we do about writes
  - **instruction/data:** do we treat them separately
- when address arrives to cache for read, in parallel address sent to:  
**tag store:** check if the address is present in the cache and returns hit/miss, also has some bookkeeping information for replacement/eviction  
**data store:** stores memory blocks, returns memory, discard data if tag store returns miss  
![](./media/computer_architecture/cache_tag_data_store.png)  
**cache hit rate:** `(num_hits) / (num_hits + num_misses) = (num_hits) / (num_accesses)`  
**average memory access time:** `(hit_rate x hit_latency) + (miss_rate x miss_latency)`  
 reducing these three parameters will increase cache performance: miss rate, miss latency/cost & hit latency/cost
- **cache addressing:** main memory is logically divided into fixed-size chunks (blocks)  
cache can only house limited number of blocks so each block address maps to a potential location in the cache determined by the index bits in the address, these are used to index into the tag & data stores  
![](./media/computer_architecture/cache_index_bits.png)  
- **cache access:**  
![](./media/computer_architecture/cache_access.png)
  - index into the tag and data stores with index bits in address
  - check valid bit in tag store and compare tag bits in address with stored tag in tag store
  - if the stored tag is valid and matches the tag of the block then it is a cache hit
  - block in data store valid, get the required word from block using mux
- **cache mapping:** how a certain block that is present in the main memory gets mapped to the memory of a cache in the case of any cache miss  
**associativity:** how many blocks can map to the same index, blocks that map to the same index are called set  
![](./media/computer_architecture/cache_associativity.png)
  - **direct mapped:** a given main memory block can be placed in only one possible cache location  
  if the location is previously taken up then the new block is loaded after evicting old block, so two blocks that map to the same index cannot be present in the cache at the same time so can cause conflict misses  
  example: can lead to 0% hit rate if same block accessed in interleaved manner
  - **fully associative:** a block can be placed in any cache location, don't have conflict misses instead has capacity misses
  - **k-way set associative:** a given main memory block can be placed in any of the `k` cache locations (`k`-way associative)  
  trade-off between direct-mapped cache (less complex) and fully associative cache (fewer misses)  
  direct mapped is an extreme case with `k==1`  
  diminishing returns for higher associativity as it will lead to higher hit rate but also slower cache access time (longer tag search) and more expensive hardware (more comparators)
- think of each block in set having a priority indicating how important it to keep the block in the cache then there are three key decisions within a set to determine/adjust block priorities:
  - **insertion:** what happens to priorities when a block is inserted into the set (cache fill)
  - **promotion:** what happens to priorities on a cache hit
  - **eviction/replacement:** what happens to priorities on a cache miss
- **working set:** whole set of data the executing application references within a time interval
- **eviction/replacement policy:** on a cache miss replace any invalid block first, if all blocks are valid then consult replacement policy
  - **first-in first-out (FIFO):** evict blocks in the order they were added
  - **least-recently used (LRU):** evict the least recently accessed block  
  so need to keep track of access ordering of blocks, but for a 4-way cache there are `4! == 24` possible orderings so we need 5 bits per set  
  so most modern processors don't implement true/perfect LRU in highly associative caches, instead:
    - **not most-recently used (nMRU):** keep track of only MRU, for replacement randomly choose one of the not-MRU blocks
    - **hierarchical LRU:** divide the k-way set into `m` groups and keep track of only the MRU group and MRU block within each group  
    on replacement select victim randomly from one of the not-MRU block in one of the not-MRU groups
    - **victim next-victim replacement:** only keep track of victim (MRU) and the next-victim (next MRU)
  - **random:** is better when set thrashing (program working set is larger than set associativity) occurs  
  example: 0% hit-rate with LRU for cyclic reference to A, B, C, D, E in a 4-way cache
  - **least-frequently used (LFU):** algorithm counts how often a block is needed, those used less often are discarded first
  - **least costly to re-fetch:** different memory accesses have different cost (latency) associated with it (L2 cache vs DRAM), those with lowest latencies are evicted first
  - **hybrid replacement policies:** in practice  performance of replacement policy depends on the workload (like LRU vs random for thrashing), so instead use a hybrid to get the best of both worlds
  - **Belady's optimal replacement policy:** replace the block that is going to be referenced furthest in the future by the program, cannot be implemented since this requires knowledge of the future
- when do we write the modified data in a cache to the next level:
  - **write-back:** when the block is evicted  
  can combine multiple writes to the same block before eviction saving bandwidth and energy  
  most modern caches use this  
  - **write-through:** at the time the write happens  
  simpler and makes sure all levels are up to date (cache-coherent) but bandwidth intensive (multiple writes)  
  useful when multiple processors share memory
- **dirty/modified bit:** is part of tag-store entry to indicate that data has been written (to cache) but memory has not been updated, required for write-back caches
- do we allocate a cache block on a write miss:
  - **allocate on write miss:** can combine writes instead of writing each of them individually to next level  
  simpler because write misses can be treated the same way as read misses  
  but requires transfer of the whole cache block, example: entire 64byte cache block needs to be written for a 1byte modification
  - **no-allocate:** conserves cache space if locality of writes is low (potentially improving cache read hit rate)
- **streaming writes:** processor writes to an entire block over a small amount of time (like `memset()`), allocating on streaming writes is not preferable here since it can pollute the cache with unnecessary data
- instead write to only a portion of the block (sub-block) to get the best of allocate on write miss & no-allocate  
**sub-blocked (sectored) caches:** divide a block into sub-blocks (sectors) each having a separate valid & dirty bits  
allocate only a sub-block (or a subset of sub-blocks) on a request  
no need to transfer the entire cache block from cache, a write simply validates and updates a sub-block  
more freedom in transferring sub-blocks into the cache, a cache block does not need to be in the cache fully  
but increased complexity and may not fully exploit spatial locality  
![](./media/computer_architecture/cache_sub_blocks.png)
- **instruction & data caches:**
  - **unified:** dynamic sharing of cache space (no static partitioning), but instructions & data can kick each other out (no guaranteed space for either)
  - **separate:** instruction and data are accessed in different places in the pipeline so first level caches are almost always split and higher level caches are almost always unified
- **multi-level caching in a pipelined design:**
  - **first level caches:** separate instruction and data caches, decisions very much affected by cycle time, small & lower associativity cache (latency is critical), tag store and data store accessed in parallel
  - **second level caches:** decisions need to balance hit rate and access latency, usually large and highly associative (latency not as important), tag store and data store accessed serially (to save energy since miss rate is higher)  
   second level doesn't see the same accesses as the first so first level acts as a filter (filtering some temporal and spatial locality)
- **cache inclusion policy:**
  - **inclusive:** a block in an lower level is always also included in higher levels to simplify cache coherence
  - **exclusive:** a block in an lower level will not be included in higher levels to better utilize space across entire hierarchy
  - **non-inclusive:** a block in an lower level may or may not be included in higher levels, relaxes design decisions
- **cache performance:** depends on:
  - **cache size:** total data (not including tag) capacity, bigger can exploit temporal locality better but too large of a cache can adversely affect latency (bigger is slower)  
  ![](./media/computer_architecture/cache_performance_cache_size.png)
  - **block size:** data that is associated with an address tag  
  too small blocks don't exploit spatial locality well and have larger tag overhead  
  too large blocks will lead to less total number of blocks so less temporal locality exploitation and waste of cache space (& bandwidth/energy) if spatial locality is not high  
  ![](./media/computer_architecture/cache_performance_block_size.png)
    - **critical word first:** large cache blocks can take a long time to fill into the cache, so fetch critical word first into the cache line and supply it to the processor then fill the cache line
    - **sub-blocking:** sub-blocks to help with higher bandwidth wastage for large cache blocks
  - **associativity:** larger associativity lowers miss rate (reduced conflicts) but higher hit latency & area cost, but diminishing returns on miss rate  
  smaller associativity lowers cost & hit latency (important for L1 caches)  
  ![](./media/computer_architecture/cache_performance_associativity.png)
- **cache miss classification:**
  - **compulsory:** first reference to an address (block) always results in a miss, prefetching can reduce misses by anticipating which blocks will be needed soon
  - **capacity:** cache is too small to hold everything needed  
  defined as the misses that would occur even with a fully-associative cache (with optimal replacement) of the same capacity
  - **conflict:** any miss that is neither a compulsory nor a capacity miss, increasing associativity can help reduce these misses
- **restructuring data access patterns:** software approaches for higher hit rate
  - **loop interchange:** exchanging the order of two iteration variables used by a nested loop to ensure that the data is accessed in the order in which they are present in memory  
  example: for a row major layout accessing consecutive elements help with spatial locality
    ```cpp
    // original
    for (int x = 0, x < width; x++)
        for (int y = 0, y < height; y++)
            sum += input[x * width + y];

    // improved
    for (int y = 0, y < height; y++)
        for (int x = 0, x < width; x++)
            sum += input[x * width + y];
    ```
  - **tiling:** divide the working set so that each piece fits in the cache, avoids cache conflicts between different chunks of computation  
  basically operate on smaller data (tiles) that fit fast memories (cache or shared memory)  
  example: in image convolution same memory locations access by neighboring threads, so divide the input into tiles that can be loaded in shared memory  
  ![](./media/computer_architecture/tiling.png)
  - **improved data packing:** separate rarely-accessed fields of a data structure and pack them into a separate data structure  
  example: in a linked-list, rarely accessed data occupy most of the cache line
    ```cpp
    // original
    typedef struct
    {
        // frequently accessed
        node_t *next;
        int key;
        // rarely accessed
        char[256] name;
        char[256] school;
    } node_t;

    while (node)
    {
        if (node->key == input_key)
        {
            // access other fields of node
        }
        node = node->next;
    }

    // improved
    typedef struct
    {
        // frequently accessed
        node_t *next;
        int key;
        // rarely accessed
        node_data_t *node_data;
    } node_t;

    typedef struct
    {
        char[256] name;
        char[256] school;
    } node_data_t;

    while (node)
    {
        if (node->key == input - key)
        {
            // access node->node_data
        }
        node = node->next;
    }
    ```
- **memory level parallelism:** generating & servicing multiple memory accesses in parallel  
eliminating an isolated miss helps performance more than eliminating a parallel miss  
eliminating a higher-latency miss could help performance more than eliminating a lower-latency miss
![](./media/computer_architecture/memory_level_parallelism.png)  
![](./media/computer_architecture/memory_level_parallelism_example.png)
- **false sharing:** when a core attempts to periodically access data that is not being altered but it shares a cache block with data that is being altered then caching protocol may force the first participant to reload the whole cache block despite a lack of logical necessity  
example: if two variables share a cache line then unmodified variable read will be as expensive as modified variable read if there's an intervening write to the other variable since cache line needs to be invalidated then fetched from main memory again

## multi core caches
- cache efficiency becomes even more important in a multi-core/threaded systems since memory bandwidth is at premium & cache space is a limited resource across cores/threads
- **private cache:** cache belongs to one core, a shared data blocks needs to be brought into respective caches (redundant transfer)  
**shared cache:** cache is shared by multiple cores  
improves utilization since a idle resource can be used by another thread  
no fragmentation due to static partitioning  
easier to maintain coherence  
reduces communication latency by storing shared data in same cache  
easier to maintain coherence between cores  
but can lead to contention for resources between threads leading to performance degradation  
inconsistent performance across runs since performance depends on co-executing threads  
slower access since cache not tightly coupled with the core  
![](./media/computer_architecture/cache_shared_vs_private.png)
- **cache coherence:** refers to the consistency and synchronization of data stored in different caches within a multi-core system  
**simple coherence implementation:** all caches will observe each other's write/read operations, if a processor writes to a block then others will invalidate that block in their respective caches

# prefetching
- **prefetching:** fetch the data before it is needed by the program  
if data can be prefetched accurately & early enough then (high) memory latency can be reduced/eliminated  
can eliminate compulsory cache misses (only option other than very large cache blocks)  
prefetching involves predicting which address will be needed in the future, mis-predicted data is simply not used so no need for state recovery like branch prediction but can lead to side channels like meltdown & spectre
- **example: HW prefetcher in memory system:**  
![](./media/computer_architecture/prefetch_memory_system.png)
- **prefetching challenges:**
  - **what:** prefetching useless data wastes resources (memory bandwidth, cache/prefetch buffer space, energy consumption) so accurate prediction of addresses is important  
  predict based on past access pattern in HW or compiler's/programmer's knowledge of data structures SW
  - **when:** if data prefetched too early then it might not be used before it is evicted  
  if prefetched too late it might not hide the entire memory latency
  in HW prefetcher try to stay far ahead of the processor's demand access stream  
  in SW move the prefetch instructions earlier in the code
  - **where:** prefetcher will see different access patterns based on where it is placed  
  example: at L1 it sees all L1 hits & misses, at L2 level it only sees L1 misses and at L3 level it only sees L2 misses  
  so having the prefetcher closer to processor leads to better accuracy & coverage but prefetcher needs to examine more requests
  - **how:** how & who does the prefetching
    - **software:** programmer/compiler insert ISA provided prefetch instructions (extra effort), usually works well for regular access patterns
    - **hardware:** specialized hardware monitors memory accesses (auto address generation)  
    memorizes, finds & learns address strides, patterns & correlation
    - **execution-based:** a special thread execute to prefetch data for the main program, can be generated by either SW/programmer or HW
- **example: IBM POWER4 streaming prefetcher:** when load instruction miss sequential cache lines (ascending or descending) the prefetch engine initiates access to the following cache lines before being referenced by load instructions  
![](./media/computer_architecture/streaming_prefetcher.png)
- **stride prefetcher:** record the stride between consecutive memory accesses, if stable use it to predict future memory accesses  
stride can be determined on a per-instruction (hash `PC`) basis or per-memory-region (hash cache block) basis  
stream prefetching is a special case of  per-memory-region prefetching with stride 1
memory-region based stride prefetching where N = 1
- **prefetcher performance:**
  - **accuracy:** `used_prefetches / sent_prefetches`
  - **coverage:** `prefetched_misses / all_prefetches`
  - **timeliness:** `on_time_prefetches / used_prefetches`
  - **bandwidth consumption:** bandwidth consumed with/without prefetcher, can utilize idle bus bandwidth if available
  - **cache pollution:** extra load demand misses due to prefetch placement in cache

## runahead execution
- long latency cache misses are responsible for most OoO execution full-window stalls so large instruction windows are required to fully tolerate memory latency  
but this conflicts with lower energy consumption (tag matching, load/store buffers), shorter cycle time (wakeup/select, regfile & bypass latencies) and lower DV (design & verification) complexity
![](./media/computer_architecture/full_window_stall.png)
- **runahead execution:** technique to obtain the memory-level parallelism benefits of a large instruction window  
![](./media/computer_architecture/runahead_execution.png)
  - when the oldest instruction is a long-latency cache miss, checkpoint architectural state and enter runahead mode
  - in runahead mode processor speculatively pre-execute instructions with sole purpose of prefetching, instructions dependent on long-latency cache miss are ignored & dropped
  - when the original miss returns restore the checkpoint, flush pipeline and resume normal execution
  - architecturally nothing has happened but hopefully micro-architecturally lot of useful data has been prefetched and subsequent cache misses can be avoided
- very accurate prefetches since it follows the program path  
simple to implement since most of the hardware is already present  
but prefetch distance limited by memory latency