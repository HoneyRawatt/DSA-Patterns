#include <bits/stdc++.h>
using namespace std;

/*
    TRIANGLE MINIMUM PATH SUM
    Allowed moves: Down (i+1, j), Down-right (i+1, j+1)

    Time:  O(n^2)
    Space: O(n^2) for memo/tabu, O(n) for optimized
*/

/* -----------------------------------------------------------
   1️⃣ MEMOIZATION (Top-Down)
----------------------------------------------------------- */
int minimumPathsum_triangle_memo(int i, int j, vector<vector<int>>& triangle, vector<vector<int>>& dp) {
    int n = triangle.size();

    if (i == n - 1)
        return triangle[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int d  = triangle[i][j] + minimumPathsum_triangle_memo(i + 1, j, triangle, dp);
    int dg = triangle[i][j] + minimumPathsum_triangle_memo(i + 1, j + 1, triangle, dp);

    return dp[i][j] = min(d, dg);
}


/* -----------------------------------------------------------
   2️⃣ TABULATION (Bottom-Up)
----------------------------------------------------------- */
int minimumPathsum_triangle_tabu(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base (last row)
    for (int j = 0; j < n; j++)
        dp[n - 1][j] = triangle[n - 1][j];

    // Fill DP from bottom to top
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int d  = triangle[i][j] + dp[i + 1][j];
            int dg = triangle[i][j] + dp[i + 1][j + 1];

            dp[i][j] = min(d, dg);
        }
    }
    return dp[0][0];
}


/* -----------------------------------------------------------
   3️⃣ SPACE OPTIMIZED (1D DP)
----------------------------------------------------------- */
int minimumPathsum_triangle(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> prev(n);

    // Base case (last row → prev[])
    for (int j = 0; j < n; j++)
        prev[j] = triangle[n - 1][j];

    // Process from bottom to top
    for (int i = n - 2; i >= 0; i--) {
        vector<int> curr(n);

        for (int j = 0; j <= i; j++) {
            int d  = triangle[i][j] + prev[j];
            int dg = triangle[i][j] + prev[j + 1];

            curr[j] = min(d, dg);
        }
        prev = curr;
    }
    return prev[0];
}


/* -----------------------------------------------------------
   MAIN
----------------------------------------------------------- */
int main() {
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    cout << "Memoization: " << minimumPathsum_triangle_memo(0, 0, triangle, dp) << endl;
    cout << "Tabulation: " << minimumPathsum_triangle_tabu(triangle) << endl;
    cout << "Optimized: " << minimumPathsum_triangle(triangle) << endl;

    return 0;
}


// Time & Space Complexity
// 1) Memoization

// Time: O(n²)

// Space: O(n²) + recursion stack O(n)

// 2) Tabulation

// Time: O(n²)

// Space: O(n²)

// 3) Space Optimized (Best)

// Time: O(n²)

// Space: O(n)