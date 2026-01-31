package SlidingWindow;
import java.util.*;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given a binary array `nums` (containing only
0s and 1s) and an integer `k`.

You are allowed to flip at most `k` zeros to 1s.

Goal:
- Find the length of the longest subarray containing
  only 1s after performing at most `k` flips.

--------------------------------------------------------
EXAMPLE:
Input:  nums = [1,1,0,0,1,1,1,0,1], k = 2
Output: 7

========================================================
*/
public class MaxConsecutiveOnesIII {
    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Consider every subarray
    - Count number of zeros
    - If zeros ≤ k, update answer

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Check all possible windows and validate whether they
    satisfy the constraint (zeros ≤ k).

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n²)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
    public static int longestOnesBrute(int[] nums, int k) {
        int n = nums.length;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            int zeros = 0;
            for (int j = i; j < n; j++) {
                if (nums[j] == 0) zeros++;

                if (zeros <= k) {
                    int len = j - i + 1;
                    maxLen = Math.max(maxLen, len);
                } else {
                    break;
                }
            }
        }
        return maxLen;
    }

    /*
    ========================================================
    BETTER APPROACH (SLIDING WINDOW):
    --------------------------------------------------------
    Idea:
    - Use two pointers (left & right)
    - Expand window by moving right
    - Shrink window from left when zeros exceed k

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    We maintain a window where zeros ≤ k.
    If constraint breaks, move left pointer.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(2n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
    public static int longestOnesBetter(int[] nums, int k) {
        int left = 0, right = 0;
        int zeros = 0, maxLen = 0;

        while (right < nums.length) {
            if (nums[right] == 0) zeros++;

            while (zeros > k) {
                if (nums[left] == 0) zeros--;
                left++;
            }

            int len = right - left + 1;
            maxLen = Math.max(maxLen, len);
            right++;
        }

        return maxLen;
    }

    /*
    ========================================================
    OPTIMAL APPROACH (CLEAN SLIDING WINDOW):
    --------------------------------------------------------
    Same logic as above, written more concisely.

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    - Always expand right
    - Shrink left only when zeros exceed k
    - Update answer whenever window is valid

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
    public static int longestOnesOptimal(int[] nums, int k) {
        int left = 0, zeros = 0, maxLen = 0;

        for (int right = 0; right < nums.length; right++) {
            if (nums[right] == 0) zeros++;

            if (zeros > k) {
                if (nums[left] == 0) zeros--;
                left++;
            }

            if (zeros <= k) {
                int len = right - left + 1;
                maxLen = Math.max(maxLen, len);
            }
        }

        return maxLen;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        int[] nums = {1, 1, 0, 0, 1, 1, 1, 0, 1};
        int k = 2;

        System.out.println("Brute force: " + longestOnesBrute(nums, k));
        System.out.println("Better (sliding window): " + longestOnesBetter(nums, k));
        System.out.println("Optimal (clean): " + longestOnesOptimal(nums, k));
    }
}
