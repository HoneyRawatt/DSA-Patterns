#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------
    LCS – LONGEST COMMON SUBSEQUENCE
---------------------------------------------
Intuition:
- If two characters match → we take them and move both pointers.
- If not → we try skipping one char from either string and take the maximum.
- Classic DP because two choices at each position → overlapping subproblems.
---------------------------------------------
*/



/*------------------------------------------------------
    1) MEMOIZATION (Top-Down DP)
    Time Complexity:  O(n*m)
    Space Complexity: O(n*m) + recursion stack
-------------------------------------------------------*/
int lcs_memo(int i, int j, string &s1, string &s2, vector<vector<int>>& dp)
{
    // Base: if any index goes negative → no LCS
    if (i < 0 || j < 0)
        return 0;

    // If already calculated
    if (dp[i][j] != -1)
        return dp[i][j];

    // If current characters match → include & move both back
    if (s1[i] == s2[j])
        return dp[i][j] = 1 + lcs_memo(i - 1, j - 1, s1, s2, dp);

    // Else: try skipping one char from either string
    return dp[i][j] = max(
        lcs_memo(i - 1, j, s1, s2, dp),
        lcs_memo(i, j - 1, s1, s2, dp)
    );
}



/*------------------------------------------------------
    2) TABULATION (Bottom-Up DP)
    Time Complexity:  O(n*m)
    Space Complexity: O(n*m)
-------------------------------------------------------*/
int lcs_tabu(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    // dp[i][j] = LCS of s1[0..i-1] & s2[0..j-1]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Build table bottom-up
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // Char match → take diagonal + 1
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];

            // Else take maximum of skipping from s1 or s2
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n][m];
}



/*------------------------------------------------------
    3) SPACE-OPTIMIZED TABULATION (Only 1 row)
    Time Complexity:  O(n*m)
    Space Complexity: O(m)
-------------------------------------------------------*/
int lcs_tabu_so(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }

        // Move curr → prev
        prev = curr;
    }

    return prev[m];
}



/*------------------------------------------------------
                    MAIN FUNCTION
-------------------------------------------------------*/
int main()
{
    string s1 = "abcde";
    string s2 = "ace";

    int n = s1.size(), m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    cout << "LCS (Memoization):        " 
         << lcs_memo(n - 1, m - 1, s1, s2, dp) << endl;

    cout << "LCS (Tabulation):         " 
         << lcs_tabu(s1, s2) << endl;

    cout << "LCS (Space Optimized):    " 
         << lcs_tabu_so(s1, s2) << endl;

    return 0;
}
