package SlidingWindow;
import java.util.*;

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
public class minWindowsubstr {

    // ------------------- Optimized Sliding Window -------------------
    public static String minWindowOptimized(String s, String t) {
        int l = 0, r = 0;
        int minLen = Integer.MAX_VALUE;
        int startIdx = -1;
        int count = 0;

        int[] hash = new int[256];  // ASCII characters frequency

        // Fill target string frequency
        for (char c : t.toCharArray()) hash[c]++;

        while (r < s.length()) {
            // If current char is needed, increment count
            if (hash[s.charAt(r)] > 0) count++;

            // Decrease frequency for current char
            hash[s.charAt(r)]--;

            // When all chars of t are matched
            while (count == t.length()) {
                // Update minimum window
                if (r - l + 1 < minLen) {
                    minLen = r - l + 1;
                    startIdx = l;
                }

                // Shrink from left
                hash[s.charAt(l)]++;
                if (hash[s.charAt(l)] > 0) count--;
                l++;
            }

            r++;
        }

        return (startIdx == -1) ? "" : s.substring(startIdx, startIdx + minLen);
    }

    // ------------------- Brute Force -------------------
    public static String minWindowBrute(String s, String t) {
        int minLen = Integer.MAX_VALUE;
        int startIdx = -1;

        for (int i = 0; i < s.length(); i++) {
            int[] hash = new int[256];
            for (char c : t.toCharArray()) hash[c]++;

            int count = 0;
            for (int j = i; j < s.length(); j++) {
                if (hash[s.charAt(j)] > 0) count++;
                hash[s.charAt(j)]--;

                if (count == t.length()) {
                    if (j - i + 1 < minLen) {
                        minLen = j - i + 1;
                        startIdx = i;
                    }
                    break;
                }
            }
        }

        return (startIdx == -1) ? "" : s.substring(startIdx, startIdx + minLen);
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        String s = "ADOBECODEBANC";
        String t = "ABC";

        System.out.println("Source String: " + s);
        System.out.println("Target String: " + t + "\n");

        String ansBrute = minWindowBrute(s, t);
        System.out.println("[Brute Force]  Smallest window: \"" + ansBrute + "\"");

        String ansOpt = minWindowOptimized(s, t);
        System.out.println("[Optimized]    Smallest window: \"" + ansOpt + "\"");
    }
}

