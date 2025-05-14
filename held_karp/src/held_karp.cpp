#include "../include/held_karp.hpp"
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

int held_karp(const vector<vector<int>>& dist) {
    
    int n = dist.size();
    cout << "[held_karp] n = " << n << " (input matrix loaded)\n";
    
    // 1. dp 노드 초기화
    int FULL = 1 << n;
    vector<vector<int>> dp(FULL, vector<int>(n, INT_MAX));
    // 시작노드만 방문한 상태 거리는 0
    dp[1][0] = 0;


    // 아직 방문하지 않은 노드 방문 및 DP 채우기
    for(int s = 1; s < FULL; s++) {
        for(int i = 0; i < n; i++) {
            // 현재 방문한 노드에서
            if(!(s & (1<<i))) continue; // 현재 방문한 노드가 아니면 continue
            // 다음 방문할 곳 DP 채우기
            for (int j = 0; j < n; ++j) {
                if (s & (1 << j)) continue;
                int next_s = s | (1 << j);
                if (dp[s][i] != INT_MAX)
                    dp[next_s][j] = min(dp[next_s][j], dp[s][i] + dist[i][j]);
            }
        }
    }
    
    int ret = INT_MAX;
    for(int i = 0; i < n; i++) {
        if (dp[FULL - 1][i] != INT_MAX) 
            ret = min(ret, dp[FULL-1][i] + dist[i][0]);
    }
    return ret;  
}
