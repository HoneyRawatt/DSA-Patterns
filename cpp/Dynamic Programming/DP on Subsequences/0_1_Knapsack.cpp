#include <bits/stdc++.h>
using namespace std;

/*
    0/1 Knapsack Problem:
    Given weights[] and value[] and maxWeight W,
    find maximum total value using each item 0 or 1 time.

    Approaches:
    1) Memoization
    2) Tabulation
    3) Space Optimized (2 rows)
    4) More Optimized (1 row, reverse loop)
*/

//////////////////////////////////////////////////////////
// 1) MEMOIZATION
// Time: O(N * W)
// Space: O(N * W) + O(N) recursion stack
//////////////////////////////////////////////////////////
int knapsack_memo(int ind, int W, vector<int>& weight, vector<int>& value, vector<vector<int>>& dp) {

    if (ind == 0) {
        if (weight[0] <= W) return value[0];
        else return 0;
    }

    if (dp[ind][W] != -1) return dp[ind][W];

    int notTake = knapsack_memo(ind - 1, W, weight, value, dp);
    int take = INT_MIN;

    if (weight[ind] <= W)
        take = value[ind] + knapsack_memo(ind - 1, W - weight[ind], weight, value, dp);

    return dp[ind][W] = max(take, notTake);
}

//////////////////////////////////////////////////////////
// 2) TABULATION
// Time: O(N * W)
// Space: O(N * W)
//////////////////////////////////////////////////////////
int knapsack_tabu(vector<int>& weight, vector<int>& value, int maxWeight) {

    int n = weight.size();
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

    // Base case for item 0
    for (int W = weight[0]; W <= maxWeight; W++)
        dp[0][W] = value[0];

    for (int i = 1; i < n; i++) {
        for (int W = 0; W <= maxWeight; W++) {

            int notTake = dp[i - 1][W];
            int take = INT_MIN;

            if (weight[i] <= W)
                take = value[i] + dp[i - 1][W - weight[i]];

            dp[i][W] = max(take, notTake);
        }
    }

    return dp[n - 1][maxWeight];
}

//////////////////////////////////////////////////////////
// 3) SPACE OPTIMIZED (2 rows)
// Time: O(N * W)
// Space: O(W)
//////////////////////////////////////////////////////////
int knapsack_So(vector<int>& weight, vector<int>& value, int maxWeight) {

    int n = weight.size();
    vector<int> prev(maxWeight + 1, 0), curr(maxWeight + 1, 0);

    for (int W = weight[0]; W <= maxWeight; W++)
        prev[W] = value[0];

    for (int i = 1; i < n; i++) {
        for (int W = 0; W <= maxWeight; W++) {

            int notTake = prev[W];
            int take = INT_MIN;

            if (weight[i] <= W)
                take = value[i] + curr[W - weight[i]];

            curr[W] = max(take, notTake);
        }

        prev = curr;
    }

    return prev[maxWeight];
}

//////////////////////////////////////////////////////////
// 4) MORE OPTIMIZED (1 row, reverse loop)
// Time: O(N * W)
// Space: O(W)  → BEST VERSION
//////////////////////////////////////////////////////////
int knapsack_moreSo(vector<int>& weight, vector<int>& value, int maxWeight) {

    int n = weight.size();
    vector<int> dp(maxWeight + 1, 0);

    // Initialize from item 0
    for (int W = weight[0]; W <= maxWeight; W++)
        dp[W] = value[0];

    for (int i = 1; i < n; i++) {

        // BACKWARD LOOP is the KEY for 1D DP
        for (int W = maxWeight; W >= 0; W--) {

            int notTake = dp[W];
            int take = INT_MIN;

            if (weight[i] <= W)
                take = value[i] + dp[W - weight[i]];

            dp[W] = max(take, notTake);
        }
    }

    return dp[maxWeight];
}

//////////////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////////////
int main() {

    vector<int> weight = {1, 3, 4, 5};
    vector<int> value = {1, 4, 5, 7};
    int maxWeight = 7;
    int n = weight.size();

    // Memoization call
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
    int ans_memo = knapsack_memo(n - 1, maxWeight, weight, value, dp);

    // Tabulation call
    int ans_tabu = knapsack_tabu(weight, value, maxWeight);

    // Space Optimized
    int ans_so = knapsack_So(weight, value, maxWeight);

    // More optimized
    int ans_moreSo = knapsack_moreSo(weight, value, maxWeight);

    cout << "Memoization:           " << ans_memo << "\n";
    cout << "Tabulation:            " << ans_tabu << "\n";
    cout << "Space Optimized:       " << ans_so << "\n";
    cout << "More Space Optimized:  " << ans_moreSo << "\n";

    return 0;
}
