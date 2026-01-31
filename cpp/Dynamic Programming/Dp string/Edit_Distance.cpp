#include <bits/stdc++.h>
using namespace std;

/*-----------------------------------------------
    RECURSION + MEMOIZATION
    Time:  O(n*m)
    Space: O(n*m) + Recursion stack
------------------------------------------------*/
int editDistance_memo(int i, int j, string &str1, string &str2, vector<vector<int>>& dp) 
{
    if (i < 0) return j + 1;   // need j+1 insertions
    if (j < 0) return i + 1;   // need i+1 deletions

    if (dp[i][j] != -1) return dp[i][j];

    if (str1[i] == str2[j])
        return dp[i][j] = editDistance_memo(i - 1, j - 1, str1, str2, dp);

    return dp[i][j] = 1 + min({ 
                editDistance_memo(i - 1, j, str1, str2, dp),     // delete
                editDistance_memo(i - 1, j - 1, str1, str2, dp), // replace
                editDistance_memo(i, j - 1, str1, str2, dp)      // insert
            });
}

/*-----------------------------------------------
    TABULATION DP
    Time:  O(n*m)
    Space: O(n*m)
------------------------------------------------*/
int editDistance_tabu(string& str1, string& str2) 
{
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 0; i <= n; i++) dp[i][0] = i;

    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= m; j++) 
        {
            if (str1[i - 1] == str2[j - 1]) 
                dp[i][j] = dp[i - 1][j - 1];
            else 
                dp[i][j] = 1 + min({
                    dp[i - 1][j],     // delete
                    dp[i - 1][j - 1], // replace
                    dp[i][j - 1]      // insert
                });
        }
    }
    return dp[n][m];
}

/*-----------------------------------------------
    SPACE OPTIMIZED (2 rows)
    Time:  O(n*m)
    Space: O(m)
------------------------------------------------*/
int editDistance_tabu_so(string& str1, string& str2) 
{
    int n = str1.size(), m = str2.size();
    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) 
    {
        curr[0] = i;

        for (int j = 1; j <= m; j++) 
        {
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({ 
                    prev[j],     // delete
                    prev[j - 1], // replace
                    curr[j - 1]  // insert
                });
        }
        prev = curr;
    }
    return prev[m];
}

int main() {
    string s1 = "horse", s2 = "ros";

    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), -1));

    cout << "Memoized: " << editDistance_memo(s1.size()-1, s2.size()-1, s1, s2, dp) << "\n";
    cout << "Tabulation: " << editDistance_tabu(s1, s2) << "\n";
    cout << "Space Optimized: " << editDistance_tabu_so(s1, s2) << "\n";

    return 0;
}
