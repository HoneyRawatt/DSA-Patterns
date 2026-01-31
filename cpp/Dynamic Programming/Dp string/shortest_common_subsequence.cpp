#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    TABULATION DP for LCS (Full DP Table)

    Intuition:
    - dp[i][j] = LCS length of:
        s1[0 .. i-1]
        s2[0 .. j-1]
    - If chars match → 1 + diagonal
    - Else → take max of removing char from either string

    Time Complexity:  O(n * m)
    Space Complexity: O(n * m)
-------------------------------------------------------*/
vector<vector<int>> lcs_tabu(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp; // return entire table (needed for SCS reconstruction)
}

/*------------------------------------------------------
    Construct Shortest Common Supersequence (SCS)
    using backtracking on the LCS dp table.

    Intuition:
    - We move from dp[n][m] → dp[0][0]
    - If characters match → include once
    - Else move in direction of larger dp value
    - After finishing one string, append the rest of the other

    Time Complexity:  O(n + m)
    Space Complexity: O(n + m)
-------------------------------------------------------*/
string shortest_common_superseq(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    // Build full LCS dp table
    vector<vector<int>> dp = lcs_tabu(s1, s2);

    string ans = "";
    int i = n, j = m;

    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            // characters match → add only once
            ans += s1[i - 1];
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            ans += s1[i - 1];
            i--;
        }
        else
        {
            ans += s2[j - 1];
            j--;
        }
    }

    // Add leftover characters
    while (i > 0)
    {
        ans += s1[i - 1];
        i--;
    }
    while (j > 0)
    {
        ans += s2[j - 1];
        j--;
    }

    // reverse to get correct order
    reverse(ans.begin(), ans.end());
    return ans;
}

/*------------------------------------------------------
                            MAIN
    Reads input → prints Shortest Common Supersequence

    Overall Time Complexity:
        LCS DP     : O(n*m)
        Backtrack  : O(n+m)
        Total      : O(n*m)

    Overall Space Complexity:
        DP table   : O(n*m)
-------------------------------------------------------*/
int main()
{
    string s1, s2;

    cout << "Enter first string: ";
    cin >> s1;

    cout << "Enter second string: ";
    cin >> s2;

    string scs = shortest_common_superseq(s1, s2);

    cout << "Shortest Common Supersequence = " << scs << endl;

    return 0;
}
