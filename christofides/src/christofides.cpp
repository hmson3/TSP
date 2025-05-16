#include "../include/christofides.hpp"
#include <vector>
#include <climits>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int christofides(const vector<vector<int>>& dist) {
    int n = dist.size();
    cout << "[Christofides] n = " << n << "\n";
    auto mst = compute_mst(dist,n);
    cout << "edges = " << mst.size() << "\n";
    for (auto [u, v] : mst) { 
        cout << u << " - " << v << " (" << dist[u][v] << ")" << "\n";
    }

    auto odd_nodes = find_odd_nodes(mst, n);

    cout << "odd nodes = ";
    for (int v : odd_nodes) cout << v << " ";
    cout << "\n";   

    // 원래 blossom 알고리즘으로 완전매칭을 구현해야하지만 너무 복잡하고 오래걸림 O(n^3) 
    // 이거 때문에 Christofides 알고리즘 시간복잡도가 O(n^3)
    // 그리디로 구현 후에 성능 비교?

    auto matchings = greedy_matching(odd_nodes, dist);
    for (auto [u, v] : matchings) {
        cout << u << " - " << v << " (dist = " << dist[u][v] << ")" << endl;
    }

    return -1; 
}



vector<pair<int, int>> compute_mst(const vector<vector<int>>& dist, int n) {
    vector<bool> in_tree(n, false);
    vector<pair<int, int>> edges;

    using Edge = tuple<int, int, int>; // cost, u, v
    priority_queue<Edge, vector<Edge>, greater<>> pq;

    in_tree[0] = true;
    for (int i = 1; i < n; i++) {
        pq.push({dist[0][i], 0, i});
    }
    while (!pq.empty() && edges.size() < unsigned(n - 1)) {
        auto [cost, u, v] = pq.top();
        pq.pop();

        if (in_tree[v]) continue;
        in_tree[v] = true;
        edges.push_back({u,v});

        for (int i = 0; i < n; i++) {
            if(!in_tree[i])
                pq.push({dist[v][i], v, i});
        }   
    }

    return edges;
}

vector<int> find_odd_nodes(const vector<pair<int, int>>& edges, int n) {
    vector<int> degree(n, 0);
    for (auto [u, v] : edges) {
        degree[u]++;
        degree[v]++;
    }

    vector<int> odd_nodes;
    for (int i = 0; i < n; ++i) {
        if (degree[i] % 2 == 1)
            odd_nodes.push_back(i);
    }
    return odd_nodes;
}

vector<pair<int, int>> greedy_matching(const vector<int>& odd_nodes, const vector<vector<int>>& dist) {

    vector<pair<int, int>> ret;
    int n = odd_nodes.size();
    vector<bool> matched(n, false);

    vector<tuple<int, int, int>> candi;

    // 모든 후보 거리 계산
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int u = odd_nodes[i];
            int v = odd_nodes[j];
            candi.push_back({dist[u][v], i, j});
        }
    }

    // 거리순에 정렬
    sort(candi.begin(),candi.end());
 
    // 가까운 순으로 매칭
    int nn = 0; 
    for(auto[cost,i,j] : candi) {
        if(nn >= n) break;
        if(matched[i] || matched[j]) continue;
        matched[i] = true;
        matched[j] = true;
        ret.push_back({odd_nodes[i], odd_nodes[j]});
        nn += 2;
    }

    return ret;
}