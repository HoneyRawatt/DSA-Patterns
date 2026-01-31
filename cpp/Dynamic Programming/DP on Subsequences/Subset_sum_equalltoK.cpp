#include <bits/stdc++.h>
using namespace std;

/*-----------------------------------------------------------
    🔹 INTUITION — SUBSET SUM TO K
    We want to check if there exists a subsequence whose
    elements add up to exactly K.

    At every index, we have 2 choices:
        1. NOT TAKE    → move to previous index, target unchanged
        2. TAKE        → move to previous index, target reduces by arr[ind]

    Base cases:
        - If target == 0 → subset found
        - If ind == 0 → only arr[0] can make target

-----------------------------------------------------------*/


/********************** MEMOIZATION ********************************/

bool subsetSumToK_memo(int ind, int target,
                       vector<int> &arr,
                       vector<vector<int>> &dp)
{
    // base case 1
    if (target == 0) return true;

    // base case 2
    if (ind == 0) return (arr[0] == target);

    if (dp[ind][target] != -1)
        return dp[ind][target];

    // not-take option
    bool notTake = subsetSumToK_memo(ind - 1, target, arr, dp);

    // take option
    bool take = false;
    if (arr[ind] <= target)
        take = subsetSumToK_memo(ind - 1, target - arr[ind], arr, dp);

    return dp[ind][target] = (take || notTake);
}

/*
    ⏱ TIME COMPLEXITY : O(N * K)
    📦 SPACE COMPLEXITY: O(N * K) + O(N) recursion stack
*/


/********************** TABULATION ********************************/

bool subsetSumToK_tabu(int n, int k, vector<int> &arr)
{
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

    // every index can make target = 0
    for (int i = 0; i < n; i++)
        dp[i][0] = true;

    // base case for index 0
    if (arr[0] <= k)
        dp[0][arr[0]] = true;

    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 1; target <= k; target++)
        {
            bool notTake = dp[ind - 1][target];

            bool take = false;
            if (arr[ind] <= target)
                take = dp[ind - 1][target - arr[ind]];

            dp[ind][target] = (take || notTake);
        }
    }

    return dp[n - 1][k];
}

/*
    ⏱ TIME COMPLEXITY : O(N * K)
    📦 SPACE COMPLEXITY: O(N * K)
*/


/********************** SPACE OPTIMIZED TABULATION ********************************/

bool subsetSumToK_tabu_OS(int n, int k, vector<int> &arr)
{
    vector<bool> prev(k + 1, false);
    prev[0] = true;

    if (arr[0] <= k)
        prev[arr[0]] = true;

    for (int ind = 1; ind < n; ind++)
    {
        vector<bool> curr(k + 1, false);
        curr[0] = true;

        for (int target = 1; target <= k; target++)
        {
            bool notTake = prev[target];

            bool take = false;
            if (arr[ind] <= target)
                take = prev[target - arr[ind]];

            curr[target] = (take || notTake);
        }
        prev = curr;
    }

    return prev[k];
}

/*
    ⏱ TIME COMPLEXITY : O(N * K)
    📦 SPACE COMPLEXITY: O(K)
*/

int main() {
    int n, k;
    cout << "Enter number of elements (n): ";
    cin >> n;

    cout << "Enter target sum (k): ";
    cin >> k;

    vector<int> arr(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    // ---------------- Memoization ----------------
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    bool memoAns = subsetSumToK_memo(n - 1, k, arr, dp);
    cout << "Memoization Result: "
         << (memoAns ? "YES, subset exists" : "NO subset exists") << endl;

    // ---------------- Tabulation ----------------
    bool tabuAns = subsetSumToK_tabu(n, k, arr);
    cout << "Tabulation Result: "
         << (tabuAns ? "YES, subset exists" : "NO subset exists") << endl;

    // ---------------- Space Optimized Tabulation ----------------
    bool osAns = subsetSumToK_tabu_OS(n, k, arr);
    cout << "Space Optimized Tabulation Result: "
         << (osAns ? "YES, subset exists" : "NO subset exists") << endl;

    return 0;
}
