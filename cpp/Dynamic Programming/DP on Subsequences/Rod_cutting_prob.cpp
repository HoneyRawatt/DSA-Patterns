#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
    ROD CUTTING PROBLEM — INTUITION
===========================================================
You are given:
- N = length of the rod
- price[i] = price of rod piece of length (i+1)

You want the MAXIMUM profit by cutting the rod any number
of times (unbounded knapsack).

Choice:
    For price[i] (which corresponds to rod length L = i+1):

    1) NOT TAKE → try smaller piece index (i-1)
    2) TAKE → if we cut piece of length L, then
         profit = price[i] + solve(i, N-L)

This is exactly UNBOUNDED KNAPSACK where:
    weight = length of pieces
    value  = price
    capacity = N
===========================================================
*/

// =========================================================
// 1) MEMOIZATION
// =========================================================

int rod_cut_memo(int i, int N, vector<int>& price, vector<vector<int>>& dp) {
    if (i == 0) return N * price[0];       // Only length-1 rods available

    if (dp[i][N] != -1) return dp[i][N];

    int notTake = rod_cut_memo(i-1, N, price, dp);

    int take = INT_MIN;
    int rod_length = i + 1;

    if (rod_length <= N)
        take = price[i] + rod_cut_memo(i, N - rod_length, price, dp);

    return dp[i][N] = max(take, notTake);
}

// =========================================================
// 2) TABULATION
// =========================================================

int rod_cut_tabu(int N, vector<int>& price) {
    vector<vector<int>> dp(N, vector<int>(N + 1, 0));

    // Base case: only length-1 rod available
    for (int n = 0; n <= N; n++)
        dp[0][n] = n * price[0];

    for (int i = 1; i < N; i++) {
        int rod_length = i + 1;

        for (int n = 0; n <= N; n++) {
            int notTake = dp[i-1][n];

            int take = INT_MIN;
            if (rod_length <= n)
                take = price[i] + dp[i][n - rod_length];

            dp[i][n] = max(take, notTake);
        }
    }
    return dp[N-1][N];
}

// =========================================================
// 3) SPACE OPTIMIZED — O(N)
// =========================================================

int rod_cut_spaceOpt(int N, vector<int>& price) {
    vector<int> prev(N+1, 0), curr(N+1, 0);

    for (int n = 0; n <= N; n++)
        prev[n] = n * price[0];

    for (int i = 1; i < N; i++) {
        int rod_length = i + 1;

        for (int n = 0; n <= N; n++) {
            int notTake = prev[n];

            int take = INT_MIN;
            if (rod_length <= n)
                take = price[i] + curr[n - rod_length];

            curr[n] = max(take, notTake);
        }
        prev = curr;
    }
    return prev[N];
}

// =========================================================
// 4) MORE SPACE-OPTIMIZED — Only 1 array
// =========================================================

int rod_cut_moreSO(int N, vector<int>& price) {
    vector<int> dp(N+1, 0);

    // Base for length-1 rods
    for (int n = 0; n <= N; n++)
        dp[n] = n * price[0];

    for (int i = 1; i < N; i++) {
        int rod_length = i + 1;

        for (int n = rod_length; n <= N; n++) {
            dp[n] = max(dp[n], price[i] + dp[n - rod_length]);
        }
    }
    return dp[N];
}

// =========================================================
// MAIN FUNCTION
// =========================================================

int main() {
    int N;
    cout << "Enter rod length: ";
    cin >> N;

    vector<int> price(N);
    cout << "Enter prices for rod lengths 1 to " << N << ":\n";
    for (int i = 0; i < N; i++) cin >> price[i];

    // Memoization
    vector<vector<int>> dp(N, vector<int>(N+1, -1));
    int ans1 = rod_cut_memo(N-1, N, price, dp);

    // Tabulation
    int ans2 = rod_cut_tabu(N, price);

    // Space optimized
    int ans3 = rod_cut_spaceOpt(N, price);

    // More optimized
    int ans4 = rod_cut_moreSO(N, price);

    cout << "\nMaximum Profit:\n";
    cout << "Memoization: " << ans1 << endl;
    cout << "Tabulation: " << ans2 << endl;
    cout << "Space Optimized: " << ans3 << endl;
    cout << "More Space Optimized: " << ans4 << endl;

    return 0;
}

/*
===========================================================
TIME & SPACE COMPLEXITIES
-----------------------------------------------------------
1) Memoization:
   Time:  O(N*N)
   Space: O(N*N) + O(N) recursion

2) Tabulation:
   Time:  O(N*N)
   Space: O(N*N)

3) Space Optimized:
   Time:  O(N*N)
   Space: O(2N)

4) Most Optimized:
   Time:  O(N*N)
   Space: O(N)
===========================================================
*/
