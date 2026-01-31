#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    MEMOIZATION (Top-Down DP)

    State:
    ind  → current day
    buy  → 1 = can buy, 0 = must sell
    dp[ind][buy] → maximum profit from day ind onwards

    Intuition:
    - If buy == 1:
        Option 1: Buy today → -price[ind] + solve(ind+1, 0)
        Option 2: Skip today
    - If buy == 0:
        Option 1: Sell today → +price[ind] + solve(ind+1, 1)
        Option 2: Skip today

    Time Complexity:  O(n * 2)
    Space Complexity: O(n * 2) + O(n) recursion stack
-------------------------------------------------------*/
int best_timeto_buy_sell_V_memo(int ind, int buy,
                              vector<int>& price,
                              vector<vector<long>>& dp,
                              int n)
{
    if (ind == n) return 0;

    if (dp[ind][buy] != -1)
        return dp[ind][buy];

    long profit;

    if (buy)
    {
        profit = max(
            -price[ind] + best_timeto_buy_sell_V_memo(ind + 1, 0, price, dp, n), // buy
             0 + best_timeto_buy_sell_V_memo(ind + 1, 1, price, dp, n)           // not buy
        );
    }
    else
    {
        profit = max(
            price[ind] + best_timeto_buy_sell_V_memo(ind + 2, 1, price, dp, n), // sell
            0 + best_timeto_buy_sell_V_memo(ind + 1, 0, price, dp, n)           // not sell
        );
    }

    return dp[ind][buy] = profit;
}

/*------------------------------------------------------
    TABULATION (Bottom-Up DP)

    Time Complexity:  O(n * 2)
    Space Complexity: O(n * 2)
-------------------------------------------------------*/
int best_timeto_buy_sell_V_tabu(vector<int>& price)
{
    int n = price.size();
    vector<vector<long>> dp(n + 1, vector<long>(2, 0));

    // dp[n][0] = dp[n][1] = 0 → already initialized

    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            if (buy)
            {
                dp[i][buy] = max(
                    -price[i] + dp[i + 1][0], // buy
                     dp[i + 1][1]              // not buy
                );
            }
            else
            {
                dp[i][buy] = max(
                    price[i] + dp[i + 2][1], // sell
                    dp[i + 1][0]              // not sell
                );
            }
        }
    }

    return dp[0][1];
}

/*------------------------------------------------------
    SPACE OPTIMIZED TABULATION (Cooldown)

    front1 → dp[i+1]
    front2 → dp[i+2]

    Time Complexity:  O(n * 2)
    Space Complexity: O(2)
-------------------------------------------------------*/
int best_timeto_buy_sell_tabu_so(vector<int>& price)
{
    int n = price.size();
    vector<long> front1(2, 0), front2(2, 0), curr(2, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        // buy = 1 → can buy
        curr[1] = max(
            -price[i] + front1[0],  // buy
             front1[1]              // not buy
        );

        // buy = 0 → can sell
        curr[0] = max(
            price[i] + front2[1],  // sell (cooldown)
            front1[0]              // not sell
        );

        front2 = front1;   // shift dp[i+2]
        front1 = curr;     // shift dp[i+1]
    }

    return front1[1];
}


