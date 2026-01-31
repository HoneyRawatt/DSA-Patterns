#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
/*
    GOAL:
    Count the number of subsets whose sum equals TARGET.

    We use 3 methods:
    1) Memoization (Top-Down DP)
    2) Tabulation (Bottom-Up DP)
    3) Space Optimized DP
*/
//////////////////////////////////////////////////////////
// 1) MEMOIZATION
// Time: O(n × target)
// Space:
// Recursion stack: O(n)
// DP table: O(n × target)
//////////////////////////////////////////////////////////
long long noofsubset_memo(int ind, int target, vector<int> &arr,vector<vector<long long>> &dp)
{
    if (ind == 0)
    {
        if (target == 0 && arr[0] == 0) return 2;  // { } , {0}
        if (target == 0) return 1;                // empty subset
        return (arr[0] == target) ? 1 : 0;        // take arr[0] or not
    }

    if (dp[ind][target] != -1) return dp[ind][target];

    long long notTake = noofsubset_memo(ind - 1, target, arr, dp);

    long long take = 0;
    if (arr[ind] <= target)
        take = noofsubset_memo(ind - 1, target - arr[ind], arr, dp);

    return dp[ind][target] = (take + notTake) % MOD;
}

//////////////////////////////////////////////////////////
// 2) TABULATION
// Time: O(n × target)
// Space: O(n × target)
//////////////////////////////////////////////////////////

long long noofsubset_tabu(vector<int> &arr, int target, int n)
{
    vector<vector<long long>> dp(n, vector<long long>(target + 1, 0));

    // Base case
    if (arr[0] == 0)
        dp[0][0] = 2;   // include or exclude zero
    else
        dp[0][0] = 1;

    if (arr[0] != 0 && arr[0] <= target)
        dp[0][arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int s = 0; s <= target; s++)
        {
            long long notTake = dp[i - 1][s];

            long long take = 0;
            if (arr[i] <= s)
                take = dp[i - 1][s - arr[i]];

            dp[i][s] = (take + notTake) % MOD;
        }
    }

    return dp[n - 1][target];
}

//////////////////////////////////////////////////////////
// 3) SPACE OPTIMIZED DP
// Time: O(n × target)
// Space: O(target) only ✔
//////////////////////////////////////////////////////////


long long noofsubset_so(vector<int> &arr, int target, int n)
{
    vector<long long> prev(target + 1, 0), curr(target + 1, 0);

    // Base case
    if (arr[0] == 0)
        prev[0] = 2; // {} and {0}
    else
        prev[0] = 1;

    if (arr[0] != 0 && arr[0] <= target)
        prev[arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
        curr[0] = (arr[i] == 0 ? (prev[0] * 2) % MOD : prev[0]);

        for (int s = 0; s <= target; s++)
        {
            long long notTake = prev[s];

            long long take = 0;
            if (arr[i] <= s)
                take = prev[s - arr[i]];

            curr[s] = (take + notTake) % MOD;
        }

        prev = curr;
    }

    return prev[target];
}

//////////////////////////////////////////////////////////
// MAIN FUNCTION
//////////////////////////////////////////////////////////

int main()
{
    vector<int> arr = {2, 4, 4, 6};
    int target = 6;
    int n = arr.size();

    // Memoization Call
    vector<vector<long long>> dp(n, vector<long long>(target + 1, -1));
    long long ans1 = noofsubset_memo(n - 1, target, arr, dp);

    // Tabulation Call
    long long ans2 = noofsubset_tabu(arr, target, n);

    // Space Optimized Call
    long long ans3 = noofsubset_so(arr, target, n);

    cout << "Count (Memoization): " << ans1 << "\n";
    cout << "Count (Tabulation): " << ans2 << "\n";
    cout << "Count (Space Optimized): " << ans3 << "\n";

    return 0;
}
