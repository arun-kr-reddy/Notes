# Algorithms <!-- omit from toc -->
- [Asymptotic Notation](#asymptotic-notation)
- [Misc](#misc)

# Links <!-- omit from toc -->
- [Analysis of Algorithms (Lectures)](https://www3.cs.stonybrook.edu/~skiena/373/videos/)

# Asymptotic Notation
- **RAM Model of Computation:**
  - machine/language independent model for analyzing algorithms by counting number of steps
  - each simple operation (`+`, `-`, `=`, `if`, `call`) and memory access takes one step
  - cost of loops & subroutines depends on number of iterations & contents
- **Worst-Case Complexity:**
  - maximum steps taken by algorithm on any instance of size `n`
  - worst-case preferred measure of algorithm efficiency
  - but randomized algorithms require average-case to show off their merits
- **Big-O (Asymptomatic) Notation:**
  - modelling exact worst, average & best case is difficult
  - `g(n) = O(f(n))` means `C * f(n)` upper bound of `g(n)`
  - `g(n) = Ω(f(n))` means `C * f(n)` lower bound of `g(n)`
  - `g(n) = θ(f(n))` means `C1 * f(n)` upper bound & `C2 * f(n)` lower bound
  - notations only hold beyond a constant `n0`, we don't care about small values of `n`
  - ```mermaid
    ---
    config:
      themeVariables:
        xyChart:
          plotColorPalette: '#FF0000, #000000, #00FF00'
    ---
    xychart-beta
      title "g(n) = θ(f(n)) holds beyond n = 3"
      x-axis "problem size" 1 --> 10
      y-axis "number of steps"
      line [4, 6, 7, 8, 10, 12, 15, 17, 20, 25]
      line [7, 2, 5, 6, 8, 10, 12, 15, 17, 20]
      line [2, 3, 3.5, 4, 5, 6, 7.5, 8.5, 10, 12.5]
    ```
- **Asymptotic Dominance:**
  - function with higher growth rate eventually becomes much larger, even if other function starts out larger
  - `n!` >> `2^n` >> `n^3` >> `n^2` >> `nlogn` >> `n` >> `logn` >> `1`
- **Logarithm:**
  - number of steps it takes to double `1` repeatedly to reach `n`
  - number of times you can halve `n` to get down to `1`
  - **Base Asymptotically Unimportant:**
    - `log2(n)` --> `log100(n) / log100(2)` --> `O(logn)`

# Misc
- **Proof by Contradiction:**
  - assume statement's opposite is true, then prove assumption leads to logical impossibility (contradiction), thereby proving original statement as true