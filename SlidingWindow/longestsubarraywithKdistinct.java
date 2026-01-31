package SlidingWindow;

import java.util.*;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
Given an integer array `arr` and an integer `k`,
find the length of the longest contiguous subarray
that contains at most `k` distinct elements.

--------------------------------------------------------
EXAMPLE:
Input:  arr = [1, 2, 1, 2, 3], k = 2
Output: 4
Explanation:
The longest subarray with at most 2 distinct elements
is [1, 2, 1, 2]

========================================================
*/

class longestsubarraywithKdistinct{

    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Generate all possible subarrays
    - Use a set to track distinct elements
    - Stop expanding when distinct count exceeds k

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Try every starting index and extend the subarray
    until the constraint (≤ k distinct elements) breaks.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n²)

    SPACE COMPLEXITY:
    - O(1) (set size ≤ k)
    ========================================================
    */
    public static int longestSubstrBrute(int[] arr, int k) {
        int maxLen = 0;

        for (int i = 0; i < arr.length; i++) {
            Set<Integer> set = new HashSet<>();

            for (int j = i; j < arr.length; j++) {
                set.add(arr[j]);

                if (set.size() <= k) {
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
    BETTER APPROACH (SLIDING WINDOW + HASHMAP):
    --------------------------------------------------------
    Idea:
    - Use two pointers (left & right)
    - Maintain frequency of elements in a hashmap
    - Shrink window when distinct elements exceed k

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Keep a window that always satisfies:
        number of distinct elements ≤ k

    Expand right pointer.
    Shrink left pointer only when constraint breaks.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(2n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
    public static int longestSubstrBetter(int[] arr, int k) {
        int left = 0, maxLen = 0;
        Map<Integer, Integer> map = new HashMap<>();

        for (int right = 0; right < arr.length; right++) {
            map.put(arr[right], map.getOrDefault(arr[right], 0) + 1);

            while (map.size() > k) {
                map.put(arr[left], map.get(arr[left]) - 1);
                if (map.get(arr[left]) == 0)
                    map.remove(arr[left]);
                left++;
            }

            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    /*
    ========================================================
    OPTIMAL APPROACH (CLEAN SLIDING WINDOW):
    --------------------------------------------------------
    Same logic as the better approach, written more cleanly.

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    - Expand window using right pointer
    - Shrink from left only when needed
    - Always keep the window valid

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
    public static int longestSubstrOptimal(int[] arr, int k) {
        int left = 0, maxLen = 0;
        Map<Integer, Integer> map = new HashMap<>();

        for (int right = 0; right < arr.length; right++) {
            map.put(arr[right], map.getOrDefault(arr[right], 0) + 1);

            if (map.size() > k) {
                map.put(arr[left], map.get(arr[left]) - 1);
                if (map.get(arr[left]) == 0)
                    map.remove(arr[left]);
                left++;
            }

            if (map.size() <= k) {
                maxLen = Math.max(maxLen, right - left + 1);
            }
        }
        return maxLen;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        int[] arr = {1, 2, 1, 2, 3};
        int k = 2;

        System.out.println("Brute Force: " + longestSubstrBrute(arr, k));
        System.out.println("Better: " + longestSubstrBetter(arr, k));
        System.out.println("Optimal: " + longestSubstrOptimal(arr, k));
    }
}
