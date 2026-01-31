#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    MEMOIZATION (Top-Down DP)

    Intuition:
    - At every index `ind`, we have two choices:
        1. Do NOT take arr[ind]
        2. Take arr[ind] (only if it's greater than previous taken element)

    State:
    ind      → current index
    prevind  → index of previous element taken (-1 if none)
    dp[ind][prevind+1] → LIS length from index ind

    Why prevind+1?
    - prevind ranges from -1 to n-1
    - shifting by +1 allows 0-based indexing in dp
------------------------------------------------------*/

int longest_inc_subseq_memo(
    int ind,
    int prevind,
    vector<int>& arr,
    int n,
    vector<vector<int>>& dp
) {
    if (ind == n) return 0;

    if (dp[ind][prevind + 1] != -1)
        return dp[ind][prevind + 1];

    // Option 1: Do not take current element
    int len = longest_inc_subseq_memo(ind + 1, prevind, arr, n, dp);

    // Option 2: Take current element if valid
    if (prevind == -1 || arr[ind] > arr[prevind]) {
        len = max(len,
                  1 + longest_inc_subseq_memo(ind + 1, ind, arr, n, dp));
    }

    return dp[ind][prevind + 1] = len;
}

/*------------------------------------------------------
    TABULATION (Bottom-Up DP)

    dp[ind][prevind+1] → LIS starting from index ind

    We fill table from bottom (ind = n-1 → 0)
------------------------------------------------------*/

int longest_inc_subseq_tabu(vector<int>& arr, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int ind = n - 1; ind >= 0; ind--) {
        for (int prevind = ind - 1; prevind >= -1; prevind--) {
            int len = dp[ind + 1][prevind + 1];

            if (prevind == -1 || arr[ind] > arr[prevind]) {
                len = max(len, 1 + dp[ind + 1][ind + 1]);
            }

            dp[ind][prevind + 1] = len;
        }
    }
    return dp[0][0];
}

/*------------------------------------------------------
    TABULATION WITH SPACE OPTIMIZATION

    Uses two 1D arrays instead of 2D dp table
------------------------------------------------------*/

int longest_inc_subseq_tabu_so(vector<int>& arr, int n) {
    vector<int> next(n + 1, 0), curr(n + 1, 0);

    for (int ind = n - 1; ind >= 0; ind--) {
        for (int prevind = ind - 1; prevind >= -1; prevind--) {
            int len = next[prevind + 1];

            if (prevind == -1 || arr[ind] > arr[prevind]) {
                len = max(len, 1 + next[ind + 1]);
            }

            curr[prevind + 1] = len;
        }
        next = curr;
    }
    return next[0];
}

/*------------------------------------------------------
    OPTIMAL O(N^2) DP APPROACH

    dp[i] → LIS ending at index i

    For every element, check all previous elements
------------------------------------------------------*/

int longest_inc_subseq_optimal(vector<int>& arr, int n) {
    vector<int> dp(n, 1);
    int maxi = 1;

    for (int ind = 0; ind < n; ind++) {
        for (int prev = 0; prev < ind; prev++) {
            if (arr[ind] > arr[prev]) {
                dp[ind] = max(dp[ind], 1 + dp[prev]);
            }
        }
        maxi = max(maxi, dp[ind]);
    }
    return maxi;
}

/*------------------------------------------------------
    MAIN FUNCTION
------------------------------------------------------*/

int main() {
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = arr.size();

    // Memoization
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    cout << "LIS (Memoization): "
         << longest_inc_subseq_memo(0, -1, arr, n, dp) << endl;

    // Tabulation
    cout << "LIS (Tabulation): "
         << longest_inc_subseq_tabu(arr, n) << endl;

    // Space Optimized Tabulation
    cout << "LIS (Space Optimized): "
         << longest_inc_subseq_tabu_so(arr, n) << endl;

    // Optimal O(N^2)
    cout << "LIS (Optimal O(N^2)): "
         << longest_inc_subseq_optimal(arr, n) << endl;

    return 0;
}
