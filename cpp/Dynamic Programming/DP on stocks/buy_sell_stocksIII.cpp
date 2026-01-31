#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    MEMOIZATION (Top-Down DP)

    State:
    ind  → current day
    buy  → 1 = can buy, 0 = must sell
    cap  → remaining transactions (max = 2)

    dp[ind][buy][cap] = max profit from day ind

    Intuition:
    - If cap == 0 → no transactions left → profit = 0
    - If buy == 1:
        → Buy today OR Skip
    - If buy == 0:
        → Sell today (cap--) OR Skip

    Time Complexity:  O(n * 2 * 3)
    Space Complexity: O(n * 2 * 3) + recursion stack
-------------------------------------------------------*/
int best_timeto_buy_sell_memo(int ind, int buy, int cap,
                              vector<int>& price,
                              vector<vector<vector<int>>>& dp,
                              int n)
{
    if (ind == n || cap == 0) return 0;

    if (dp[ind][buy][cap] != -1)
        return dp[ind][buy][cap];

    if (buy)
    {
        return dp[ind][buy][cap] = max(
            -price[ind] + best_timeto_buy_sell_memo(ind + 1, 0, cap, price, dp, n), // buy
             0 + best_timeto_buy_sell_memo(ind + 1, 1, cap, price, dp, n)           // not buy
        );
    }
    else
    {
        return dp[ind][buy][cap] = max(
            price[ind] + best_timeto_buy_sell_memo(ind + 1, 1, cap - 1, price, dp, n), // sell
            0 + best_timeto_buy_sell_memo(ind + 1, 0, cap, price, dp, n)               // not sell
        );
    }
}

/*------------------------------------------------------
    TABULATION (Bottom-Up DP)

    Time Complexity:  O(n * 2 * 3)
    Space Complexity: O(n * 2 * 3)
-------------------------------------------------------*/
int best_timeto_buy_sell_tabu(vector<int>& price)
{
    int n = price.size();
    vector<vector<vector<int>>> dp(n + 1,
        vector<vector<int>>(2, vector<int>(3, 0)));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= 2; cap++)
            {
                if (buy)
                {
                    dp[i][buy][cap] = max(
                        -price[i] + dp[i + 1][0][cap],
                        dp[i + 1][1][cap]
                    );
                }
                else
                {
                    dp[i][buy][cap] = max(
                        price[i] + dp[i + 1][1][cap - 1],
                        dp[i + 1][0][cap]
                    );
                }
            }
        }
    }
    return dp[0][1][2];
}

/*------------------------------------------------------
    SPACE OPTIMIZED TABULATION

    Optimization:
    - Only next day state is required

    Time Complexity:  O(n * 2 * 3)
    Space Complexity: O(2 * 3)
-------------------------------------------------------*/
int best_timeto_buy_sell_tabu_so(vector<int>& price)
{
    int n = price.size();
    vector<vector<int>> after(2, vector<int>(3, 0));
    vector<vector<int>> curr(2, vector<int>(3, 0));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= 2; cap++)
            {
                if (buy)
                {
                    curr[buy][cap] = max(
                        -price[i] + after[0][cap],
                        after[1][cap]
                    );
                }
                else
                {
                    curr[buy][cap] = max(
                        price[i] + after[1][cap - 1],
                        after[0][cap]
                    );
                }
            }
        }
        after = curr;
    }
    return after[1][2];
}

/*------------------------------------------------------
    MAIN FUNCTION
-------------------------------------------------------*/
int main()
{
    vector<int> prices = {3,3,5,0,0,3,1,4};

    int n = prices.size();
    vector<vector<vector<int>>> dp(n,
        vector<vector<int>>(2, vector<int>(3, -1)));

    cout << "Memoization Profit: "
         << best_timeto_buy_sell_memo(0, 1, 2, prices, dp, n) << endl;

    cout << "Tabulation Profit: "
         << best_timeto_buy_sell_tabu(prices) << endl;

    cout << "Space Optimized Profit: "
         << best_timeto_buy_sell_tabu_so(prices) << endl;

    return 0;
}



//another logic 
int maxProfit(vector<int>& prices) {
        int buy1 = INT_MAX, buy2 = INT_MAX;
        int sell1 = 0, sell2 = 0;

        for (int i = 0; i < prices.size(); i++) {
            buy1 = min(buy1, prices[i]);
            sell1 = max(sell1, prices[i] - buy1);
            buy2 = min(buy2, prices[i] - sell1);
            sell2 = max(sell2, prices[i] - buy2);
        }

        return sell2;
}
