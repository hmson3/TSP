#pragma once
#include <string>
#include <vector>

void save_result(const std::string& filepath, const std::string& algo, const std::string& instance, int cost, double time_ms, double ratio);
std::vector<int> load_opt_tour(const std::string& path);
int compute_path_cost(const std::vector<int>& path, const std::vector<std::vector<int>>& dist);