# Standard Template Library
- **Containers:**
  - essentially data structures that stores templated elements
- **Algorithms:**
  - functions that operate on elements stored in containers using iterator-range
- **Iterators:**
  - general way to access elements in containers
- 
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
- **Sequence Containers:**
  - element position dictated by user
- **Associative Containers:**
  - elements stored in a way that allows fast look-up (sorted or hashed)

### String
- basically `basic_string<char>`
  - also supports other element sizes (for unicodes)
- 
  ```cpp
  #include <string>
  std::string str;

  str = another_str;                // copy assign
  char c = str.at(i);               // get element (with bounds checking)
  str += another_str;               // append operator
  str.erase(itr);                   // remove element
  str.push_back(val);               // add element at the end, pop_back()

  size_t size = str.size();         // num elements (excluding NULL)
  size_t capacity = str.capacity(); // max num elements (+ 1) possible in allocated mem
  str.reserve(size);                // reserve memory
  str.shrink_to_fit();              // dealloc unused memory
  str.clear();                      // clear string

  char *data = str.data();          // underlying C array (NULL terminated)
  if (str.find(substr) != str.npos) // index of first substring occurence
  str.swap(another_str);            // swap string contents
  ```

### Array
- fixed-size contiguous array on stack
- commonly used APIs like `size()`, `at()`, etc are `constexpr`
- 
  ```cpp
  #include <array>
  std::array<T, SIZE_MAX> arr;

  arr.fill(value); // assign value to all elements

  // =, at, size, clear, data, swap
  ```

### Vector
- dynamic-size contiguous array on heap
- 
  ```cpp
  #include <vector>
  std::vector<T> vector;

  auto val_itr = insert(itr, val); // insert element

  // =, at, erase, push_back, size, capacity, reserve, shrink_to_fit, clear, data, swap
  ```

### List
- doubly-linked list
- ```cpp
  #include <list>
  std::list<T> lst;

  lst.push_front(val);                                          // add element at the start, pop_front()

  lst.sort();                                                   // sort elements
  lst.merge(another_lst);                                       // merge sorted lists
  lst.unique();                                                 // remove consecutive duplicate elements
  lst.reverse();                                                // reverse order of elements
  lst.splice(another_lst_itr, another_lst, start_itr, end_itr); // move elements between iterator range

  // =, erase, push_back, insert, size, clear, swap

  // no random access, so no at()
  // each node allocates its own memory, so no capacity related functions
  ```

### Forward List
- singly-linked list
- ```cpp
  #include <forward_list>
  std::forward_list<T> fwd_lst;

  fwd_lst.before_begin(); // special itr to element before beginning (useful for insert at start)

  fwd_lst.erase_after(itr);                                       // similar to erase
  fwd_lst.insert_after(itr, val);                                 // similar to insert
  splice_after(another_lst_itr, another_lst, start_itr, end_itr); // similar to splice

  // =, push_front (no push_back), clear, swap, sort, merge, unique, reverse

  // use std::distance to get size
  ```


## Iterators
- `adv_itr = std::next(itr, val)` advance iterator specific number of positions

# Doubts
- C-style arrays decay to pointer when passed to function
- when to use curly brace initializer & when to use parantheses?
  ```cpp
  std::string str("hello world");
  std::array<uint32_t, 3> arr{1, 2, 3};
  ```
- `insert`/`push_back` vs `emplace`/`emplace_back`:
  - constructs temporary object then copy/move it  
  - constructs object in place with ctor arguments, more performant for types with inefficient move ctor
- list `O(n)` search but low spatial locality so slower than vector
- all containers table with `O()` for common operations & when to use
  - in Algorithms?