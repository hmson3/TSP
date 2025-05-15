#pragma once
#include <vector>

int christofides(const std::vector<std::vector<int>>& dist);
std::vector<std::pair<int, int>> compute_mst(const std::vector<std::vector<int>>& dist, int n);
std::vector<int> find_odd_nodes(const std::vector<std::pair<int, int>>& edges, int n);
