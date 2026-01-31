package SlidingWindow;

import java.util.*;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given a string `s` consisting of uppercase
English letters and an integer `k`.

You can replace at most `k` characters in the string
with any other character.

Goal:
- Find the length of the longest substring that can be
  obtained after performing at most `k` replacements
  such that all characters in the substring are the same.

--------------------------------------------------------
EXAMPLE:
Input:  s = "AABABBA", k = 1
Output: 4
Explanation:
Replace one 'B' with 'A' → "AAAA"

========================================================
*/

public class LongestRepeatingCharReplacement {

    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Fix a starting index
    - Extend substring character by character
    - Track frequency of characters
    - Find the most frequent character (maxf)
    - Check if replacements needed ≤ k

    replacements = window_length - maxf

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    To make all characters same, we only need to replace
    the characters that are NOT the most frequent one.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n² * 26) ≈ O(n²)

    SPACE COMPLEXITY:
    - O(26) = O(1)
    ========================================================
    */
    public static int characterReplacementBrute(String s, int k) {
        int maxLen = 0;

        for (int i = 0; i < s.length(); i++) {
            int[] freq = new int[26];
            int maxf = 0;

            for (int j = i; j < s.length(); j++) {
                freq[s.charAt(j) - 'A']++;
                maxf = Math.max(maxf, freq[s.charAt(j) - 'A']);

                if ((j - i + 1) - maxf <= k) {
                    maxLen = Math.max(maxLen, j - i + 1);
                } else {
                    break;
                }
            }
        }
        return maxLen;
    }

    /*
    ========================================================
    BETTER APPROACH (Sliding Window + Recompute maxf):
    --------------------------------------------------------
    Idea:
    - Use sliding window (left & right pointers)
    - Maintain character frequencies
    - When window becomes invalid, shrink it
    - Recalculate maxf when shrinking (costly but safe)

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Sliding window keeps checking valid substrings while
    expanding and shrinking dynamically.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(26 * n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(26) = O(1)
    ========================================================
    */
    public static int characterReplacementBetter(String s, int k) {
        int left = 0, maxLen = 0, maxf = 0;
        int[] freq = new int[26];

        for (int right = 0; right < s.length(); right++) {
            freq[s.charAt(right) - 'A']++;
            maxf = Math.max(maxf, freq[s.charAt(right) - 'A']);

            while ((right - left + 1) - maxf > k) {
                freq[s.charAt(left) - 'A']--;
                maxf = 0;
                for (int i = 0; i < 26; i++)
                    maxf = Math.max(maxf, freq[i]);
                left++;
            }

            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    /*
    ========================================================
    OPTIMIZED APPROACH (Sliding Window without recomputing maxf):
    --------------------------------------------------------
    Key Trick:
    - Do NOT decrease maxf when shrinking window
    - maxf may become stale, but window validity remains correct

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Even if maxf is outdated, it only makes the window
    larger, never invalid.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(26) = O(1)
    ========================================================
    */
    public static int characterReplacementOptimized(String s, int k) {
        int left = 0, maxLen = 0, maxf = 0;
        int[] freq = new int[26];

        for (int right = 0; right < s.length(); right++) {
            freq[s.charAt(right) - 'A']++;
            maxf = Math.max(maxf, freq[s.charAt(right) - 'A']);

            if ((right - left + 1) - maxf > k) {
                freq[s.charAt(left) - 'A']--;
                left++;
            }

            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        String s = "AABABBA";
        int k = 1;

        System.out.println("Brute Force Result:    " + characterReplacementBrute(s, k));
        System.out.println("Better Result:         " + characterReplacementBetter(s, k));
        System.out.println("Optimized Result:      " + characterReplacementOptimized(s, k));
    }
}
