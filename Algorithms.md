# Algorithms <!-- omit from toc -->
- [Asymptotic Notation](#asymptotic-notation)

# Links <!-- omit from toc -->


# Asymptotic Notation
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
  - `g(n) = θ(f(n))` means `C1 * f(n)` upper bound & `C2 * f(n)` lower bound
  - notations only hold beyond a constant `n0`, we don't care about small values of n
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
- **Asymptotic Dominance:**
  - function with higher growth rate eventually becomes much larger for very large input sizes
  - `f(n)` dominates `g(n)` if $\lim_{n\to\infty} g(n) / f(n) = 0$
  - example:
    | `n` | `lg(n)`  | `n`     | `n*lg(n)` | `n^2`  | `2^n`    | `n!`            |
    | --- | -------- | ------- | --------- | ------ | -------- | --------------- |
    | 10  | 0.003 µs | 0.01 µs | 0.033 µs  | 0.1 µs | 1 µs     | 3.63 ms         |
    | 20  | 0.004 µs | 0.02 µs | 0.086 µs  | 0.4 µs | 1 ms     | 77.1 years      |
    | 30  | 0.005 µs | 0.03 µs | 0.147 µs  | 0.9 µs | 1 sec    | 8.4 × 10^15 yrs |
    | 40  | 0.005 µs | 0.04 µs | 0.213 µs  | 1.6 µs | 18.3 min |                 |
    | 50  | 0.006 µs | 0.05 µs | 0.282 µs  | 2.5 µs | 13 days  |                 |

[Continue](https://www.youtube.com/watch?v=9RrdOssuOY4&list=PLOtl7M3yp-DX6ic0HGT0PUX_wiNmkWkXx&t=4040s)