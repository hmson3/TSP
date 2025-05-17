#include "../common/include/tsp_loader.hpp"
#include "../common/include/util.hpp"
#include "include/my_tsp.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    string instance = (argc > 1) ? argv[1] : "test20_grid";
    string input_path = "../data/" + instance + ".tsp";
    string output_path = "../my_tsp/result/my_tsp_result.csv";

    auto dist = load_tsplib_file(input_path);

    auto start = chrono::steady_clock::now();
    int cost = my_tsp(dist);
    auto end = chrono::steady_clock::now();

    double time_ms = chrono::duration<double, milli>(end - start).count();

    cout << "[My-TSP] Cost = " << cost << ", Time = " << time_ms << " ms" << endl;

    save_result(output_path, "my_tsp", instance, cost, time_ms);
    return 0;
}