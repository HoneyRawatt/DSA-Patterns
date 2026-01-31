#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------
MEMOIZATION (TOP-DOWN)
----------------------------------------------------
Intuition:
- Assume we burst balloon `ind` LAST in range [i..j]
- Then neighbors are fixed: a[i-1] and a[j+1]
- Try all possible last balloons
----------------------------------------------------
*/

int maxCoins_memo(int i, int j, vector<int>& a,
                  vector<vector<int>>& dp) {
    if (i > j) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    int maxi = INT_MIN;

    for (int ind = i; ind <= j; ind++) {
        int cost =
            a[i - 1] * a[ind] * a[j + 1] +
            maxCoins_memo(i, ind - 1, a, dp) +
            maxCoins_memo(ind + 1, j, a, dp);

        maxi = max(maxi, cost);
    }

    return dp[i][j] = maxi;
}

/*
----------------------------------------------------
TABULATION (BOTTOM-UP)
----------------------------------------------------
*/

int maxCoins_tabu(vector<int>& a, int n) {
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if(i>j) continue;   // also u remove this annd run the loop of j=i -- same thing 
            int maxi = INT_MIN;

            for (int ind = i; ind <= j; ind++) {
                int cost =
                    a[i - 1] * a[ind] * a[j + 1] +
                    dp[i][ind - 1] +
                    dp[ind + 1][j];

                maxi = max(maxi, cost);
            }

            dp[i][j] = maxi;
        }
    }

    return dp[1][n];
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
*/

int main() {
    vector<int> a = {3, 1, 5, 8};

    int n = a.size();

    // Add boundaries
    a.push_back(1);
    a.insert(a.begin(), 1);

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));

    cout << "Memoization Answer: "
         << maxCoins_memo(1, n, a, dp) << endl;

    cout << "Tabulation Answer: "
         << maxCoins_tabu(a, n) << endl;

    return 0;
}
