#include "../common/include/tsp_loader.hpp"
#include "../common/include/util.hpp"
#include "include/held_karp.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    string instance = (argc > 1) ? argv[1] : "test4";

    string input_path = "../data/" + instance + ".tsp";
    string output_path = "../held_karp/result/held_karp_result.csv";

    auto dist = load_tsplib_file(input_path);

    // 알고리즘 특성상 
    int n = dist.size();
    if (n > 20) {
        cout << "[Held-Karp] Skipped: n = " << n << " is too large for Held-Karp (max 20 allowed)\n";
    return 0;
    }

    auto start = chrono::steady_clock::now();
    int cost = held_karp(dist);
    auto end = chrono::steady_clock::now();

    double time_ms = chrono::duration<double, milli>(end - start).count();

    cout << "[Held-Karp] Cost = " << cost << ", Time = " << time_ms << " ms" << endl;

    save_result(output_path, "held_karp", instance, cost, time_ms);
    return 0;
}
