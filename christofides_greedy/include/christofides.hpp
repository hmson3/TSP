#pragma once
#include <vector>

int christofides(const std::vector<std::vector<int>>& dist);
std::vector<std::pair<int, int>> compute_mst(const std::vector<std::vector<int>>& dist, int n);
std::vector<int> find_odd_nodes(const std::vector<std::pair<int, int>>& edges, int n);
std::vector<std::pair<int, int>> greedy_matching(const std::vector<int>& odd_nodes, const std::vector<std::vector<int>>& dist);
std::vector<std::vector<int>> graph_make(const std::vector<std::pair<int, int>>& mst, const std::vector<std::pair<int, int>>& matching, int n);
std::vector<int> find_eulerian_tour(const std::vector<std::vector<int>>& graph);
std::vector<int> hamiltonian_cycle(const std::vector<int>& tour);