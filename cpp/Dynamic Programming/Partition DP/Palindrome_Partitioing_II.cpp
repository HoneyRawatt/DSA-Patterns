#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------
Utility Function: Check Palindrome
----------------------------------------------------
Time: O(n)
----------------------------------------------------
*/
bool isPalindrome(int i, int j, string &str) {
    while (i < j) {
        if (str[i] != str[j]) return false;
        i++;
        j--;
    }
    return true;
}

/*
----------------------------------------------------
MEMOIZATION (TOP-DOWN DP)
----------------------------------------------------
Intuition:
- dp[i] = minimum partitions needed from index i to end
- Try every possible palindrome substring [i..j]
- Take 1 cut + solve remaining part
----------------------------------------------------
Time Complexity: O(n^3)
Space Complexity: O(n) + recursion stack
----------------------------------------------------
*/

int palindrome_partitioning_II_memo(int i, int n, string &str,
                                    vector<int> &dp) {
    if (i == n) return 0;

    if (dp[i] != -1) return dp[i];

    int minicost = INT_MAX;

    for (int j = i; j < n; j++) {
        if (isPalindrome(i, j, str)) {
            int cost = 1 + palindrome_partitioning_II_memo(j + 1, n, str, dp);
            minicost = min(minicost, cost);
        }
    }

    return dp[i] = minicost;
}

/*
----------------------------------------------------
TABULATION (BOTTOM-UP DP)
----------------------------------------------------
Intuition:
- dp[i] = minimum cuts needed from index i
- Build from end towards start
----------------------------------------------------
Time Complexity: O(n^3)
Space Complexity: O(n)
----------------------------------------------------
*/

int palindrome_partitioning_II_tabu(string &str) {
    int n = str.size();
    vector<int> dp(n + 1, 0);

    dp[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        int minicost = INT_MAX;

        for (int j = i; j < n; j++) {
            if (isPalindrome(i, j, str)) {
                int cost = 1 + dp[j + 1];
                minicost = min(minicost, cost);
            }
        }
        dp[i] = minicost;
    }

    // -1 because last partition does not need a cut
    return dp[0] - 1;
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
*/

int main() {
    string str = "aab";
    int n = str.size();

    vector<int> dp(n, -1);

    cout << "Memoization Answer: "
         << palindrome_partitioning_II_memo(0, n, str, dp) - 1 << endl;

    cout << "Tabulation Answer: "
         << palindrome_partitioning_II_tabu(str) << endl;

    return 0;
}
