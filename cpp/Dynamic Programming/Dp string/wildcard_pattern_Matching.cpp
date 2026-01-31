#include <bits/stdc++.h>
using namespace std;

/*---------------------------------------------------------------
    WILDCARD MATCHING (Memoization)
    pattern → may contain '?' (matches 1 char) and '*' (matches 0+ chars)
    text → normal string

    Intuition:
    - If characters match OR '?' → match 1 char → move diagonally (i-1, j-1)
    - If '*' → can match:
        1) zero characters → move up (i-1, j)
        2) one or more characters → move left (i, j-1)
    - If both reach start (i<0 && j<0) → match successful
    - If pattern exhausted but text not → false
    - If text exhausted but pattern left → only valid if remaining pattern = all '*'

    Time Complexity:  O(n*m)
    Space Complexity: O(n*m) + recursion stack
----------------------------------------------------------------*/
int WildcardMatching_memo(int i, int j, string &pattern, string &text, vector<vector<int>> &dp)
{
    if (i < 0 && j < 0) return 1;      // both strings exhausted → match
    if (i < 0 && j >= 0) return 0;     // pattern finished but text still left → no match

    if (dp[i][j] != -1) return dp[i][j];

    if (j < 0 && i >= 0)
    {
        // text finished; pattern must be all '*' to match
        for (int x = 0; x <= i; x++)
            if (pattern[x] != '*')
                return dp[i][j] = 0;
        return dp[i][j] = 1;
    }

    // Char matches OR '?' → consume both characters
    if (pattern[i] == text[j] || pattern[i] == '?')
        return dp[i][j] = WildcardMatching_memo(i - 1, j - 1, pattern, text, dp);

    // '*' → two choices:
    // 1) '*' = empty → move up
    // 2) '*' = one or more chars → move left
    if (pattern[i] == '*')
        return dp[i][j] =
                   (WildcardMatching_memo(i - 1, j, pattern, text, dp) ||   // '*' as empty
                    WildcardMatching_memo(i, j - 1, pattern, text, dp));   // '*' consumes char

    return dp[i][j] = 0; // no match
}



/*---------------------------------------------------------------
    TABULATION DP
    Time Complexity:  O(n*m)
    Space Complexity: O(n*m)

    dp[i][j] = whether first i characters of pattern
               match first j characters of text
----------------------------------------------------------------*/
bool WildcardMatching_tabu(string &pattern, string &text)
{
    int n = pattern.size(), m = text.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;  // empty pattern = empty text

    // pattern empty but text not empty → false already

    // text empty → pattern must be only '*' to become true
    for (int i = 1; i <= n; i++)
    {
        bool allStars = true;
        for (int x = 0; x < i; x++)
        {
            if (pattern[x] != '*')
            {
                allStars = false;
                break;
            }
        }
        dp[i][0] = allStars;
    }

    // fill table
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (pattern[i - 1] == text[j - 1] || pattern[i - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];

            else if (pattern[i - 1] == '*')
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1]; // '*' as empty  OR '*' consuming char

            else
                dp[i][j] = false;
        }
    }
    return dp[n][m];
}



/*---------------------------------------------------------------
    SPACE OPTIMIZED DP (2 ROWS)
    Time Complexity:  O(n*m)
    Space Complexity: O(m)
----------------------------------------------------------------*/
bool WildcardMatching_tabu_so(string &pattern, string &text)
{
    int n = pattern.size(), m = text.size();
    vector<bool> prev(m + 1, false), curr(m + 1, false);

    prev[0] = true; // empty pattern & empty text

    for (int i = 1; i <= n; i++)
    {
        //curr is the current row/s column
        //and that curs 0th row has to be assigned
        bool allStars = true;
        for (int x = 0; x < i; x++)
        {
            if (pattern[x] != '*')
            {
                allStars = false;
                break;
            }
        }
        curr[0] = allStars; //for every row i am assiging the 0th columns value
        for (int j = 1; j <= m; j++)
        {
            if (pattern[i - 1] == text[j - 1] || pattern[i - 1] == '?')
                curr[j] = prev[j - 1];

            else if (pattern[i - 1] == '*')
                curr[j] = prev[j] || curr[j - 1];

            else
                curr[j] = false;
        }

        prev = curr;
    }
    return prev[m];
}



/*---------------------------------------------------------------
    MAIN FUNCTION
----------------------------------------------------------------*/
int main()
{
    string pattern = "a*b?c";
    string text = "axxbbzc";

    int n = pattern.size(), m = text.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    cout << "Memoization Result: " 
         << WildcardMatching_memo(n - 1, m - 1, pattern, text, dp) << "\n";

    cout << "Tabulation Result: "
         << WildcardMatching_tabu(pattern, text) << "\n";

    cout << "Space Optimized Result: "
         << WildcardMatching_tabu_so(pattern, text) << "\n";

    return 0;
}


//another and most optimal solution
class Solution {
public:
    bool isMatch(string s, string p) {
        int i=0,j=0,n=s.size(),m=p.size(),laststar=-1,matchstar=-1;;
        while(i<n){
            if(j<m &&( s[i]==p[j] || p[j]=='?')){
                i++;
                j++;
            }
            else if(j<m && p[j]=='*'){
               laststar=j;
              matchstar=i;
              j++;
            }
            else if(laststar!=-1){
               j=laststar+1;
               i=(++matchstar);
            }
            else return false;
        }
        while(j<m && p[j]=='*')j++;
        return (j==m);
    }
};