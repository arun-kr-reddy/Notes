## Leetcode
- [Leetcode](#leetcode)
- [Array \& Hash Map](#array--hash-map)
  - [Contains Duplicate (E 217)](#contains-duplicate-e-217)
  - [Valid Anagram (E 242)](#valid-anagram-e-242)
  - [Two Sum (E 1)](#two-sum-e-1)

## Links <!-- omit from toc -->
- [Neetcode Roadmap](https://neetcode.io/roadmap)
- [Leetcode Progress](https://leetcode.com/progress/)

## To Do <!-- omit from toc -->

## Plan <!-- omit from toc -->
- 
  | Week | Topics                                  | #   |
  | ---- | --------------------------------------- | --- |
  | 1    | Arrays & Hashing → Two Pointers → Stack | 12  |
  | 2    | Sliding Window, Binary Search, LL       | 12  |
  | 3    | Trees → Tries                           | 14  |
  | 4    | Backtracking → Heap → Graphs            | 10  |
  | 5    | 1D DP → 2D DP → Advanced Graphs         | 12  |
  | 6    | Intervals, Greedy, Bit Manip, Math      | 15  |

## Array & Hash Map

### Contains Duplicate (E 217)
- `bool containsDuplicate(vector<int>& nums)`
- given integer array `nums`, return true if any value appreads at-least twice
- `O(n)` time & `O(n)` space  
  using sort then linear scan `O(n*logn + n)` time, `O(1)` space
  ```cpp
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> prevNumMap;
    prevNumMap.reserve(nums.size());

    for (const int &val : nums) {
      if (prevNumMap.contains(val))
        return true;
      else
        prevNumMap.insert(val);
    }

    return false;
  }
  ```

### Valid Anagram (E 242)
- `bool isAnagram(string s, string t)`
- given two strings `s` &  `t`, return true if they are anagrams (must use all letters and with same frequency)
- `O(n)` time, `O(k)` space (`k == 26` alphabets)  
  ```cpp
  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false;

    unordered_map<char, size_t> charFreq;
    for (const char &c : s)
      charFreq[c]++;

    for (const char &c : t) {
      if (!charFreq.contains(c))
        return false;

      charFreq[c]--;
      if (charFreq[c] == 0)
        charFreq.erase(c);
    }

    return true;
  }
  ```
- **note:** using array of 26 counters same `O()` but practically much faster
  ```cpp
  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false;

    std::array<int, 26> freqCount = {0};
    for (const char &c : s) {
      freqCount[c - 'a']++;
    }

    for (const char &c : t) {
      if (freqCount[c - 'a'] == 0) {
        return false;
      }

      freqCount[c - 'a']--;
    }

    return true;
  }
  ```

### Two Sum (E 1)
- `vector<int> twoSum(vector<int> &nums, int target)`
- given integer array and target, return indices of the two numbers such that they add up to target
- `O(n)` time, `O(n)` space
  ```cpp
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> prevNums;

    for (int i = 0; i < nums.size(); i++) {
      const int required = target - nums[i];
      if (prevNums.contains(required)) {
        return {prevNums[required], i};
      }

      prevNums[nums[i]] = i;
    }

    return {};
  }
  ```