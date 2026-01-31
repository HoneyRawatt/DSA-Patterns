#include <bits/stdc++.h>
using namespace std;

/*
    ==========================================================
    🔹 PROBLEM: Maximum Falling Path Sum
    ----------------------------------------------------------
    You are given an n x m matrix. From cell (i, j) you can move:
      - down        → (i+1, j)
      - down-left   → (i+1, j-1)
      - down-right  → (i+1, j+1)

    You start from ANY cell in the TOP row and must reach SOME
    cell in the BOTTOM row. Find the MAXIMUM path sum.

    All three methods below solve this:
      1) Memoization (Top-down DP)
      2) Tabulation (Bottom-up DP)
      3) Space Optimized DP
    ==========================================================
*/

/* ==========================================================
   1️⃣ MEMOIZATION (Top-Down DP)
   ----------------------------------------------------------
   ✅ Time Complexity:  O(n * m)
      - Each state (i, j) is computed once.
      - There are n * m states.

   ✅ Space Complexity: O(n * m) for dp
                        + O(n) recursion stack (max depth = n)
   ========================================================== */

int helper(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
    int n = matrix.size();
    int m = matrix[0].size();

    // Out of boundary (invalid) → very small number so it is never chosen
    if (j < 0 || j >= m) return -1e9;

    // Base case: top row
    if (i == 0) return matrix[0][j];

    // If already computed, return stored value
    if (dp[i][j] != -1) return dp[i][j];

    // Move up, up-left, up-right (since we are going from bottom to top)
    int u  = matrix[i][j] + helper(i - 1, j,     matrix, dp);
    int ld = matrix[i][j] + helper(i - 1, j - 1, matrix, dp);
    int rd = matrix[i][j] + helper(i - 1, j + 1, matrix, dp);

    return dp[i][j] = max(u, max(ld, rd));
}

int maxFallingPathSumMemo(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    int ans = -1e9;
    // We can end at any column in the last row
    for (int j = 0; j < m; j++) 
        ans = max(ans, helper(n - 1, j, matrix, dp));

    return ans;
}


/* ==========================================================
   2️⃣ TABULATION (Bottom-Up DP)
   ----------------------------------------------------------
   ✅ Time Complexity:  O(n * m)
      - Double loop over all cells.

   ✅ Space Complexity: O(n * m)
      - 2D dp array of size n x m
   ========================================================== */

int maxFallingPathSumTabu(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Base row: top row of dp is same as matrix
    for (int j = 0; j < m; j++)
        dp[0][j] = matrix[0][j];

    // Fill the DP table from row 1 to n-1
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {

            int u  = matrix[i][j] + dp[i - 1][j];

            int ld = -1e9;
            if (j > 0)
                ld = matrix[i][j] + dp[i - 1][j - 1];

            int rd = -1e9;
            if (j + 1 < m)
                rd = matrix[i][j] + dp[i - 1][j + 1];

            dp[i][j] = max(u, max(ld, rd));
        }
    }

    // Answer = max in last row
    int ans = -1e9;
    for (int j = 0; j < m; j++)
        ans = max(ans, dp[n - 1][j]);

    return ans;
}


/* ==========================================================
   3️⃣ SPACE OPTIMIZED DP (1D)
   ----------------------------------------------------------
   ✅ Time Complexity:  O(n * m)
      - Still loop over all cells.

   ✅ Space Complexity: O(m)
      - Only store previous row and current row (two 1D arrays).
   ========================================================== */

int maxFallingPathSumSO(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<int> prev(m), curr(m);

    // Base row: same as matrix[0]
    for (int j = 0; j < m; j++)
        prev[j] = matrix[0][j];

    // Build from row 1 to n-1
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {

            int u  = matrix[i][j] + prev[j];

            int ld = -1e9;
            if (j > 0)
                ld = matrix[i][j] + prev[j - 1];

            int rd = -1e9;
            if (j + 1 < m)
                rd = matrix[i][j] + prev[j + 1];

            curr[j] = max(u, max(ld, rd));
        }
        // Current row becomes previous for next iteration
        prev = curr;
    }

    int ans = -1e9;
    for (int j = 0; j < m; j++)
        ans = max(ans, prev[j]);

    return ans;
}


/* ==========================================================
   MAIN (for quick testing)
   ========================================================== */

int main() {
    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };

    cout << "Memoization:      " << maxFallingPathSumMemo(matrix) << '\n';
    cout << "Tabulation:       " << maxFallingPathSumTabu(matrix) << '\n';
    cout << "Space Optimized:  " << maxFallingPathSumSO(matrix) << '\n';

    return 0;
}
