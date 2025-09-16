# Algorithms
- [Asymptotic Notation](#asymptotic-notation)

## Schedule <!-- omit from toc -->
- [Theory (Skiena)](https://www3.cs.stonybrook.edu/~skiena/373/videos/)
  - sort implementation in C++ STL
- [Practice (NeetCode150)](https://neetcode.io/practice?tab=neetcode150)
- **Method:** ([reddit](https://www.reddit.com/r/cscareerquestions/comments/ot9ssf/comment/h6tx1vx/?utm_source=share&utm_medium=mweb3x&utm_name=mweb3xcss&utm_term=1&utm_content=share_button), [medium](https://medium.com/@rajbopche/my-preparation-for-algo-ds-193c90952d8c))
  - if no progress within first 10min then mark it (for review later), watch video solution & then code it yourself
  - short notes for each problem:
    - approach with pseducode in short
    - new trick/pattern involved
    - time & space complexity
  - give yourself time to forget and retry marked problems after 2 weeks
  - goal is to understand the problem not memorize solution
    - if you can't solve new problems then you are memorizing solutions
  - first time will take multiple months but getting back into it next time will just take weeks

## Asymptotic Notation
- **RAM Model of Computation:**
  - to study algorithms in a machine/language independent way
  - each simple operations (`+`, `-`, `=`, `if`, `call`) takes 1 step
  - loops & subroutine calls are not simple operations
    - depend upon size of data and loop/subroutine contents
  - each memory access takes exactly 1 step
  - run time of algorithm measured by counting number of steps
- **Worst-Case Complexity:**
  - maximum steps taken by algorithm on any instance of size n
  - worst-case preferred measure of algorithm efficiency
  - but randomized algorithms require average-case to show off their merits
  - ```mermaid
    ---
    config:
      themeVariables:
        xyChart:
          plotColorPalette: '#FF0000, #000000, #00FF00'
    ---
    xychart-beta
    title "worst, average & best case"
      x-axis "problem size" 1 --> 5
      y-axis "number of steps"
      line [2, 6, 10, 20, 40]
      line [2, 4, 8, 16, 32]
      line [2, 3, 6, 14, 28]
    ```
- **Big-O (Asymptomatic) Notation:**
  - modelling exact worst, average & best case is difficult
  - `g(n) = O(f(n))` means `C * f(n)` upper bound of `g(n)`
  - `g(n) = Ω(f(n))` means `C * f(n)` lower bound of `g(n)`
  - `g(n) = θ(f(n))` means `C1 * f(n)` upper bound and `C2 * f(n)` lower bound
  - notations only hold beyond a constant `n0`, don't care about small values of n
  - ```mermaid
    ---
    config:
      themeVariables:
        xyChart:
          plotColorPalette: '#FF0000, #000000, #00FF00'
    ---
    xychart-beta
    title "g(n) = θ(f(n)) holds beyond n == 3"
      x-axis "problem size" 1 --> 10
      y-axis "number of steps"
      line [4, 6, 7, 8, 10, 12, 15, 17, 20, 25]
      line [7, 2, 5, 6, 8, 10, 12, 15, 17, 20]
      line [2, 3, 3.5, 4, 5, 6, 7.5, 8.5, 10, 12.5]
    ```