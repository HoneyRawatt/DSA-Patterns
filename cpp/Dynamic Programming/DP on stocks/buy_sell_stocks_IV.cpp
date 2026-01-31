#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    MEMOIZATION – Buy & Sell Stock IV (k transactions)

    State:
    ind     → current day
    tranno  → transaction number (0 to 2*k)
    dp[ind][tranno] → max profit from day ind

    Intuition:
    - Even tranno → BUY
    - Odd tranno  → SELL

    Time Complexity:  O(n * 2k)
    Space Complexity: O(n * 2k) + recursion stack
-------------------------------------------------------*/
int buy_sell_stocksIV_memo(int ind, int tranno,
                           vector<int>& prices, int n, int k,
                           vector<vector<int>>& dp)
{
    if (ind == n || tranno == 2 * k)
        return 0;

    if (dp[ind][tranno] != -1)
        return dp[ind][tranno];

    if (tranno % 2 == 0)
    {
        // BUY
        return dp[ind][tranno] = max(
            -prices[ind] + buy_sell_stocksIV_memo(ind + 1, tranno + 1, prices, n, k, dp),
             buy_sell_stocksIV_memo(ind + 1, tranno, prices, n, k, dp)
        );
    }
    else
    {
        // SELL
        return dp[ind][tranno] = max(
            prices[ind] + buy_sell_stocksIV_memo(ind + 1, tranno + 1, prices, n, k, dp),
            buy_sell_stocksIV_memo(ind + 1, tranno, prices, n, k, dp)
        );
    }
}

/*------------------------------------------------------
    TABULATION – Buy & Sell Stock IV

    Time Complexity:  O(n * 2k)
    Space Complexity: O(n * 2k)
-------------------------------------------------------*/
int buy_sell_stocksIV_tabu(vector<int>& prices, int k)
{
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int tranno = 2 * k - 1; tranno >= 0; tranno--)
        {
            if (tranno % 2 == 0)
            {
                dp[ind][tranno] = max(
                    -prices[ind] + dp[ind + 1][tranno + 1],
                     dp[ind + 1][tranno]
                );
            }
            else
            {
                dp[ind][tranno] = max(
                    prices[ind] + dp[ind + 1][tranno + 1],
                    dp[ind + 1][tranno]
                );
            }
        }
    }
    return dp[0][0];
}

/*------------------------------------------------------
    SPACE OPTIMIZED TABULATION

    Time Complexity:  O(n * 2k)
    Space Complexity: O(2k)
-------------------------------------------------------*/
int buy_sell_stocksIV_tabu_so(vector<int>& prices, int k)
{
    int n = prices.size();
    vector<int> after(2 * k + 1, 0), curr(2 * k + 1, 0);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int tranno = 2 * k - 1; tranno >= 0; tranno--)
        {
            if (tranno % 2 == 0)
            {
                curr[tranno] = max(
                    -prices[ind] + after[tranno + 1],
                     after[tranno]
                );
            }
            else
            {
                curr[tranno] = max(
                    prices[ind] + after[tranno + 1],
                    after[tranno]
                );
            }
        }
        after = curr;
    }
    return after[0];
}

int main()
{
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2 * k, -1));

    cout << "Memoization Profit: "
         << buy_sell_stocksIV_memo(0, 0, prices, n, k, dp) << endl;

    cout << "Tabulation Profit: "
         << buy_sell_stocksIV_tabu(prices, k) << endl;

    cout << "Space Optimized Profit: "
         << buy_sell_stocksIV_tabu_so(prices, k) << endl;

    return 0;
}
