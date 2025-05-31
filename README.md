# TSP Solver: Held-Karp, Christofides, and My-TSP

This project provides implementations and comparative evaluation of three different algorithms for solving the Travelling Salesman Problem (TSP):

- **Held-Karp** (exact, dynamic programming)
- **Christofides** (1.5-approximation, including greedy variant)
- **My-TSP** (custom clustering-based approximation)

## 🚀 How to Run

### 1. Build the Executables

```bash
mkdir build && cd build
cmake ..
make
```

### 2. Run Experiments

```bash
# Held-Karp
python3 held_karp/run_experiments.py
python3 held_karp/summary.py

# Christofides_2approx
python3 christofides_2approx/run_experiments.py
python3 christofides_2approx/summary.py

# Christofides_greedy
python3 christofides_greedy/run_experiments.py
python3 christofides_greddy/summary.py

# My-tsp
python3 my_tsp/run_experiments.py
python3 my_tsp/summary.py
```
