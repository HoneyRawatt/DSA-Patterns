#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given a string `s` representing a non-negative integer
and an integer `k`, remove exactly `k` digits from `s`
such that the resulting number is the smallest possible.

Return the resulting number as a string.
Leading zeros are not allowed unless the result is "0".

Example:
s = "1432219", k = 3
Output: "1219"
=====================================================
*/

/*
===============================
Greedy + Monotonic Stack Approach
===============================
Intuition:
- To make the number as small as possible, we want
  smaller digits to appear as early as possible.
- Use a monotonic increasing stack (digits in increasing order).
- If the current digit is smaller than the stack top,
  removing the stack top leads to a smaller number.
- Repeat until the stack is valid or k removals are done.

Key Observations:
- Removing a larger digit before a smaller one reduces the number
- If removals remain after processing all digits,
  remove digits from the end (largest impact at the back)

Time Complexity: O(n)
- Each digit is pushed and popped at most once

Space Complexity: O(n)
- Stack stores digits of the number
*/
string remove_k_digits(string s, int k) {
    stack<char> st;
    int n = s.length();

    // Traverse each digit in the string
    for (int i = 0; i < n; i++) {

        // Remove previous larger digits to make number smaller
        while (!st.empty() && k > 0 && st.top() > s[i]) {
            st.pop();  // remove larger digit
            k--;
        }

        // Push current digit
        st.push(s[i]);
    }

    // If removals are still left, remove from the end
    // (largest digits remain at the top)
    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }

    // Build result string from stack (reverse order)
    string res;
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());

    // Remove leading zeros
    while (res.size() > 1 && res[0] == '0') {
        res.erase(res.begin());
    }

    // If all digits removed, return "0"
    if (res.empty()) return "0";

    return res;
}

/*
===============================
Main Function
===============================
*/
int main() {
    string s = "1432219";
    int k = 3;

    cout << remove_k_digits(s, k) << endl; 
    // Expected output: "1219"

    return 0;
}
