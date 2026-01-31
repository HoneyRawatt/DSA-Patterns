#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:
-----------
We want to count ALL square submatrices that contain only 1s.

Key idea:
Let dp[i][j] = size of the largest square submatrix
              ending at cell (i, j) as the bottom-right corner.

If arr[i][j] == 0 → dp[i][j] = 0 (no square possible)
If arr[i][j] == 1 → dp[i][j] =
    1 + min(
        dp[i-1][j],     // top
        dp[i][j-1],     // left
        dp[i-1][j-1]    // top-left
    )

Why min?
Because a square can only grow if all three neighbors
support forming a larger square.

Each dp[i][j] contributes dp[i][j] squares:
Example: if dp[i][j] = 3 → squares of size 1, 2, 3
*/

int countSquares(int n, int m, vector<vector<int>>& arr) {
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int sum = 0;

    // First row
    for (int j = 0; j < m; j++) {
        dp[0][j] = arr[0][j];
        sum += dp[0][j];
    }

    // First column (start from i = 1 to avoid double counting dp[0][0])
    for (int i = 1; i < n; i++) {
        dp[i][0] = arr[i][0];
        sum += dp[i][0];
    }

    // Fill remaining DP table
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (arr[i][j] == 1) {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                });
            }
            // else dp[i][j] = 0 (already 0 by initialization)

            sum += dp[i][j];
        }
    }

    return sum;
}

/*
TIME COMPLEXITY:
----------------
O(n × m)
Each cell is computed once.

SPACE COMPLEXITY:
-----------------
O(n × m)
DP table of same size as matrix.
(Can be optimized to O(m) if required)
*/

int main() {
    vector<vector<int>> matrix = {
        {1, 0, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int n = matrix.size();
    int m = matrix[0].size();

    cout << "Total square submatrices with all 1s: "
         << countSquares(n, m, matrix) << endl;

    return 0;
}
