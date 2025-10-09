# C++ <!-- omit from toc -->
- [Standard Template Library](#standard-template-library)
  - [Containers](#containers)
    - [Interface](#interface)
    - [Sequence Containers](#sequence-containers)
  - [Iterators](#iterators)
- [Doubts](#doubts)

# Links <!-- omit from toc -->
- [STL Containers (CPP Con)](https://www.youtube.com/watch?v=ZMUKa2kWtTk)

# Standard Template Library

- **Containers:** essentially data structures that stores templated elements  
  **Algorithms:** functions that operate on elements stored in containers using iterator-range  
  **Iterators:** general way to access elements in containers
  ```mermaid
  graph LR
    e0[Element 0]
    e1[Element 1]
    en[Element n]

    algo[Algorithm]

    range[Iterator Range]

    subgraph Container
    e0 --> e1
    e1 -.-> en
    end

    e0 -.start.-> range
    en -.end.-> range
    range --> algo
  ```
## Containers
- **Sequence Containers:** elements stored linearly with position dictated by user
- **Associative Containers:** elements stored in a way that allows fast look-up
    - can be ordered (sorted) or unordered (hashed)

### Interface
- **Constructors:**
  |          |                                              |
  | -------- | -------------------------------------------- |
  | default  | `std::vector<int> vec`                       |
  | count    | `std::vector<int> vec(size)`                 |
  | range    | `std::vector<int> vec(vec2.begin, vec2.end)` |
  | copy     | `std::vector<int> vec(vec2)`                 |
  | move     | `std::vector<int> vec(std::move(vec2)`       |
  | sequence | `std::vector<int> vec{1, 2, 3, 4, 5}`        |
- **Removing Elements:**
  |                              |                                                    |
  | ---------------------------- | -------------------------------------------------- |
  | clear all elements           | `vec.clear()`                                      |
  | erase element in position    | `vec.erase(itr)`                                   |
  | erase all elements of value  | `std::erase(vec, 5)`                               |
  | erase if predicate satisfied | `std::erase_if(vec, [](auto i) { return i >= 3 })` |
- **Size:**
  |                    |                  |
  | ------------------ | ---------------- |
  | empty?             | `vec.empty()`    |
  | number of elements | `vec.size()`     |
  | capacity           | `vec.capacity()` |
- **Assignment & Swap:**
  |                   |                         |
  | ----------------- | ----------------------- |
  | copy assign       | `vec = vec2`            |
  | move assign       | `vec = std::move(vec2)` |
  | initialize assign | `vec = {1, 2, 3, 4, 5}` |
  | swap API          | `vec.swap(vec2)`        |
  | swap Algorithm    | `std::swap(vec, vec2)`  |
- **Comparison:** first size compared, then elements compared one-by-one
  - all containers support `==` & `!=`
  - onlysequence & ordered containers support `<`, `<=`, `>` & `>=`
    - first mismatched element comparison determines result
- **Range-Based Loop:**
  ```cpp
  for (const auto i : vec) {
      std::cout << i << " ";
  }
  ```

### Sequence Containers
- **Overview:**
  |                       | array              | vector               | deque                   | list                   | forward_list     |
  | --------------------- | ------------------ | -------------------- | ----------------------- | ---------------------- | ---------------- |
  | size                  | static             | dynamic              | dynamic                 | dynamic                | dynamic          |
  | implementation        | static array       | dynamic array        | sequence of arrays      | doubly-LL              | singly-LL        |
  | access                | random             | random               | random                  | forward & backward     | forward          |
  | optimized for         |                    | end `O(1)`           | begin & end `O(1)`      | begin & end `O(1)`     | begin `O(1)`     |
  | memory reserve        |                    | yes                  | no (not useful)         | no                     | no               |
  | memory release        |                    | `shrink_to_fit()`    | `shrink_to_fit()`       | always                 | always           |
  | iterator invalidation |                    | yes                  | yes                     | no                     | no               |
  | strength              | stack, no overhead | 95% solution         | insert/delete begin/end | insert/delete anywhere | no overhead      |
  | weakness              | fixed size         | `O(n)` insert/delete | `O(n)` insert/delete    | no random access       | no random access |
- **Aggregate Initialization:**
  ```cpp
  std::array<int, 10> arr          // elements not initialized
  std::array<int, 10> arr{}        // elements default initialized
  std::array<int, 10> arr{1, 2, 3} // remaining elements default initialized
  ```
- **Special Elements:**
    ```cpp
    vec.front() // first element
    vec.back()  // last element
    ```
- **Index Access:**
  ```cpp
  vec[i]    // bounds not checked
  vec.at(i) // bounds checked
  ```
- **Insert vs Emplace:**
  - temporary object created then copy/move into container
    ```cpp
    vec.insert(pos_itr, initializer_list) // insert at position
    vec.push_back(initializer_list)       // insert at back
    ```
  - object ctor in container memory, more performant if move ctor inefficient
    ```cpp
    vec.emplace(pos_itr, initializer_list)      // similar to insert
    vec.emplace_back(pos_itr, initializer_list) // similar to push_back
    ```
- **List Special Functions:** optimized for pointer manipulation
  - ```cpp
    lst.sort()                                                   // sort elements
    lst.merge(another_lst)                                       // merge sorted lists
    lst.unique()                                                 // remove consecutive duplicate elements
    lst.reverse()                                                // reverse order of elements
    lst.splice(another_lst_itr, another_lst, start_itr, end_itr) // move elements between iterator range
    ```
  - `forward_list` only stores pointer to next element, so only next can be modified
    ```cpp
    fwd_lst.erase_after(itr)                                       // similar to erase
    fwd_lst.insert_after(itr, val)                                 // similar to insert
    splice_after(another_lst_itr, another_lst, start_itr, end_itr) // similar to splice
    ```
- **Special Notes:**
  - `std::string` is just `std::vector<char>` with special operations like `+=`
  - `deque` comes from **d**ouble **e**nded **que**ue
  - `deque` doesn't need data relocation when resized, so no memory reservation
  - `forward_list` doesn't know its size, instead use `std::distance(f_list.begin(), f_list.end())`
  - all search `O(n)` but costant factor high for list due to low spatial locality

## Iterators
- `adv_itr = std::next(itr, val)` advance iterator specific number of positions

# Doubts
- C-style arrays decay to pointer when passed to function
- when to use curly brace initializer & when to use parantheses?
  ```cpp
  std::string str("hello world");
  std::array<uint32_t, 3> arr{1, 2, 3};
  ```
- all containers table with `O()` for common operations & when to use
  - in Algorithms?