#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    3) SPACE-OPTIMIZED TABULATION (Only 1 row)
    Finds LCS(s1, s2)
    Time Complexity:  O(n*m)
    Space Complexity: O(m)
-------------------------------------------------------*/

int lcs_tabu_so(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    // prev[j] = DP[i-1][j], curr[j] = DP[i][j]
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        // Clear current row before using it
        fill(curr.begin(), curr.end(), 0);

        for (int j = 1; j <= m; j++)
        {
            /* Intuition:
                If characters match → part of LCS → take diagonal + 1
                If not match → best of excluding one char from either side
            */
            if (s1[i - 1] == s2[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }

        // Current becomes previous for next iteration
        prev = curr;
    }

    return prev[m]; // final LCS length
}

/*------------------------------------------------------
    lcp() → Longest Common Palindromic Subsequence
    Uses LCS(s, reverse(s))
-------------------------------------------------------*/
int lcp(string &s1)
{
    string s2 = s1;
    reverse(s2.begin(), s2.end()); // Correct reverse usage

    return lcs_tabu_so(s1, s2);
}

// another method
int longest(int i, int j, string &s, vector<vector<int>> &dp)
{
    if (i == j)
        return 1;
    if (i > j)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    if (s[i] == s[j])
        return dp[i][j] = longest(i + 1, j - 1, s, dp) + 2;
    else
        return dp[i][j] = max(longest(i + 1, j, s, dp), longest(i, j - 1, s, dp));
}
int longestPalindromeSubseq(string s)
{
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
    return longest(0, s.size() - 1, s, dp);
}
/*------------------------------------------------------
                       MAIN FUNCTION
-------------------------------------------------------*/
int main()
{
    string s;
    cout << "Enter a string: ";
    cin >> s;

    // LCP = LCS(s , reverse(s))
    int ans = lcp(s);

    cout << "Longest Palindromic Subsequence Length = " << ans << endl;

    return 0;
}
