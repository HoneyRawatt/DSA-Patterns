#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

/*
-------------------------------------------------------
🔹 PROBLEM: Frog Jump (Minimum Energy to Reach Last Stone)
-------------------------------------------------------
Given heights of stones (or stairs), the frog can jump
either 1 or 2 steps. The cost of jumping from stone i to j
is |stones[i] - stones[j]|. Find the minimum total energy
required to reach the last stone.

Example:
stones = [10, 20, 30, 10]
Output = 20
-------------------------------------------------------
*/

// 🔸 MEMOIZATION (Top-Down DP)
int maxjump_memoization(int ind, vector<int>& stones, vector<int>& dp) {
    if (ind == 0) return dp[ind] = 0;
    if (dp[ind] != -1) return dp[ind];

    int left = maxjump_memoization(ind - 1, stones, dp) + abs(stones[ind] - stones[ind - 1]);
    int right = INT_MAX;
    if (ind > 1)
        right = maxjump_memoization(ind - 2, stones, dp) + abs(stones[ind] - stones[ind - 2]);

    return dp[ind] = min(left, right);
}

// 🔸 TABULATION (Bottom-Up DP)
int maxjump_tabulation(vector<int>& stones) {
    int n = stones.size();
    vector<int> dp(n, 0);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int fs = dp[i - 1] + abs(stones[i] - stones[i - 1]);
        int ss = INT_MAX;
        if (i > 1)
            ss = dp[i - 2] + abs(stones[i] - stones[i - 2]);
        dp[i] = min(fs, ss);
    }
    return dp[n - 1];
}

// 🔸 SPACE-OPTIMIZED (O(1) space)
int maxJump(vector<int>& stones) {
    int prev = 0;   // DP[i-1]: min energy to reach (i-1)
    int prev2 = 0;  // DP[i-2]: min energy to reach (i-2)

    for (int i = 1; i < stones.size(); i++) {
        int oneStep = prev + abs(stones[i] - stones[i - 1]);
        int twoStep = INT_MAX;
        if (i > 1)
            twoStep = prev2 + abs(stones[i] - stones[i - 2]);

        int curr = min(oneStep, twoStep);
        prev2 = prev;
        prev = curr;
    }

    return prev;  // min energy to reach last stone
}

// 🔹 MAIN FUNCTION
int main() {
    vector<int> stones = {10, 20, 30, 10};
    int n = stones.size();

    // For Memoization
    vector<int> dp(n, -1);
    cout << "Memoization: " << maxjump_memoization(n - 1, stones, dp) << endl;

    // For Tabulation
    cout << "Tabulation: " << maxjump_tabulation(stones) << endl;

    // For Space Optimization
    cout << "Optimized: " << maxJump(stones) << endl;

    return 0;
}
