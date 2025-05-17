#include "../include/my_tsp.hpp"
#include "../../held_karp/include/held_karp.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <random>
#include <climits>

using namespace std;

int my_tsp(const vector<vector<int>>& dist) {
    int n = dist.size();
    cout << "[My-TSP] n = " << n << endl;

    // KNN 그래프
    int k = 5;
    auto graph = build_knn(dist, k);

    // LPA 클러스터링
    auto label = run_lpa(graph);
    /*
    cout << "[LPA] Labels: ";
    for (int x : label) cout << x << " ";
    cout << endl;
    */

    // 클러스터별 부분 TSP
    unordered_map<int, vector<int>> clusters;
    vector<vector<int>> cluster_paths;

    for (int i = 0; i < (int)label.size(); i++) {
        clusters[label[i]].push_back(i);
    }

    for (auto& [label, nodes] : clusters) {
        auto path = tsp_nearest_neighbor(nodes, dist, 0);
        cluster_paths.push_back(path);
    }
    
    /*
    for (int i = 0; i < (int)cluster_paths.size(); i++) {
        cout << "[cluster " << i << "] ";
        for (int v : cluster_paths[i]) cout << v << " ";
        cout << endl;
    }
    */


    // 먼저 cluster 대표 노드 수집
    vector<int> representatives;
    unordered_map<int, int> nti;
    for (int i = 0; i < (int)cluster_paths.size(); i++) {
        int rep = cluster_paths[i].front();
        representatives.push_back(rep);
        nti[rep] = i;
    }

    // 대표 노드 순서 정하기기
    vector<int> cluster_order;
    for (int rep : tsp_nearest_neighbor(representatives, dist, true)) {
        cluster_order.push_back(nti[rep]);
    }

    // 경로 합치기
    vector<int> full_path;
    for (int cid : cluster_order) {
        auto& path = cluster_paths[cid];
        full_path.insert(full_path.end(), path.begin(), path.end() - 1);
    }

    full_path.push_back(full_path[0]);

    /*
    cout << "[full_path] = ";
    for(auto vv : full_path) cout << vv << ' ';
    cout << endl;
    */

    // 비용계산
    int ret = 0;
    for (int i = 0; i + 1 < (int)full_path.size(); i++)
        ret += dist[full_path[i]][full_path[i + 1]];
    
    return ret;
}

vector<vector<int>> build_knn(const vector<vector<int>>& dist, int k) {
    int n = dist.size();
    vector<vector<int>> graph(n);

    for (int u = 0; u < n; u++) {
        vector<pair<int, int>> neighbors;
        for (int v = 0; v < n; v++) {
            if (u == v) continue;
            neighbors.push_back({dist[u][v], v});
        }

        sort(neighbors.begin(), neighbors.end());

        int kk = min(k, (int)neighbors.size());
        for (int i = 0; i < kk; i++) {
            int v = neighbors[i].second;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }

    return graph;
}

vector<int> run_lpa(const vector<vector<int>>& graph, int max_iter) {
    int n = graph.size();
    vector<int> label(n);
    for (int i = 0; i < n; i++) label[i] = i;

    mt19937 rng(3);
    for (int iter = 0; iter < max_iter; iter++) {
        vector<int> nodes(n);
        for (int i = 0; i < n; i++) {
            nodes[i] = i;
        }
        shuffle(nodes.begin(), nodes.end(), rng);

        for (int u : nodes) {
            unordered_map<int, int> freq;
            for (int v : graph[u]) {
                freq[label[v]]++;
            }

            // 가장 자주 나온 라벨 선택
            int best_label = label[u];
            int best_freq = -1;
            for (auto& [lab, f] : freq) {
                if (f > best_freq || (f == best_freq && lab < best_label)) {
                    best_label = lab;
                    best_freq = f;
                }
            }
            label[u] = best_label;
        }
    }
    return label;
}

vector<int> tsp_nearest_neighbor(const vector<int>& nodes, const vector<vector<int>>& dist, bool representative) {
    int m = nodes.size();
    vector<bool> visited(m, false);
    vector<int> path;

    int idx = 0;
    path.push_back(nodes[idx]);
    visited[idx] = true;
    int si = 1;
    
    while(si < m) {
        int u = nodes[idx];
        int best_dist = INT_MAX, next_idx = -1;

        for (int i = 0; i < m; i++) {
            if (visited[i]) continue;
            int v = nodes[i];
            if (dist[u][v] < best_dist) {
                best_dist = dist[u][v];
                next_idx = i;
            }
        }

        idx = next_idx;
        visited[idx] = true;
        path.push_back(nodes[idx]);
        si++;
    }
    if(representative) return path;
    path.push_back(path[0]);
    return path;
}

