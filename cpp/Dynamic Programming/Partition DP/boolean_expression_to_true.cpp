#include <bits/stdc++.h>
using namespace std;

#define ll long long
int mod = 1000000007;

/*
----------------------------------------------------
MEMOIZATION (TOP-DOWN DP)
----------------------------------------------------
Intuition:
- We try every operator `ind` between i and j as the LAST operator
- Count number of ways left & right can be True/False
- Combine them based on operator (&, |, ^)
- dp[i][j][isTrue] = number of ways expression [i..j] evaluates to isTrue
----------------------------------------------------
Time Complexity: O(n^3)
Space Complexity: O(n^2 * 2) + recursion stack
----------------------------------------------------
*/

ll boolean_expr_totrue_memo(int i, int j, int isTrue,
                            string& exp,
                            vector<vector<vector<ll>>>& dp) {

    // Invalid range
    if (i > j) return 0;

    // Single operand
    if (i == j) {
        if (isTrue) return exp[i] == 'T';
        else        return exp[i] == 'F';
    }

    if (dp[i][j][isTrue] != -1)
        return dp[i][j][isTrue];

    ll ways = 0;

    // Operators are at odd indices
    for (int ind = i + 1; ind <= j - 1; ind += 2) {

        ll lt = boolean_expr_totrue_memo(i, ind - 1, 1, exp, dp);
        ll lf = boolean_expr_totrue_memo(i, ind - 1, 0, exp, dp);
        ll rt = boolean_expr_totrue_memo(ind + 1, j, 1, exp, dp);
        ll rf = boolean_expr_totrue_memo(ind + 1, j, 0, exp, dp);

        if (exp[ind] == '&') {
            if (isTrue)
                ways = (ways + lt * rt) % mod;
            else
                ways = (ways + lt * rf + lf * rt + lf * rf) % mod;
        }
        else if (exp[ind] == '|') {
            if (isTrue)
                ways = (ways + lt * rt + lt * rf + lf * rt) % mod;
            else
                ways = (ways + lf * rf) % mod;
        }
        else { // XOR (^)
            if (isTrue)
                ways = (ways + lt * rf + lf * rt) % mod;
            else
                ways = (ways + lt * rt + lf * rf) % mod;
        }
    }

    return dp[i][j][isTrue] = ways;
}

/*
----------------------------------------------------
TABULATION (BOTTOM-UP DP)
----------------------------------------------------
Intuition:
- Same logic as memo, but fill dp table iteratively
- i goes backward, j goes forward
----------------------------------------------------
Time Complexity: O(n^3)
Space Complexity: O(n^2 * 2)
----------------------------------------------------
*/

ll boolean_expr_totrue_tabu(string& exp) {
    int n = exp.size();
    vector<vector<vector<ll>>> dp(
        n, vector<vector<ll>>(n, vector<ll>(2, 0)));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {

            // Base case
            if (i == j) {
                dp[i][j][1] = (exp[i] == 'T');
                dp[i][j][0] = (exp[i] == 'F');
                continue;
            }

            for (int isTrue = 0; isTrue <= 1; isTrue++) {
                ll ways = 0;

                for (int ind = i + 1; ind <= j - 1; ind += 2) {

                    ll lt = dp[i][ind - 1][1];
                    ll lf = dp[i][ind - 1][0];
                    ll rt = dp[ind + 1][j][1];
                    ll rf = dp[ind + 1][j][0];

                    if (exp[ind] == '&') {
                        if (isTrue)
                            ways = (ways + lt * rt) % mod;
                        else
                            ways = (ways + lt * rf + lf * rt + lf * rf) % mod;
                    }
                    else if (exp[ind] == '|') {
                        if (isTrue)
                            ways = (ways + lt * rt + lt * rf + lf * rt) % mod;
                        else
                            ways = (ways + lf * rf) % mod;
                    }
                    else { // XOR (^)
                        if (isTrue)
                            ways = (ways + lt * rf + lf * rt) % mod;
                        else
                            ways = (ways + lt * rt + lf * rf) % mod;
                    }
                }

                dp[i][j][isTrue] = ways;
            }
        }
    }

    return dp[0][n - 1][1];
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
*/

int main() {
    string exp = "T|T&F^T";
    int n = exp.size();

    vector<vector<vector<ll>>> dp(
        n, vector<vector<ll>>(n, vector<ll>(2, -1)));

    cout << "Memoization Answer: "
         << boolean_expr_totrue_memo(0, n - 1, 1, exp, dp) << endl;

    cout << "Tabulation Answer: "
         << boolean_expr_totrue_tabu(exp) << endl;

    return 0;
}
