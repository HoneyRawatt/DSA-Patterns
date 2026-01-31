#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------
RECURSIVE APPROACH
----------------------------------------------------
Intuition:
- We are given dimensions of matrices in array `arr`
- Matrix Ai has dimensions: arr[i-1] x arr[i]
- We try every possible partition k between i and j
- Cost = cost(left part) + cost(right part) + cost of multiplying results
----------------------------------------------------
*/

int matrix_chain_mul_rec(int i, int j, vector<int>& arr) {
    // Base case: single matrix → no multiplication needed
    if (i == j) return 0;

    int mini = 1e9;

    // Try all possible partitions
    for (int k = i; k < j; k++) {
        int steps =
            arr[i - 1] * arr[k] * arr[j] +   // cost of current multiplication
            matrix_chain_mul_rec(i, k, arr) +
            matrix_chain_mul_rec(k + 1, j, arr);

        mini = min(mini, steps);
    }

    return mini;
}

/*
----------------------------------------------------
MEMOIZATION (TOP-DOWN DP)
----------------------------------------------------
Intuition:
- Same recursion, but store answers of subproblems
- Avoid recomputation of overlapping subproblems
----------------------------------------------------
*/

int matrix_chain_mul_mem(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
    if (i == j) return 0;

    // If already computed
    if (dp[i][j] != -1) return dp[i][j];

    int mini = 1e9;

    for (int k = i; k < j; k++) {
        int steps =
            arr[i - 1] * arr[k] * arr[j] +
            matrix_chain_mul_mem(i, k, arr, dp) +
            matrix_chain_mul_mem(k + 1, j, arr, dp);

        mini = min(mini, steps);
    }

    return dp[i][j] = mini;
}

/*
----------------------------------------------------
TABULATION (BOTTOM-UP DP)
----------------------------------------------------
Intuition:
- dp[i][j] = minimum cost to multiply matrices i to j
- Build solution for smaller chains first
- Length of chain increases gradually
----------------------------------------------------
*/

int matrix_chain_mul_tabu(vector<int>& arr) {
    int n = arr.size();

    // dp[i][j] → min cost to multiply matrices from i to j
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // i moves from bottom to top
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j < n; j++) {
            int mini = 1e9;

            for (int k = i; k < j; k++) {
                int steps =
                    arr[i - 1] * arr[k] * arr[j] +
                    dp[i][k] +
                    dp[k + 1][j];

                mini = min(mini, steps);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][n - 1];
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
*/

int main() {
    vector<int> arr = {10, 20, 30, 40, 50};
    int n = arr.size();

    cout << "Recursive Answer: "
         << matrix_chain_mul_rec(1, n - 1, arr) << endl;

    vector<vector<int>> dp(n, vector<int>(n, -1));
    cout << "Memoization Answer: "
         << matrix_chain_mul_mem(1, n - 1, arr, dp) << endl;

    cout << "Tabulation Answer: "
         << matrix_chain_mul_tabu(arr) << endl;

    return 0;
}
