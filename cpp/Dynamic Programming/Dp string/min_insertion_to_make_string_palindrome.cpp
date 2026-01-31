#include <bits/stdc++.h> 
using namespace std;

/*------------------------------------------------------
    SPACE-OPTIMIZED TABULATION for LCS(s1, s2)
    
    Intuition:
    - LCS is built by comparing characters.
    - If chars match: 1 + diagonal previous
    - Else: take max of left or top (ignoring one character)
    - Instead of full 2D DP table, we maintain only 2 rows:
          prev[] = DP[i-1][..]
          curr[] = DP[i][..]

    Time Complexity:  O(n * m)
    Space Complexity: O(m)
-------------------------------------------------------*/
int lcs_tabu_so(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        fill(curr.begin(), curr.end(), 0);  // reset row

        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                // characters match → part of LCS
                curr[j] = 1 + prev[j - 1];
            }
            else
            {
                // take the better option: top or left
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        prev = curr; // slide window: curr becomes prev
    }

    return prev[m];
}

/*------------------------------------------------------
    lcp(): Longest Common Palindromic Subsequence
    Idea:
    - A palindrome reads same forward & backward
    - So LPS = LCS(s, reverse(s))

    Time Complexity:  O(n^2)
    Space Complexity: O(n)
-------------------------------------------------------*/
int lcp(string &s1)
{
    string s2 = s1;
    reverse(s2.begin(), s2.end());

    return lcs_tabu_so(s1, s2);
}

/*------------------------------------------------------
    Minimum Insertions to Make String Palindrome

    Formula:
        min_insertions = n - LPS_length

    Reason:
    - LPS tells how many chars are already "in place"
    - Others must be inserted to fix symmetry

    Time Complexity:  O(n^2)
    Space Complexity: O(n)
-------------------------------------------------------*/
int min_insertion_make_string_palindrome(string &s1)
{
    int palLen = lcp(s1);  
    return s1.size() - palLen;
}

/*------------------------------------------------------
                        MAIN FUNCTION
    What it does:
    - Takes string input
    - Computes minimum insertions required to make it a palindrome
    - Shows final output

    Overall Time Complexity:  O(n^2)
    Overall Space Complexity: O(n)
-------------------------------------------------------*/
int main()
{
    string s;
    cout << "Enter a string: ";
    cin >> s;

    int ans = min_insertion_make_string_palindrome(s);

    cout << "Minimum Insertions to Make Palindrome = " << ans << endl;

    return 0;
}
