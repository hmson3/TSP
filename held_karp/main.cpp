#include "../common/include/tsp_loader.hpp"
#include "../common/include/util.hpp"
#include "include/held_karp.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    string instance = (argc > 1) ? argv[1] : "test4";
    string input_path = "../data/" + instance + ".tsp";
    string opt_path = "../data/opt/" + instance + ".opt.tour";
    string output_path = "../held_karp/result/held_karp_result.csv";

    auto dist = load_tsplib_file(input_path);

    // 알고리즘 특성상 n이 넘어가면 공간 시간 부족 그래서 n을 25이하로 잡음
    int n = dist.size();
    if (n > 24) {
        cout << "[Held-Karp] Skipped: n = " << n << " is too large for Held-Karp (max 25 allowed)\n";
        return 0;
    }

    auto start = chrono::steady_clock::now();
    int cost = held_karp(dist);
    auto end = chrono::steady_clock::now();

    double time_ms = chrono::duration<double, milli>(end - start).count();

    cout << "[Held-Karp] Cost = " << cost << ", Time = " << time_ms << " ms" << endl;

    auto opt_path_vec = load_opt_tour(opt_path);
    double ratio = -1.0;
    if (!opt_path_vec.empty()) {
        int opt_cost = compute_path_cost(opt_path_vec, dist);
        ratio = static_cast<double>(cost) / opt_cost;
        cout << "[OPT] Cost = " << opt_cost << ", Approx Ratio = " << fixed << setprecision(4) << ratio << endl;
    } else {
        cout << "[OPT] N/A" << endl;
    }

    save_result(output_path, "my_tsp", instance, cost, time_ms, ratio);
    return 0;
}
