#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    Comparator:
    Sort strings by length (ascending)
------------------------------------------------------*/
bool comp(string &s1, string &s2) {
    return s1.size() < s2.size();
}

/*------------------------------------------------------
    checkPossible(s1, s2)

    Returns true if s2 can be obtained by removing
    exactly one character from s1.

    Example:
    s1 = "abcd", s2 = "abc" → true
------------------------------------------------------*/
bool checkPossible(string &s1, string &s2) {
    if (s1.size() != s2.size() + 1) return false;

    int i = 0, j = 0;
    while (i < s1.size()) {
        if (j < s2.size() && s1[i] == s2[j]) {
            i++;
            j++;
        } else {
            i++;  // skip one char from s1
        }
    }
    return j == s2.size();
}

/*------------------------------------------------------
    Longest String Chain (DP)

    Intuition:
    - Sort strings by length
    - dp[i] → longest chain ending at string i
    - For every string, try appending it to all
      smaller-length strings
------------------------------------------------------*/
int longest_string_chain(vector<string>& arr, int n) {
    sort(arr.begin(), arr.end(), comp);

    vector<int> dp(n, 1);
    int maxi = 1;

    for (int ind = 0; ind < n; ind++) {
        for (int prev = 0; prev < ind; prev++) {
            if (checkPossible(arr[ind], arr[prev]) &&
                dp[prev] + 1 > dp[ind]) {

                dp[ind] = dp[prev] + 1;
            }
        }
        maxi = max(maxi, dp[ind]);
    }
    return maxi;
}

/*------------------------------------------------------
    MAIN FUNCTION
------------------------------------------------------*/
int main() {
    vector<string> words = {"a", "b", "ba", "bca", "bda", "bdca"};
    int n = words.size();

    cout << "Longest String Chain Length: "
         << longest_string_chain(words, n) << endl;

    return 0;
}


// ⏱️ Time & Space Complexity
// Metric	Complexity
// Sorting	O(N log N)
// DP	O(N² × L) (L = max string length)
// Space	O(N)