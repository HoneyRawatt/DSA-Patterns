#include <iostream>
#include <vector>
using namespace std;

/*
    -----------------------------------------------------------
    UNIQUE PATHS (Grid m x n)
    Move only DOWN or RIGHT.
    Count number of ways to reach bottom-right.
    -----------------------------------------------------------

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimized DP (1D DP)
    4. Combinatorics: (m+n-2 choose m-1)
*/


/* -----------------------------------------------------------
    1️⃣ MEMOIZATION
    TIME:  O(m*n)
    SPACE: O(m*n) + recursion
----------------------------------------------------------- */
int unique_paths_memo(int i, int j, vector<vector<int>>& dp)
{
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    int up = unique_paths_memo(i - 1, j, dp);
    int left = unique_paths_memo(i, j - 1, dp);

    return dp[i][j] = up + left;
}


/* -----------------------------------------------------------
    2️⃣ TABULATION (Bottom-Up DP)
    TIME:  O(m*n)
    SPACE: O(m*n)
----------------------------------------------------------- */
int unique_paths_tabulation(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (i == 0 && j == 0) dp[i][j] = 1;
            else {
                int up = (i > 0) ? dp[i - 1][j] : 0;
                int left = (j > 0) ? dp[i][j - 1] : 0;
                dp[i][j] = up + left;
            }
        }
    }
    return dp[m - 1][n - 1];
}


/* -----------------------------------------------------------
    3️⃣ SPACE OPTIMIZED DP (Using 1D array)
    TIME:  O(m*n)
    SPACE: O(n)
----------------------------------------------------------- */
int unique_paths_opti(int m, int n)
{
    vector<int> prev(n, 0);

    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0);

        for (int j = 0; j < n; j++) {

            if (i == 0 && j == 0)
                curr[j] = 1;
            else {
                int up = (i > 0) ? prev[j] : 0;
                int left = (j > 0) ? curr[j - 1] : 0;
                curr[j] = up + left;
            }
        }

        prev = curr;
    }

    return prev[n - 1];
}


/* -----------------------------------------------------------
    4️⃣ COMBINATORICS (nCr)
    Unique paths = C(m+n-2, m-1)
    TIME:  O(min(m,n)) → very fast
    SPACE: O(1)
----------------------------------------------------------- */
int unique_paths_combi(int m, int n)
{
    int N = m + n - 2;   // total moves
    int r = m - 1;       // number of DOWN moves
    double res = 1;

    for (int i = 1; i <= r; i++) {
        res = res * (N - r + i) / i;
    }

    return (int)res; 
}


/* -----------------------------------------------------------
    MAIN FUNCTION TO TEST ALL METHODS
----------------------------------------------------------- */
int main()
{
    int m = 3, n = 7;

    vector<vector<int>> dp(m, vector<int>(n, -1));
    cout << "Memoization:       " << unique_paths_memo(m - 1, n - 1, dp) << endl;
    cout << "Tabulation:        " << unique_paths_tabulation(m, n) << endl;
    cout << "Space Optimized:   " << unique_paths_opti(m, n) << endl;
    cout << "Combinatorics:     " << unique_paths_combi(m, n) << endl;

    return 0;
}
