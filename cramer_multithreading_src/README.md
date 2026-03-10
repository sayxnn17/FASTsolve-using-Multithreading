<h1 align="center">FASTsolve using Multithreading</h1>

<p align="center">
High-performance C++ implementation of <b>Cramer's Rule</b> using <b>multithreading</b> to solve systems of linear equations efficiently.
</p>

---

## Overview

FASTsolve is a C++ project that solves systems of linear equations using **Cramer's Rule**, while improving performance through **multithreading**.

Cramer's Rule requires multiple determinant calculations. Since each determinant is independent, they can be computed in parallel, making the algorithm a good demonstration of **parallel numerical computation**.

The project focuses on:

- Efficient determinant computation
- Parallel execution using multiple threads
- Better CPU utilization on multi-core systems

---

## How It Works

Given a system:

```
A · X = B
```

Where:

- **A** → coefficient matrix  
- **X** → unknown variables  
- **B** → constant vector  

Using Cramer's Rule:

```
Xi = det(Ai) / det(A)
```

Where:

- `det(A)` → determinant of coefficient matrix  
- `Ai` → matrix formed by replacing column *i* of `A` with `B`

### Parallelization Strategy

Each `det(Ai)` calculation is independent.

So the program:

1. Computes `det(A)`
2. Creates multiple threads
3. Each thread computes one determinant `det(Ai)`
4. Results are combined to obtain the final solution

---

## Project Structure

```
cramer_multithreading_src
│
├── main.cpp
│   Entry point of the program
│
├── cramer.cpp
│   Implementation of Cramer's Rule
│
├── cramer.h
│   Function declarations and structures
│
├── thread_worker.cpp
│   Worker thread logic
│
├── thread_worker.h
│   Thread worker definitions
│
└── Makefile
    Build configuration
```

## Why Multithreading?

Determinant computation becomes expensive as matrix size increases.

Using multithreading:

- Independent computations run simultaneously
- CPU cores are utilized efficiently
- Execution time decreases for larger systems

---

## Concepts Demonstrated

- Multithreading in C++
- Parallel computation
- Numerical methods
- Matrix determinant calculation
- Cramer's Rule

---

## Possible Improvements

- Replace Cramer's Rule with **LU decomposition** for better scalability
- Add **OpenMP support**
- Benchmark single-thread vs multi-thread performance
- Add file-based input
- Support larger matrices

---
