#pragma once
#include <vector>

int my_tsp(const std::vector<std::vector<int>>& dist);
std::vector<std::vector<int>> build_knn(const std::vector<std::vector<int>>& dist, int k);
std::vector<int> run_lpa(const std::vector<std::vector<int>>& graph, int max_iter = 20);
std::vector<int> tsp_nearest_neighbor(const std::vector<int>& nodes, const std::vector<std::vector<int>>& dist, bool representative);
