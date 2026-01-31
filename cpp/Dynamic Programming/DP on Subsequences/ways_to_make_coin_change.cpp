#include <bits/stdc++.h>
using namespace std;

/*
    ===================== INTUITION =====================
    We must count the number of ways to make "target" using coins.
    Each coin can be used infinite times → Unbounded Knapsack.

    DP state:
    dp[i][T] = number of ways to make sum T using coins[0..i]

    Transitions:
    - notTake: dp[i-1][T]
    - take:    dp[i][T - coin[i]]   (because coin can be reused)

    ======================================================
    TIME COMPLEXITY:
        Memoization:  O(n * target)
        Tabulation:   O(n * target)
        Space Opt:    O(target)

    SPACE COMPLEXITY:
        Memoization:  O(n * target) + recursion stack
        Tabulation:   O(n * target)
        Space Opt:    O(target)
    ======================================================
*/


/*********************************************************
 ******************* 1. MEMOIZATION DP *******************
 *********************************************************/
long countWaysToMakeChange_memo(int ind, int *a, int target,
                                vector<vector<long>> &dp)
{
    // Base Case: Only coin 0 available
    if (ind == 0)
        return (target % a[0] == 0);

    if (dp[ind][target] != -1)
        return dp[ind][target];

    long notTake = countWaysToMakeChange_memo(ind - 1, a, target, dp);

    long take = 0;
    if (a[ind] <= target)
        take = countWaysToMakeChange_memo(ind, a, target - a[ind], dp);

    return dp[ind][target] = take + notTake;
}


/*********************************************************
 ******************* 2. TABULATION DP ********************
 *********************************************************/
long countWaysToMakeChange_tabu(int *a, int n, int target)
{
    vector<vector<long>> dp(n, vector<long>(target + 1, 0));

    // Base row (only coin 0)
    for (int T = 0; T <= target; T++)
        dp[0][T] = (T % a[0] == 0);

    for (int i = 1; i < n; i++)
    {
        for (int T = 0; T <= target; T++)
        {
            long notTake = dp[i - 1][T];

            long take = 0;
            if (a[i] <= T)
                take = dp[i][T - a[i]];

            dp[i][T] = take + notTake;
        }
    }

    return dp[n - 1][target];
}


/*********************************************************
 ********* 3. SPACE OPTIMIZED (2 ROWS) DP ****************
 *********************************************************/
long countWaysToMakeChange_so(int *a, int n, int target)
{
    vector<long> prev(target + 1, 0), curr(target + 1, 0);

    // Base
    for (int T = 0; T <= target; T++)
        prev[T] = (T % a[0] == 0);

    for (int i = 1; i < n; i++)
    {
        for (int T = 0; T <= target; T++)
        {
            long notTake = prev[T];
            long take = 0;

            if (a[i] <= T)
                take = curr[T - a[i]];

            curr[T] = take + notTake;
        }
        prev = curr;
    }

    return prev[target];
}


/*********************************************************
 *********************** MAIN *****************************
 *********************************************************/
int main()
{
    int a[] = {1, 2, 3};
    int n = 3;
    int target = 4;

    // MEMOIZATION
    vector<vector<long>> dp(n, vector<long>(target + 1, -1));
    long ans1 = countWaysToMakeChange_memo(n - 1, a, target, dp);

    // TABULATION
    long ans2 = countWaysToMakeChange_tabu(a, n, target);

    // SPACE OPTIMIZED
    long ans3 = countWaysToMakeChange_so(a, n, target);

    cout << "Ways (Memoization):     " << ans1 << endl;
    cout << "Ways (Tabulation):      " << ans2 << endl;
    cout << "Ways (Space Optimized): " << ans3 << endl;

    return 0;
}
