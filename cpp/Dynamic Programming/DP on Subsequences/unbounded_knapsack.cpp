#include<bits/stdc++.h>
using namespace std;

// 🚀 1) Memoization
// Time: O(N * W)
// Space: O(N * W) + recursion
// 🚀 2) Tabulation
int unbounded_knapsack_memo(int ind, int W, vector<int>& val,
                            vector<int>& wt, vector<vector<int>>& dp) {
    if (ind == 0)
        return (W / wt[0]) * val[0];  // can take unlimited items

    if (dp[ind][W] != -1) return dp[ind][W];

    int notTake = unbounded_knapsack_memo(ind - 1, W, val, wt, dp);

    int take = 0;
    if (wt[ind] <= W)
        take = val[ind] + unbounded_knapsack_memo(ind, W - wt[ind], val, wt, dp);

    return dp[ind][W] = max(take, notTake);
}

// Time: O(N * W)
// Space: O(N * W)
// 🚀 3) Space Optimized (2 arrays)
int unbounded_knapsack_tabu(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    // Base row
    for (int w = 0; w <= W; w++)
        dp[0][w] = (w / wt[0]) * val[0];

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];
            int take = 0;
            if (wt[i] <= w)
                take = val[i] + dp[i][w - wt[i]];  // SAME ROW (unbounded)

            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n - 1][W];
}

// Time: O(N * W)
// Space: O(2W)
int unbounded_knapsack_so(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<int> prev(W + 1, 0), curr(W + 1, 0);

    for (int w = 0; w <= W; w++)
        prev[w] = (w / wt[0]) * val[0];

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];
            int take = 0;
            if (wt[i] <= w)
                take = val[i] + curr[w - wt[i]];  // curr for unbounded

            curr[w] = max(take, notTake);
        }
        prev = curr;
    }

    return prev[W];
}

// Time: O(N * W)
// Space: O(W)
// 🚀 4) MOST OPTIMIZED (1 array only — BEST VERSION)
int unbounded_knapsack_moreso(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<int> dp(W + 1, 0);

    for (int w = 0; w <= W; w++)
        dp[w] = (w / wt[0]) * val[0];

    for (int i = 1; i < n; i++) {
        for (int w = wt[i]; w <= W; w++) {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}


// 🧪 MAIN FUNCTION (Test All Versions)
int main() {
    vector<int> wt = {2, 4, 6};
    vector<int> val = {5, 11, 13};
    int W = 10;
    int n = wt.size();

    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    cout << "Memo: " << unbounded_knapsack_memo(n - 1, W, val, wt, dp) << endl;
    cout << "Tabu: " << unbounded_knapsack_tabu(n, W, val, wt) << endl;
    cout << "SO:   " << unbounded_knapsack_so(n, W, val, wt) << endl;
    cout << "1D:   " << unbounded_knapsack_moreso(n, W, val, wt) << endl;

    return 0;
}
