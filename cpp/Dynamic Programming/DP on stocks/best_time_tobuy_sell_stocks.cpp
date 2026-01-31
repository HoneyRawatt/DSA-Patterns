#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    BEST TIME TO BUY AND SELL STOCK (Single Transaction)

    Intuition:
    - We want to buy at the minimum price seen so far.
    - For every day, calculate profit if we sell today.
    - Track the maximum profit achievable.
    - Update minimum price whenever we find a smaller value.

    Time Complexity:  O(n)
        → Single pass through the array

    Space Complexity: O(1)
        → Only constant extra variables used
-------------------------------------------------------*/
int best_time_tobuy_sell_stock(vector<int>& arr)
{
    int n = arr.size();

    int mini = arr[0];   // minimum price to buy so far
    int profit = 0;      // maximum profit

    for (int i = 1; i < n; i++)
    {
        int cost = arr[i] - mini;    // profit if sold today
        profit = max(profit, cost);  // update max profit
        mini = min(mini, arr[i]);    // update min price
    }

    return profit;
}

int main()
{
    /* Example Input:
       Prices represent stock price on each day
    */
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    int maxProfit = best_time_tobuy_sell_stock(prices);

    cout << "Maximum Profit: " << maxProfit << endl;

    return 0;
}
