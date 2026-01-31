#include <bits/stdc++.h>
using namespace std;


//use double if long long get overflow because the long long range 10^18  but the double range 10^308
/*
-----------------------------------------
INTUITION:
Count how many distinct subsequences of S match string T.
We try to match characters going backwards. 
If chars match → We have 2 choices:
    1) Take the match
    2) Skip the char in S
Else → Only option: skip S[i]

This forms a DP similar to LCS but counting combinations.

-----------------------------------------
TIME COMPLEXITY:
• Memoization:  O(n*m)
• Tabulation:   O(n*m)
• Space-Opt-1D: O(n*m) → O(m)

SPACE COMPLEXITY:
• Memo      : O(n*m)
• Tabu      : O(n*m)
• SO-2Row   : O(m)
• SO-1Row   : O(m)
-----------------------------------------
*/

// ---------------- MEMOIZATION ----------------
long long distinct_subseq_memo(int i, int j, string &s, string &t,
                               vector<vector<long long>> &dp)
{
    if (j < 0) return 1;      // matched whole T
    if (i < 0) return 0;      // exhausted S but T not matched
    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == t[j]) {
        // take + skip
        return dp[i][j] = distinct_subseq_memo(i-1, j-1, s, t, dp)
                        + distinct_subseq_memo(i-1, j, s, t, dp);
    }
    else {
        return dp[i][j] = distinct_subseq_memo(i-1, j, s, t, dp);
    }
}

// ---------------- TABULATION ----------------
long long distinct_subseq_tabu(string &s, string &t)
{
    int n = s.size(), m = t.size();
    vector<vector<long long>> dp(n+1, vector<long long>(m+1, 0));

    // Base case: empty T ⇒ 1 subsequence always
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][m];
}

// ---------------- SPACE OPTIMIZED (2 ROWS) ----------------
long long distinct_subseq_tabu_so(string &s, string &t)
{
    int n = s.size(), m = t.size();
    vector<long long> prev(m+1, 0), curr(m+1, 0);

    prev[0] = 1; // empty T

    for (int i = 1; i <= n; i++)
    {
        curr[0] = 1; // empty T
        for (int j = 1; j <= m; j++)
        {
            if (s[i-1] == t[j-1])
                curr[j] = prev[j-1] + prev[j];
            else
                curr[j] = prev[j];
        }
        prev = curr;
    }
    return prev[m];
}

// ---------------- SPACE OPTIMIZED (1 ROW REVERSE LOOP) ----------------
long long distinct_subseq_tabu_more_so(string &s, string &t)
{
    int n = s.size(), m = t.size();
    vector<long long> dp(m+1, 0);

    dp[0] = 1; // empty T

    for (int i = 1; i <= n; i++)
    {
        // traverse backward to avoid overwriting needed values
        for (int j = m; j >= 1; j--)
        {
            if (s[i-1] == t[j-1])
                dp[j] = dp[j] + dp[j-1];
        }
    }
    return dp[m];
}

// -------------------- MAIN --------------------
int main()
{
    string s, t;
    cout << "Enter string S: ";
    cin >> s;
    cout << "Enter string T: ";
    cin >> t;

    int n = s.size(), m = t.size();

    // memo
    vector<vector<long long>> dp(n, vector<long long>(m, -1));
    cout << "Memoization result: " 
         << distinct_subseq_memo(n-1, m-1, s, t, dp) << "\n";

    // tabulation
    cout << "Tabulation result: " 
         << distinct_subseq_tabu(s, t) << "\n";

    // space optimized - 2 row
    cout << "Space Optimized (2-row): " 
         << distinct_subseq_tabu_so(s, t) << "\n";

    // space optimized - 1 row
    cout << "Space Optimized (1-row): " 
         << distinct_subseq_tabu_more_so(s, t) << "\n";

    return 0;
}
