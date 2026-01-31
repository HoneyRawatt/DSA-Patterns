#include <bits/stdc++.h>
using namespace std;

/*=====================================================================
    LONGEST COMMON SUBSTRING (NOT LCS)
    --------------------------------------------------------------
    Intuition:
    - We want the longest substring that appears in BOTH strings.
    - Unlike LCS, here characters must match *continuously*.
    - If characters match → extend previous diagonal dp[i-1][j-1] + 1
    - If not match → reset dp[i][j] = 0
    - Track maximum value in DP table.

    Time Complexity:  O(n * m)
    Space Complexity: O(n * m)
======================================================================*/
int longestCommonSubstring_tabu(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1]; // extend substring
                ans = max(ans, dp[i][j]);
            }
            else
            {
                dp[i][j] = 0; // reset for substring rule
            }
        }
    }

    return ans;
}

/*=====================================================================
    SPACE OPTIMIZED VERSION
    --------------------------------------------------------------
    Space Optimization:
    - Only previous row is needed.
    - Use prev[] and curr[] of size m+1.

    Time Complexity:  O(n * m)
    Space Complexity: O(m)
======================================================================*/
int longestCommonSubstring_so(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
                ans = max(ans, curr[j]);
            }
            else
            {
                curr[j] = 0;
            }
        }
        prev = curr;
    }

    return ans;
}

/*=====================================================================
    MAIN FUNCTION TO TEST THE SOLUTION
======================================================================*/
int main()
{
    string s1 = "abcde";
    string s2 = "abfce";

    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;

    cout << "\nLongest Common Substring Length (Tabulation): "
         << longestCommonSubstring_tabu(s1, s2) << endl;

    cout << "Longest Common Substring Length (Space Optimized): "
         << longestCommonSubstring_so(s1, s2) << endl;

    return 0;
}
