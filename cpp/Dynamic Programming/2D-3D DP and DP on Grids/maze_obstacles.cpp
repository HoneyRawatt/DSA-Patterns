#include <iostream>
#include <vector>
using namespace std;

int mod = (int)(1e9 + 7);

/* -----------------------------------------------------------
    1️⃣ MEMOIZATION
    TIME:  O(m*n)
    SPACE: O(m*n + recursion)
----------------------------------------------------------- */
int mazeObstacles_memo(int i, int j, vector<vector<int>>& arr, vector<vector<int>>& dp)
{
    // If cell is a blocked cell
    if (i >= 0 && j >= 0 && arr[i][j] == -1) return 0;

    // Base case: reached start
    if (i == 0 && j == 0) return 1;

    // Out of bounds
    if (i < 0 || j < 0) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    int up = mazeObstacles_memo(i - 1, j, arr, dp);
    int left = mazeObstacles_memo(i, j - 1, arr, dp);

    return dp[i][j] = (up + left) % mod;
}


/* -----------------------------------------------------------
    2️⃣ TABULATION (Bottom-Up DP)
    TIME:  O(m*n)
    SPACE: O(m*n)
----------------------------------------------------------- */
int mazeObstacles_tabulation(int n, int m, vector<vector<int>>& arr)
{
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (arr[i][j] == -1) {
                dp[i][j] = 0;  // blocked
            }
            else if (i == 0 && j == 0) {
                dp[i][j] = 1;  // starting point
            }
            else {
                int up = (i > 0) ? dp[i - 1][j] : 0;
                int left = (j > 0) ? dp[i][j - 1] : 0;
                dp[i][j] = (up + left) % mod;
            }
        }
    }

    return dp[n - 1][m - 1];
}


/* -----------------------------------------------------------
    3️⃣ SPACE OPTIMIZED DP (1D array)
    TIME:  O(m*n)
    SPACE: O(m)
----------------------------------------------------------- */
int mazeObstacles_opti(int n, int m, vector<vector<int>>& arr)
{
    vector<int> prev(m, 0);

    for (int i = 0; i < n; i++) {
        vector<int> curr(m, 0);

        for (int j = 0; j < m; j++) {

            if (arr[i][j] == -1) {
                curr[j] = 0;
            }
            else if (i == 0 && j == 0) {
                curr[j] = 1;
            }
            else {
                int up = (i > 0) ? prev[j] : 0;
                int left = (j > 0) ? curr[j - 1] : 0;
                curr[j] = (up + left) % mod;
            }
        }

        prev = curr;
    }

    return prev[m - 1];
}


int main() {
    int n, m;
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> arr(n, vector<int>(m));
    cout << "Enter grid (use -1 for obstacles):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }

    // MEMOIZATION CALL
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int memo_ans = mazeObstacles_memo(n - 1, m - 1, arr, dp);

    // TABULATION CALL
    int tabu_ans = mazeObstacles_tabulation(n, m, arr);

    // SPACE OPTIMIZED CALL
    int opti_ans = mazeObstacles_opti(n, m, arr);

    cout << "\nMemoization Result       : " << memo_ans << endl;
    cout << "Tabulation Result        : " << tabu_ans << endl;
    cout << "Space Optimized Result   : " << opti_ans << endl;

    return 0;
}
