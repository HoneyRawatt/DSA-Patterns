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
int best_timeto_buy_sell_memo(int ind, int buy,
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
            -price[ind] + best_timeto_buy_sell_memo(ind + 1, 0, price, dp, n), // buy
             0 + best_timeto_buy_sell_memo(ind + 1, 1, price, dp, n)           // not buy
        );
    }
    else
    {
        profit = max(
            price[ind] + best_timeto_buy_sell_memo(ind + 1, 1, price, dp, n), // sell
            0 + best_timeto_buy_sell_memo(ind + 1, 0, price, dp, n)           // not sell
        );
    }

    return dp[ind][buy] = profit;
}

/*------------------------------------------------------
    TABULATION (Bottom-Up DP)

    Time Complexity:  O(n * 2)
    Space Complexity: O(n * 2)
-------------------------------------------------------*/
int best_timeto_buy_sell_tabu(vector<int>& price)
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
                    price[i] + dp[i + 1][1], // sell
                    dp[i + 1][0]              // not sell
                );
            }
        }
    }

    return dp[0][1];
}

/*------------------------------------------------------
    SPACE OPTIMIZED TABULATION

    Optimization:
    - Only next day values are required
    - Use two arrays: ahead & curr

    Time Complexity:  O(n * 2)
    Space Complexity: O(2)
-------------------------------------------------------*/
int best_timeto_buy_sell_tabu_so(vector<int>& price)
{
    int n = price.size();
    vector<long> ahead(2, 0), curr(2, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            if (buy)
            {
                curr[buy] = max(
                    -price[i] + ahead[0], //buy
                     ahead[1]             //not buy
                );
            }
            else
            {
                curr[buy] = max(
                    price[i] + ahead[1],  //sell
                    ahead[0]              //not sell
                );
            }
        }
        ahead = curr;
    }

    return ahead[1];
}

/*------------------------------------------------------
    MAIN FUNCTION
-------------------------------------------------------*/
int main()
{
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    int n = prices.size();
    vector<vector<long>> dp(n, vector<long>(2, -1));

    cout << "Memoization Profit: "
         << best_timeto_buy_sell_memo(0, 1, prices, dp, n) << endl;

    cout << "Tabulation Profit: "
         << best_timeto_buy_sell_tabu(prices) << endl;

    cout << "Space Optimized Profit: "
         << best_timeto_buy_sell_tabu_so(prices) << endl;

    return 0;
}
