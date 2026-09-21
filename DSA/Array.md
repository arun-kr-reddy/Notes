# Array
- [Arrays](#arrays)
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

## TODO (AI)
- Growth Factor Math (1.5 × vs. 2 ×): Why MSVC STL uses 1.5 × (allows allocator to reuse previously freed contiguous memory blocks) whereas GCC/Clang uses 2 × (faster growth, but can never reuse previous blocks).
- Amortized Analysis Proof: The Aggregate / Accounting method proving why geometric expansion is O(1) amortized, while fixed incremental growth (+K) degrades to O(n²).
- Memory Layout & Strides: Row-major vs. column-major indexing offset formulas (index = i · C + j) and cache-line misses during stride iteration.
- Circular Buffer (Ring Array): Array-backed fixed-capacity queue using head/tail modulo arithmetic ((tail + 1) % capacity).