#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    SPACE-OPTIMIZED TABULATION for LCS(s1, s2)

    Intuition:
    - LCS = longest common part that BOTH strings already share.
    - Characters NOT in LCS must be:
         deleted from s1 OR inserted from s2.
    - Using only 2 rows (prev & curr) saves memory.

    Transitions:
        If match → 1 + prev[j-1]
        Else     → max(prev[j], curr[j-1])

    Time Complexity:  O(n * m)
    Space Complexity: O(m)
-------------------------------------------------------*/
int lcs_tabu_so(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        fill(curr.begin(), curr.end(), 0);  // reset current row

        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            else
            {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        prev = curr; // move window forward
    }

    return prev[m]; // LCS length
}

/*------------------------------------------------------
    Minimum operations to convert s1 → s2 using
    INSERTIONS + DELETIONS only.

    Formula:
        ops = (|s1| + |s2|) - 2 * LCS(s1, s2)

    Intuition:
    - LCS is the longest part we DON’T need to modify.
    - Everything outside LCS must be:
          - deleted from s1 or
          - inserted to make s2.

    Time Complexity:  O(n * m)
    Space Complexity: O(m)
-------------------------------------------------------*/
int min_operation_toconvertString(string &s1, string &s2)
{
    int lcslen = lcs_tabu_so(s1, s2);
    return (s1.size() + s2.size()) - 2 * lcslen;
}

/*------------------------------------------------------
                          MAIN()
    What this does:
    - Reads two strings
    - Computes minimum insert/delete operations needed
      to convert s1 → s2
    - Prints the result

    Overall Time Complexity:  O(n * m)
    Overall Space Complexity: O(m)
-------------------------------------------------------*/
int main()
{
    string s1, s2;

    cout << "Enter first string: ";
    cin >> s1;

    cout << "Enter second string: ";
    cin >> s2;

    int result = min_operation_toconvertString(s1, s2);

    cout << "Minimum operations (insertions + deletions) to convert s1 into s2 = "
         << result << endl;

    return 0;
}
