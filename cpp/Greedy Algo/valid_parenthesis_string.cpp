#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🔹 Problem: Valid Parenthesis String (LeetCode 678)
------------------------------------------------------------
Given a string s containing '(', ')' and '*',
where '*' can represent either '(' or ')' or an empty string,
return true if the string is valid.
------------------------------------------------------------
Example:
Input: s = "(*))"
Output: true
------------------------------------------------------------
*/

// ✅ Optimized Greedy Solution
class Solution {
public:
    bool checkValidString(string s) {
        int minOpen = 0;  // Minimum number of '(' that must be unmatched
        int maxOpen = 0;  // Maximum number of '(' that could be unmatched

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            
            if (c == '(') {
                minOpen++;
                maxOpen++;
            } 
            else if (c == ')') {
                minOpen--;
                maxOpen--;
            } 
            else { // c == '*'
                // '*' could be '(', ')' or empty
                minOpen--;     // if '*' acts as ')'
                maxOpen++;     // if '*' acts as '('
            }

            // If more ')' than '(' → invalid
            if (maxOpen < 0) return false;

            // minOpen can't go below 0
            if (minOpen < 0) minOpen = 0;
        }

        // If minOpen == 0 → possible valid sequence
        return minOpen == 0;
    }
};

/*
------------------------------------------------------------
🔹 Brute Force Recursive Approach (for intuition)
------------------------------------------------------------
Try all possibilities for '*' :
  - treat '*' as '('
  - treat '*' as ')'
  - treat '*' as empty

Time Complexity:  O(3^N)
Space Complexity: O(N) recursion depth
------------------------------------------------------------
*/

// Helper recursive function
bool valid_parenthesis_brute(string &s, int i, int cnt) {
    // if too many ')' → invalid
    if (cnt < 0) return false;

    // if reached end, must have balanced count
    if (i == s.size()) return cnt == 0;

    if (s[i] == '(')
        return valid_parenthesis_brute(s, i + 1, cnt + 1);

    if (s[i] == ')')
        return valid_parenthesis_brute(s, i + 1, cnt - 1);

    // if '*', try all three possibilities
    return valid_parenthesis_brute(s, i + 1, cnt + 1) || // '*' as '('
           valid_parenthesis_brute(s, i + 1, cnt - 1) || // '*' as ')'
           valid_parenthesis_brute(s, i + 1, cnt);       // '*' as empty
}

/*
------------------------------------------------------------
🔹 INTUITION COMPARISON
------------------------------------------------------------
✅ Brute Force: Tries every possible combination → very slow.
✅ Greedy: Tracks range of possible open brackets efficiently.
------------------------------------------------------------
*/

int main() {
    Solution sol;
    string s = "(*))";

    cout << "Greedy: " << (sol.checkValidString(s) ? "Valid" : "Invalid") << endl;
    cout << "Brute Force: " << (valid_parenthesis_brute(s, 0, 0) ? "Valid" : "Invalid") << endl;

    return 0;
}
