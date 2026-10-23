# Array
- [Arrays](#arrays)
- [Hash Table](#hash-table)
- [TODO (AI)](#todo-ai)

## Arrays
- **Static Array:** fixed (compile-time) length sequential container indexable for the range `[0, n-1]`
- **Dynamic Array:** can resize itself during runtime, resizing requires copying over existing elements
- **Geometric Resizing:**
  - dynamic array underneath is a static array, keeping tracking of size while inserting/removing 
  - when `size == capacity`, create new static array of double the capacity, copy elements over
- **Complexities:**
  |           | Static | Dynamic |
  | --------- | ------ | ------- |
  | Access    | `O(1)` | `O(1)`  |
  | Search    | `O(n)` | `O(n)`  |
  | Insertion | NA     | `O(n)`  |
  | Appending | NA     | `O(1)`  |
  | Deletion  | NA     | `O(n)`  |

## Hash Table
- **Hash Table:** provides a mapping from keys to values using a technique called hashing
- **Hash Function:**
  - maps a key `x` to a whole number, which is used as index
  - 
    |                |                               |
    | -------------- | ----------------------------- |
    | `H(x) == H(y)` | `x` & `y` might be equal      |
    | `H(x) != H(y)` | `x` & `y` certainly not equal |
  - should be deterministic, *i.e.* same index for same key every time
  - should be uniform to minimize hash collisions
  - to be hashable key type should be immutable  
    *example:* lists/set can change in-place, rendering original index unreachable
- **Load Factor:** represents ratio of current size to total capacity of a hash table
- **Re-Hashing:** to maintain `O(1)` lookup, resize table (double *i.e.* exponential) and rehash keys once load factor hits a threshold
- **Hash Collisions:**
  - same hash value generated for two distinct keys
  - **Separate Chaining:**
    - each hash table bucket is a container that can hold multiple collided keys
    - collided keys appended to the container (usually LL)
    - `O(1 + a)`, where `a` is average LL length, as load factor grows `a ≈ n`, *i.e.* `O(n)`
  - **Open Addressing:**
    - search next available slot within the hash table array
    - next slot by offsetting current position to probing sequence function
    - 
      |                            |                                                       |
      | -------------------------- | ----------------------------------------------------- |
      | Linear Probing             | `P(i) = i`, sequential search for `i`th iteration     |
      | Quadratic Probing          | `P(i) = i^2`, search further & further away           |
      | Double Hashing             | `P(k, i) = i * H2(k)`, `H2()` secondary hash function |
      | Pseuo-Random Num Generator | `P(k, i) = RNG(H(k))[i]`, `RNG` seeded with `H(k)`    |
    - since probing sequence output used as offset, it should be non-zero
    - **Cycling:**
      - probing function hits same subset of indices repeatedly without checking every slot
      - instead use probing function that produce cycle of exactly table length
      - ![](./Media/Hash_Map_Probing_Cycling.png)
    - **Clustering:**
      - tendency for occupied slots to bunch together in contiguous groups
      - high load factor (~0.8) leads to high clustering, leading to higher search times
      - but linear probing can scan much faster (even at high load factors) due to high cache spatial locality
    - **Tombstones (Removing Element):**
      - elements searched till `NULL` encountered
      - replacing removed element with `NULL` leads to premature search stop
      - instead place unique tomstone marker that is skipped during search
      - tombstones increase load factor, so removed by resize or overwritten by insert
      - lazy relocation (optimization) moves a found key to the first encountered tombstone to shorten probe path for future lookups

## TODO (AI)
- Growth Factor Math (1.5 × vs. 2 ×): Why MSVC STL uses 1.5 × (allows allocator to reuse previously freed contiguous memory blocks) whereas GCC/Clang uses 2 × (faster growth, but can never reuse previous blocks).
- Amortized Analysis Proof: The Aggregate / Accounting method proving why geometric expansion is O(1) amortized, while fixed incremental growth (+K) degrades to O(n²).
- Memory Layout & Strides: Row-major vs. column-major indexing offset formulas (index = i · C + j) and cache-line misses during stride iteration.
- Circular Buffer (Ring Array): Array-backed fixed-capacity queue using head/tail modulo arithmetic ((tail + 1) % capacity).