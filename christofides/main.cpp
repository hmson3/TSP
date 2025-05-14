#include "../common/include/tsp_loader.hpp"
#include "../common/include/util.hpp"
#include "include/christofides.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    string instance = (argc > 1) ? argv[1] : "test18";
    string input_path = "../data/" + instance + ".tsp";
    string output_path = "../christofides/result/christofides_result.csv";

    auto dist = load_tsplib_file(input_path);

    auto start = chrono::steady_clock::now();
    int cost = christofides(dist);
    auto end = chrono::steady_clock::now();

    double time_ms = chrono::duration<double, milli>(end - start).count();

    cout << "[Christofides] Cost = " << cost << ", Time = " << time_ms << " ms" << endl;

    save_result(output_path, "christofides", instance, cost, time_ms);
    return 0;
}
