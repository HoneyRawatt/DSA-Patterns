#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
Given a string `s`, find the length of the longest
substring without repeating characters.

A substring is a contiguous part of the string.

--------------------------------------------------------
EXAMPLE:
Input:  "abcabcbb"
Output: 3
Explanation: The answer is "abc", with length 3.

========================================================
*/

/*
========================================================
BRUTE FORCE APPROACH:
--------------------------------------------------------
Idea:
- Try every possible starting index `i`
- Expand the substring until a duplicate character
  is found
- Track the maximum length

--------------------------------------------------------
INTUITION:
--------------------------------------------------------
For each index, keep adding characters while all are
unique. Stop as soon as a duplicate appears.

--------------------------------------------------------
TIME COMPLEXITY:
- O(n²)

SPACE COMPLEXITY:
- O(1) (fixed size array of 256 characters)
========================================================
*/
// ✅ Brute-force O(n^2) version
int lengthoflongestsubstr_brute(string s)
{
    int maxlen = 0, n = s.length();

    for (int i = 0; i < n; i++)
    {
        int hash[256] = {0}; // reset for every starting index

        for (int j = i; j < n; j++)
        {
            if (hash[s[j]])
                break; // if already seen, break

            hash[s[j]] = 1; // mark as seen
            int len = j - i + 1;
            maxlen = max(maxlen, len);
        }
    }
    return maxlen;
}
    /*
    ========================================================
    OPTIMIZED APPROACH (SLIDING WINDOW):
    --------------------------------------------------------

    INTUITION:
    --------------------------------------------------------
    - Use two pointers (left & right) to maintain a window
    - Expand the window by moving `right`
    - If a duplicate is found:
        Move `left` just after the previous occurrence
    - Always maintain a window with unique characters

    --------------------------------------------------------
    KEY IDEA:
    --------------------------------------------------------
    Store the last seen index of every character.
    This allows us to jump the left pointer directly.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(1) (array of size 256)
    ========================================================
    */
int lengthOfLongestSubstring(string s)
{
    int hash[256];
    for (int i = 0; i < 255; i++)
        hash[i] = -1; // initialize all characters as not seen

    int n = s.length();
    int l = 0, r = 0, maxlen = 0;

    while (r < n)
    {
        // if current character already seen and inside current window
        if (hash[s[r]] != -1)
        {
            if (hash[s[r]] >= l)
                l = hash[s[r]] + 1; // move left pointer to avoid duplicate
        }

        int len = r - l + 1;       // current window length
        maxlen = max(len, maxlen); // update max length

        hash[s[r]] = r; // update last seen index
        r++;            // move right pointer
    }

    return maxlen;
}

// --------------- MAIN FUNCTION ---------------
int main()
{
    string input = "abcabcbb";
    int result1 = lengthOfLongestSubstring(input);
    cout << "Optimal (O(n)) result: " << result1 << endl;

    int result2 = lengthoflongestsubstr_brute(input);
    cout << "Brute-force (O(n^2)) result: " << result2 << endl;
    return 0;
}
