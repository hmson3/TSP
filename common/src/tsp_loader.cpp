#include "../include/tsp_loader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Node {
    int id;
    double x, y;
};

double euclidean_distance(const Node& a, const Node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return round(sqrt(dx * dx + dy * dy));
}

vector<vector<int>> load_tsplib_file(const string& filename) {
    ifstream file(filename);
    string line;
    vector<Node> nodes;
    bool reading_coords = false;

    while (getline(file, line)) {
        if (line.find("NODE_COORD_SECTION") != string::npos) {
            reading_coords = true;
            continue;
        }
        if (line.find("EOF") != string::npos) break;
        if (reading_coords) {
            istringstream iss(line);
            int id;
            double x, y;
            if (iss >> id >> x >> y) {
                nodes.push_back({id, x, y});
            }
        }
    }

    int n = nodes.size();
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = static_cast<int>(euclidean_distance(nodes[i], nodes[j]));

    return dist;
}
