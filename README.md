# Priority-Queue-Heap-C

## Overview
A high-performance implementation of a **Priority Queue** based on a **Binary Heap** structure. This project emphasizes low-level system programming and efficient memory management in C.

## Key Features
- **Binary Heap Logic:** Efficient implementation using `UpdateUp` and `UpdateDown` (sift-up/sift-down) algorithms to maintain heap properties with **O(log n)** complexity.
- **Generic Design (Dependency Injection):** The queue is fully decoupled from the data it stores. It uses `void*` and function pointers, allowing users to provide their own:
  - **Allocation/Deallocation** logic (custom memory management).
  - **Comparison** logic (defining what "higher priority" means for a specific struct).
  - **Printing** logic (custom data visualization).
- **Flexible Data Schema:** Demonstrates the use of a `global.h` bridge to handle user-defined structures (like `PQInfo` with dynamic arrays) without modifying the core library.
- **Manual Memory Management:** Deep cleanup routines ensuring no memory leaks, even with nested dynamic structures.

## Tech Stack
- **Language:** C (ANSI C)
- **Concepts:** Function Pointers, Pointer Arithmetic, Heap Data Structure.

---
## Copyright

Copyright (c) 2025 Karol Bartnicki
All rights reserved.

