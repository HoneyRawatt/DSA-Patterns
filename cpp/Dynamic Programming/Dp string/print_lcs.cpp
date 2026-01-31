#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    LCS TABULATION (Bottom-Up DP)
    dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]

    Time Complexity:  O(n*m)
    Space Complexity: O(n*m)

    Intuition:
    - If characters match → LCS increases by 1
    - Otherwise → we take the maximum by skipping one char
-------------------------------------------------------*/

// Instead of returning only dp[n][m], return the whole dp table.
vector<vector<int>> lcs_tabu(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill dp bottom-up
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])    // characters match
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else                          // take max by skipping a char
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp;
}

/*------------------------------------------------------
    PRINT LCS using the DP table

    Intuition:
    - Start from bottom-right (n,m)
    - If chars match → include in answer and go diagonal
    - Else → go towards the direction from which dp was formed
-------------------------------------------------------*/
string printLcs(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp = lcs_tabu(s1, s2);

    int len = dp[n][m];
    string ans(len, '$');   // allocate correct size
    int index = len - 1;

    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])       // correct condition
        {
            ans[index] = s1[i - 1];
            index--;
            i--, j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    return ans;
}

/*------------------------------------------------------
                       MAIN FUNCTION
-------------------------------------------------------*/
int main()
{
    string s1 = "abcde";
    string s2 = "ace";

    cout << "LCS length: " << lcs_tabu(s1, s2)[s1.size()][s2.size()] << endl;
    cout << "LCS string: " << printLcs(s1, s2) << endl;
    return 0;
}


//for Print all LCS
class Solution {
public:
void backtrack(vector<vector<int>> &dp, set<string> &st, unordered_map<string,bool> &mp, 
    string &text1, string &text2, int i, int j, string &res){
        if(i == 0 || j == 0){
            string temp = res;
            reverse(temp.begin(), temp.end());
            st.insert(temp);
            return;
        }
        
        string key = to_string(i) + "$" + to_string(j) + "$" + res;
        if(mp.find(key) != mp.end()) return;
        mp[key] = true;

        if(text1[i-1] == text2[j-1]){
            res.push_back(text1[i-1]);
            backtrack(dp, st, mp, text1, text2, i-1, j-1, res);
            res.pop_back();
        } else {
            if(dp[i][j] == dp[i-1][j]){
                backtrack(dp, st, mp, text1, text2, i-1, j, res);
            }
            if(dp[i][j] == dp[i][j-1]){
                backtrack(dp, st, mp, text1, text2, i, j-1, res);
            }
        }
    }

    vector<string> allLCS(string &text1, string &text2) {
        int n = text1.size();
        int m = text2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        set<string> st;                  
        unordered_map<string,bool> mp;    
        string res = "";
        backtrack(dp, st, mp, text1, text2, n, m, res);

        return vector<string>(st.begin(), st.end());
    }
};
