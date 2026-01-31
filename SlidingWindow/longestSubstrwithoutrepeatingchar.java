package SlidingWindow;

import java.util.*;

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
class longestSubstrwithoutrepeatingchar{

    public static int lengthOfLongestSubstringBrute(String s) {
        int n = s.length();
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            int[] hash = new int[256]; // reset for each start

            for (int j = i; j < n; j++) {
                if (hash[s.charAt(j)] == 1)
                    break; // duplicate found

                hash[s.charAt(j)] = 1;
                int len = j - i + 1;
                maxLen = Math.max(maxLen, len);
            }
        }
        return maxLen;
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
    public static int lengthOfLongestSubstring(String s) {
        int[] lastSeen = new int[256];
        Arrays.fill(lastSeen, -1); // initialize all as unseen

        int left = 0, maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            char ch = s.charAt(right);

            // if character already seen in current window
            if (lastSeen[ch] >= left) {
                left = lastSeen[ch] + 1; // move left pointer
            }

            int len = right - left + 1;
            maxLen = Math.max(maxLen, len);

            lastSeen[ch] = right; // update last seen index
        }

        return maxLen;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        String input = "abcabcbb";

        int optimal = lengthOfLongestSubstring(input);
        System.out.println("Optimal (O(n)) result: " + optimal);

        int brute = lengthOfLongestSubstringBrute(input);
        System.out.println("Brute-force (O(n^2)) result: " + brute);
    }
}
