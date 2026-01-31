#include <bits/stdc++.h>
using namespace std;

const int NEG = -1e8;

/* ============================================================
   1️⃣ MEMOIZATION (TOP-DOWN DP)
   Time:  O(n * m * m * 9)
   Space: O(n * m * m) + recursion stack
   ============================================================ */
int cherryPickupMemo(int i, int j1, int j2,
                     vector<vector<int>>& grid,
                     vector<vector<vector<int>>>& dp)
{
    int n = grid.size(), m = grid[0].size();

    // Out of bounds
    if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m)
        return NEG;

    // Last row
    if (i == n - 1)
    {
        if (j1 == j2) return grid[i][j1];
        return grid[i][j1] + grid[i][j2];
    }

    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int maxi = NEG;

    // 9 possible moves
    for (int d1 = -1; d1 <= 1; d1++)
    {
        for (int d2 = -1; d2 <= 1; d2++)
        {
            int value = 0;
            if (j1 == j2)
                value = grid[i][j1];
            else
                value = grid[i][j1] + grid[i][j2];

            value += cherryPickupMemo(i + 1, j1 + d1, j2 + d2, grid, dp);
            maxi = max(maxi, value);
        }
    }
    return dp[i][j1][j2] = maxi;
}

/* ============================================================
   2️⃣ TABULATION (BOTTOM-UP DP)
   Time:  O(n * m * m * 9)
   Space: O(n * m * m)
   ============================================================ */
int cherryPickupTab(vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, 0)));

    // Fill base row
    for (int j1 = 0; j1 < m; j1++)
    {
        for (int j2 = 0; j2 < m; j2++)
        {
            if (j1 == j2) dp[n - 1][j1][j2] = grid[n - 1][j1];
            else dp[n - 1][j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
        }
    }

    // Fill upwards
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                int maxi = NEG;

                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        int value = 0;
                        if (j1 == j2)
                            value = grid[i][j1];
                        else
                            value = grid[i][j1] + grid[i][j2];

                        if (j1 + d1 >= 0 && j1 + d1 < m &&
                            j2 + d2 >= 0 && j2 + d2 < m)
                            value += dp[i + 1][j1 + d1][j2 + d2];
                        else
                            value += NEG;

                        maxi = max(maxi, value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }

    return dp[0][0][m - 1];
}

/* ============================================================
   3️⃣ SPACE OPTIMIZED (ONLY 2 LAYERS)
   Time:  O(n * m * m * 9)
   Space: O(m * m)
   ============================================================ */
int cherryPickupSO(vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> front(m, vector<int>(m, 0));
    vector<vector<int>> curr(m, vector<int>(m, 0));

    // Base row
    for (int j1 = 0; j1 < m; j1++)
    {
        for (int j2 = 0; j2 < m; j2++)
        {
            if (j1 == j2) front[j1][j2] = grid[n - 1][j1];
            else front[j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
        }
    }

    // Fill upwards
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                int maxi = NEG;

                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        int value = (j1 == j2)
                                        ? grid[i][j1]
                                        : grid[i][j1] + grid[i][j2];

                        if (j1 + d1 >= 0 && j1 + d1 < m &&
                            j2 + d2 >= 0 && j2 + d2 < m)
                            value += front[j1 + d1][j2 + d2];
                        else
                            value += NEG;

                        maxi = max(maxi, value);
                    }
                }

                curr[j1][j2] = maxi;
            }
        }
        front = curr;
    }

    return front[0][m - 1];
}

/* ============================================================
   MAIN FUNCTION
   ============================================================ */
int main()
{
    vector<vector<int>> grid = {
        {3, 1, 1},
        {2, 5, 1},
        {1, 5, 5},
        {2, 1, 1}
    };

    int n = grid.size(), m = grid[0].size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));

    cout << "Memoization: " << cherryPickupMemo(0, 0, m - 1, grid, dp) << "\n";
    cout << "Tabulation: " << cherryPickupTab(grid) << "\n";
    cout << "Space Optimized: " << cherryPickupSO(grid) << "\n";

    return 0;
}
