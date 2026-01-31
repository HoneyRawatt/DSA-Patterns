#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

/*
-----------------------------------------------------
🐸 FROG JUMP WITH K DISTANCE (Dynamic Programming)
-----------------------------------------------------
A frog is on the 0th stone and wants to reach (n-1)th stone.
It can jump up to 'k' stones ahead at a time.
Jump cost = |stones[i] - stones[j]|.

Goal: Find the minimum total energy to reach the last stone.
-----------------------------------------------------
*/

// 🔸 MEMOIZATION (Top-Down DP)
int frog_jump_memo(int ind, vector<int>& stones, int k, vector<int>& dp) {
    if (ind == 0) return 0;
    if (dp[ind] != -1) return dp[ind];

    int minSteps = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (ind - j >= 0) {
            int jump = frog_jump_memo(ind - j, stones, k, dp)
                        + abs(stones[ind] - stones[ind - j]);
            minSteps = min(minSteps, jump);
        }
    }
    return dp[ind] = minSteps;
}

// 🔸 TABULATION (Bottom-Up DP)
int frog_jump_tab(vector<int>& stones, int k) {
    int n = stones.size();
    vector<int> dp(n, 0);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int minSteps = INT_MAX;
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                int jump = dp[i - j] + abs(stones[i] - stones[i - j]);
                minSteps = min(minSteps, jump);
            }
        }
        dp[i] = minSteps;
    }
    return dp[n - 1];
}

// 🔸 SPACE OPTIMIZED (O(K) space)
int frog_jump_optimized(vector<int>& stones, int k) {
    int n = stones.size();
    vector<int> prev(k, 0); // stores last K dp values

    for (int i = 1; i < n; i++) {
        int minSteps = INT_MAX;
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                int cost = prev[(i - j) % k] + abs(stones[i] - stones[i - j]);
                minSteps = min(minSteps, cost);
            }
        }
        prev[i % k] = minSteps;
    }

    return prev[(n - 1) % k];
}

// 🔹 MAIN FUNCTION
int main() {
    vector<int> stones = {10, 30, 40, 50, 20};
    int k = 3;  // Maximum jump distance
    int n = stones.size();

    vector<int> dp(n, -1);
    cout << "Memoization: " << frog_jump_memo(n - 1, stones, k, dp) << endl;
    cout << "Tabulation: " << frog_jump_tab(stones, k) << endl;
    cout << "Space Optimized: " << frog_jump_optimized(stones, k) << endl;

    return 0;
}


// | Approach        | Time Complexity | Space Complexity | Notes                        |
// | --------------- | --------------- | ---------------- | ---------------------------- |
// | Memoization     | O(N × K)        | O(N)             | Uses recursion + dp          |
// | Tabulation      | O(N × K)        | O(N)             | Iterative, no recursion      |
// | Space Optimized | O(N × K)        | O(K)             | Uses rolling/circular buffer |
