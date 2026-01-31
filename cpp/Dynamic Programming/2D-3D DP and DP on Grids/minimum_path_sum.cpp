#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🔹 PROBLEM: Minimum Path Sum (Grid)
Move only RIGHT or DOWN from (0,0) to (n-1,m-1)
Return minimum cost path.
-----------------------------------------------------
*/

/*
=====================================================
▶ 1. MEMOIZATION (Top-Down DP)
-----------------------------------------------------
INTUITION:
We try to reach cell (i,j) from (0,0). From each cell,
we can come from UP (i-1,j) or LEFT (i,j-1).
So, dp[i][j] = grid[i][j] + min( up, left )

We use recursion + dp[][] to avoid recomputation.

TIME:  O(n*m)
SPACE: O(n*m) dp + O(n+m) recursion stack
=====================================================
*/
int minPathsum_memo(int i, int j,
                    vector<vector<int>>& grid,
                    vector<vector<int>>& dp) 
{
    // Base case: start cell
    if (i == 0 && j == 0)
        return dp[0][0] = grid[0][0];

    // Out of bounds → return very large value
    if (i < 0 || j < 0)
        return 1e9;

    // Already solved?
    if (dp[i][j] != -1)
        return dp[i][j];

    // Try UP and LEFT paths
    int up   = grid[i][j] + minPathsum_memo(i - 1, j, grid, dp);
    int left = grid[i][j] + minPathsum_memo(i, j - 1, grid, dp);

    return dp[i][j] = min(up, left);
}


/*
=====================================================
▶ 2. TABULATION (Bottom-Up DP)
-----------------------------------------------------
INTUITION:
We fill dp table from (0,0) → (n-1,m-1)
Each cell gets the minimum of coming from UP or LEFT.

TIME:  O(n*m)
SPACE: O(n*m)
=====================================================
*/
int minPathsum_tabulation(vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (i == 0 && j == 0)
                dp[i][j] = grid[0][0];
            else {
                int up = grid[i][j];
                if (i > 0) up += dp[i - 1][j];
                else up += 1e9;

                int left = grid[i][j];
                if (j > 0) left += dp[i][j - 1];
                else left += 1e9;

                dp[i][j] = min(up, left);
            }
        }
    }

    return dp[n - 1][m - 1];
}


/*
=====================================================
▶ 3. SPACE-OPTIMIZED DP (Best Method)
-----------------------------------------------------
INTUITION:
To compute row i, we only need:
- previous row (prev[])
- current row   (curr[])

Thus reduce O(n*m) → O(m)

TIME:  O(n*m)
SPACE: O(m)
=====================================================
*/
int minPathSum_spaceOptimized(vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();

    vector<int> prev(m, 0);

    for (int i = 0; i < n; i++) {
        vector<int> curr(m, 0);

        for (int j = 0; j < m; j++) {

            if (i == 0 && j == 0)
                curr[j] = grid[0][0];
            else {
                int up = grid[i][j];
                if (i > 0) up += prev[j];
                else up += 1e9;

                int left = grid[i][j];
                if (j > 0) left += curr[j - 1];
                else left += 1e9;

                curr[j] = min(up, left);
            }
        }

        prev = curr;  // move current row into prev
    }

    return prev[m - 1];
}


/*
=====================================================
▶ MAIN FUNCTION
=====================================================
*/
int main()
{
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    int n = grid.size(), m = grid[0].size();

    // Memoization usage
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << "Memoization Answer: "
         << minPathsum_memo(n - 1, m - 1, grid, dp) << "\n";

    // Tabulation usage
    cout << "Tabulation Answer: "
         << minPathsum_tabulation(grid) << "\n";

    // Space Optimized usage
    cout << "Space Optimized Answer: "
         << minPathSum_spaceOptimized(grid) << "\n";

    return 0;
}
