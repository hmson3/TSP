#include "../include/util.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void save_result(const string& filepath, const string& algo, const string& instance, int cost, double time_ms) {
    ofstream out(filepath, ios::app);  // append mode
    if (!out.is_open()) {
        cerr << "Failed to open result file: " << filepath << endl;
        return;
    }

    // 헤더가 없는 경우 첫 줄에 작성
    out.seekp(0, ios::end);
    if (out.tellp() == 0) {
        out << "algorithm,instance,cost,time_ms\n";
    }

    // 결과 한 줄 기록
    out << algo << "," << instance << "," << cost << "," << time_ms << "\n";
    out.close();
}
