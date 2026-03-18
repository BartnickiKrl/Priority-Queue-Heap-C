# Priority-Queue-Heap-C

## Overview
A high-performance implementation of a **Priority Queue** based on a **Binary Heap** (stóg binarny) structure. This project emphasizes low-level system programming and efficient memory management in C.

## Key Features
- **Binary Heap Logic:** Uses `UpdateUp` and `UpdateDown` (sift-up/sift-down) algorithms to maintain heap properties with **O(log n)** complexity.
- **Generic Programming:** Implemented using `void*` pointers and function pointers (comparators), allowing the queue to store any data type.
- **Manual Memory Management:** Full control over allocation (`malloc`/`calloc`) and deep deallocation to ensure zero memory leaks.
- **Dynamic Priority Updates:** Includes functionality to change the priority of an element already present in the queue.

## Tech Stack
- **Language:** C (ANSI C)
- **Concepts:** Function Pointers, Pointer Arithmetic, Heap Data Structure.

---
## Copyright

Copyright (c) 2025 Karol Bartnicki
All rights reserved.

