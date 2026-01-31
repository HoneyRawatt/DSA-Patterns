#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement

Minimum Window Substring:

Given strings s and t, find the smallest substring in s that contains all characters of t (including duplicates).

If no such window exists, return "".

Order of characters does not matter.

Example:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"

Intuition

Maintain a sliding window [l, r] over s.

Keep a frequency map of characters in t.

Expand r to include characters in the window and update counts.

When all characters of t are included (count == t.size()), try shrinking from left to minimize window length.

Repeat until the end of s.

Complexity Analysis
Approach	Time Complexity	Space Complexity
Brute Force	O(n²)	O(1) (hash[256])
Optimized Sliding Window	O(n)	O(256) ≈ O(1)
*/
/*
    Function: minWindow_optimized
    Purpose: Find the smallest window in `s` that contains all characters of `t`
    Approach: Sliding window with character frequency tracking
    Complexity: O(n)
*/
string minWindow_optimized(string s, string t) {
    int l = 0, r = 0;                 // Window boundaries
    int minlen = INT_MAX, sind = -1;  // Min length & starting index
    int cnt = 0;                      // Count of matched characters
    vector<int> hash(256, 0);         // ASCII char count

    // Fill frequency array for target string
    for (char c : t) hash[c]++;

    // Expand the window
    while (r < s.size()) {
        if (hash[s[r]] > 0) cnt++;     // This char is part of t
        hash[s[r]]--;                  // Decrease freq (can go negative)
        
        // When all t's chars are matched
        while (cnt == t.size()) {
            // Update min window
            if (r - l + 1 < minlen) {
                minlen = r - l + 1;
                sind = l;
            }
            // Shrink from left
            hash[s[l]]++;
            if (hash[s[l]] > 0) cnt--; // If we lost a needed char
            l++;
        }
        r++;
    }
    return (sind == -1) ? "" : s.substr(sind, minlen);
}

/*
    Function: minWindow_brute
    Purpose: Brute force check for smallest substring containing all of t
    Approach: Try every starting index i, expand until t is matched
    Complexity: O(n^2)
*/
string minWindow_brute(string s, string t) {
    int minlen = INT_MAX, sind = -1;

    for (int i = 0; i < s.size(); i++) {
        vector<int> hash(256, 0);
        for (char c : t) hash[c]++;    // Reset frequency for each i

        int cnt = 0;                   // Matches for current i
        for (int j = i; j < s.size(); j++) {
            if (hash[s[j]] > 0) cnt++;
            hash[s[j]]--;

            if (cnt == t.size()) {     // All chars matched
                if (j - i + 1 < minlen) {
                    minlen = j - i + 1;
                    sind = i;
                }
                break; // Found smallest for this i
            }
        }
    }
    return (sind == -1) ? "" : s.substr(sind, minlen);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    cout << "Source String: " << s << "\n";
    cout << "Target String: " << t << "\n\n";

    // Brute Force
    string ans_brute = minWindow_brute(s, t);
    cout << "[Brute Force]  Smallest window: \"" << ans_brute << "\"\n";

    // Optimized Sliding Window
    string ans_opt = minWindow_optimized(s, t);
    cout << "[Optimized]    Smallest window: \"" << ans_opt << "\"\n";

    return 0;
}
