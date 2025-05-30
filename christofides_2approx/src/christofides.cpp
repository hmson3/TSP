#include "../include/christofides.hpp"
#include <vector>
#include <climits>
#include <iostream>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

int christofides(const vector<vector<int>>& dist) {
    int n = dist.size();
    cout << "[Christofides] n = " << n << "\n";
    auto mst = compute_mst(dist,n);
    /*cout << "edges = " << mst.size() << "\n";
    for (auto [u, v] : mst) { 
        cout << u << " - " << v << " (" << dist[u][v] << ")" << "\n";
    }*/

    vector<vector<int>> graph(n);

    // MST 간선 추가
    for (auto [u, v] : mst) {
        graph[u].push_back(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
        graph[v].push_back(u);
    }

    auto tour = find_eulerian_tour(graph);
    
    /*
    cout << "Eulerian Tour: ";
    for (int v : tour) cout << v << " ";
    cout << '\n';
    */

    auto cycle = hamiltonian_cycle(tour);

    /*
    cout << "cycle: ";
    for(auto vv : cycle) cout << vv << ' ';
    cout << '\n';
    */
    
    int ret = 0;
    for(int i = 0; i + 1 < (int)cycle.size(); i++) ret += dist[cycle[i]][cycle[i+1]];

    return ret; 
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
/*
vector<int> find_odd_nodes(const vector<pair<int, int>>& edges, int n) {
    vector<int> degree(n, 0);
    for (auto [u, v] : edges) {
        degree[u]++;
        degree[v]++;
    }

    vector<int> odd_nodes;
    for (int i = 0; i < n; i++) {
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

vector<vector<int>> graph_make(const vector<pair<int, int>>& mst, const vector<pair<int, int>>& matching, int n) {
    vector<vector<int>> ret(n);

    // MST 간선 추가
    for (auto [u, v] : mst) {
        ret[u].push_back(v);
        ret[v].push_back(u);
    }

    // Matching 간선 추가
    for (auto [u, v] : matching) {
        ret[u].push_back(v);
        ret[v].push_back(u);
    }

    return ret;
}
*/
// Hierholzer’s Algorithm
// 1. 정점에서 시작
// 2. 갈 수 있는 간선을 따라 DFS처럼 탐색하며 경로 저장
// 3. 더 이상 갈 데가 없으면 백트래킹하면서 경로를 이어붙임
// [0,1,2,0] + [1,3,1] => [0,1,3,1,2,0]
// 4. 모든 간선 쓸때까지 반복
vector<int> find_eulerian_tour(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> tour;
    vector<multiset<int>> adj(n);
    stack<int> s;
    // 간선이 중복가능하고 없애야 하기 때문에 multiset 사용
    // set 사용시 간선 중복 불가, 사용하지 않을 시 간선 삭제에 O(n) 걸림
    for (int u = 0; u < n; u++)
        for (int v : graph[u])
            adj[u].insert(v);
    
    s.push(0);
    
    while(!s.empty()) {
        int u = s.top();
        if(adj[u].empty()) {
            tour.push_back(u);
            s.pop();
        }
        else {
            auto it = adj[u].begin();
            int v = *it;
            adj[u].erase(it);
            adj[v].erase(adj[v].find(u));
            s.push(v);
        }
    }

    reverse(tour.begin(),tour.end());

    return tour;
}

vector<int> hamiltonian_cycle(const vector<int>& tour) {
    vector<bool> visited(tour.size(), false);
    vector<int> ret;

    for (int node : tour) {
        if (!visited[node]) {
            visited[node] = true;
            ret.push_back(node);
        }
    }

    ret.push_back(ret[0]);
    return ret;
}