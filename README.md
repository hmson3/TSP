# TSP ALGORITHMS: Held-Karp, MST-based 2-approximation, Christofides, and My-TSP

This project provides implementations and comparative evaluation of three different algorithms for solving the Travelling Salesman Problem (TSP):

- **Held-Karp** (exact, dynamic programming)
- **MST-based** (2-approximaiton)
- **Christofides** (1.5-approximation, greedy variant)
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
# Run Held-Karp
python3 held_karp/run_experiments.py
python3 held_karp/summary.py  # Generates summary csv

# Run Christofides with MST doubling
python3 christofides_2approx/run_experiments.py
python3 christofides_2approx/summary.py

# Run Christofides with greedy matching
python3 christofides_greedy/run_experiments.py
python3 christofides_greedy/summary.py

# Run My-TSP (LPA + KNN + local TSP merging)
python3 my_tsp/run_experiments.py
python3 my_tsp/summary.py
```
