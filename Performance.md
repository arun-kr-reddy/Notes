# Performance <!-- omit from toc -->
- [Introduction](#introduction)

# Links <!-- omit from toc -->
- [Parallel Computing (Lectures)](https://www.youtube.com/playlist?list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp)

# Introduction
- **Superscalar Execution:**
  - processor executes independent instructions in parallel on multiple (duplicate) execution units
  - diminishing returns in performance beyond 4 execution units
- > achieving efficient processing almost always comes down to accessing data efficiently
- **Stall:**
  - processor forced to wait because the necessary resources/data are not immediately available
- **Cache:**
  - fast but small on-chip storage that maintains a copy of a subset of the values in memory
  - operates at the granularity of "cache lines"