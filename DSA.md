# DSA
- [Introduction](#introduction)
- [Big-O](#big-o)
- [Arrays](#arrays)
- [Hash Tables](#hash-tables)

## Links <!-- omit from toc -->
- [William Fiset Data Structures (Playlist)](https://www.youtube.com/playlist?list=PLDV1Zeh2NRsB6SWUrDFW2RmDotAfPbeHu)
- [Big-O Cheatsheet](https://www.bigocheatsheet.com/)
- [Why `log(n)`](https://www.youtube.com/watch?v=Xe9aq1WLpjU)

## To Do <!-- omit from toc -->
- Bloom Filter

## Introduction
- **Data Structures:** way of organizing data so that it can be used effectively
- **Abstract Data Type:**
  - provides only the interface to which a data structure must adhere to
  - *example:* queue abstraction can be implemented using LL, array or stack

## Big-O
- **Big-O/Asympotic Notation:**
  - upper bound of complexity (time & space) in the worst case
  - helps quantify performance as the input size becomes arbitrarily large (*i.e.* growth rate of complexity)
  - *example:* if running time given by `f(n) = 7*log(n)^3 + 15*n^2 + 2*n^3 + 8`, then `O(f(n)) = O(n^3)`
  - ![](./Media/Big_O_Complexity.png)
- **Logarithm:**
  - `ceil(log(n))` represe nts the minimum number of bits to uniquely identify a number
  - each step in search algo is essentially resolving 1bit of target's index, *i.e.*`O(log(n))`
  - each step in comparison sort algo is finding a correct index for each element in remaining positions  
    `log(n) + log(n-1) + ... + log(1)` = `O(log(n)) + O(log(n)) + ...` = `O(n*log(n))`
- ***Examples*:**
  - `f(n) = n/3` = `O(n)`
    ```cpp
    i = 0;
    while (i < n) {
      i = i + 3;
    }
    ```
  - inner loop executes `n`, `(n-1)` ... `1` times as `i` increases  
    total (*i.e.* sum of natural numbers) is `n*(n+1)/2` = `O(n^2)`
    ```cpp
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
    ```
  - size halves every iteration `O(log(n))`
    ```cpp
    low = 0;
    high = n - 1;
    while (low <= high) {
      mid = (low + high) / 2;
      if (array[mid] == key)
        return mid;
      else if (array[mid] < value)
        low = mid + 1;
      else if (array[mid] > value)
        high = mid - 1;
    }
    return -1; // not found
    ```

## Arrays
- **Static Array:** fixed (compile-time) length container indexable for the range `[0, n-1]`
- **Dynamic Array:** can resize itself during runtime, resizing requires copying over existing elements
- **Dynamic Array Implementation:**
  - static array with initial size (capacity)
  - keep adding elements keeping tracking of size
  - when size == capacity, create new static array of double the capacity, copy elements over

## Hash Tables
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
      | linear probing             | `P(i) = i`, sequential search for `i`th iteration     |
      | quadratic probing          | `P(i) = i^2`, search further & further away           |
      | double hashing             | `P(k, i) = i * H2(k)`, `H2()` secondary hash function |
      | pseuo-random num generator | `P(k, i) = RNG(H(k))[i]`, `RNG` seeded with `H(k)`    |
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