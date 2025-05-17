#include "../include/util.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void save_result(const string& filepath, const string& algo, const string& instance, int cost, double time_ms, double ratio) {
    ofstream out(filepath, ios::app);  // append mode
    if (!out.is_open()) {
        cerr << "Failed to open result file: " << filepath << endl;
        return;
    }

    // 헤더가 없는 경우 첫 줄에 작성
    out.seekp(0, ios::end);
    if (out.tellp() == 0) {
        out << "algorithm,instance,cost,time_ms,approx_ratio\n";
    }

    // 결과 한 줄 기록
    out << algo << "," << instance << "," << cost << "," << time_ms;
    if (ratio >= 0)
        out << "," << fixed << setprecision(4) << ratio;
    else
        out << ",N/A";
    out << "\n";
    out.close();
}

vector<int> load_opt_tour(const string& path) {
    vector<int> tour;
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[WARN] OPT tour file not found: " << path << endl;
        return tour;
    }
    string line;
    bool reading = false;
    while (getline(file, line)) {
        if (line.find("TOUR_SECTION") != string::npos) {
            reading = true;
            continue;
        }
        if (line.find("-1") != string::npos || line.find("EOF") != string::npos) break;
        if (reading) {
            int node = stoi(line) - 1;
            tour.push_back(node);
        }
    }
    if (!tour.empty() && tour.front() != tour.back())
        tour.push_back(tour.front());
    return tour;
}

int compute_path_cost(const vector<int>& path, const vector<vector<int>>& dist) {
    int total = 0;
    for (int i = 0; i + 1 < (int)path.size(); ++i)
        total += dist[path[i]][path[i + 1]];
    return total;
}

