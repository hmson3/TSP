#include "../include/held_karp.hpp"
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

int held_karp(const vector<vector<int>>& dist) {
    
    // 1. dp 노드 초기화
    int n = dist.size();
    int FULL = 1 << n;
    vector<vector<int>> dp(FULL, vector<int>(n, INT_MAX));
    // 시작노드만 방문한 상태 거리는 0
    dp[1][0] = 0;

    // 아직 방문하지 않은 노드 방문 및 DP 채우기
    

    cout << "[held_karp] n = " << n << " (input matrix loaded)\n";

    
    return -1;  
}
