#include "../common/include/tsp_loader.hpp"
#include "../common/include/util.hpp"
#include "include/my_tsp.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    string instance = (argc > 1) ? argv[1] : "test4";
    string input_path = "../data/" + instance + ".tsp";
    string opt_path = "../data/opt/" + instance + ".opt.tour";
    string output_path = "../my_tsp/result/my_tsp_result.csv";

    auto dist = load_tsplib_file(input_path);

    auto start = chrono::steady_clock::now();
    int cost = my_tsp(dist);
    auto end = chrono::steady_clock::now();

    double time_ms = chrono::duration<double, milli>(end - start).count();

    cout << "[My-TSP] Cost = " << cost << ", Time = " << time_ms << " ms" << endl;

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