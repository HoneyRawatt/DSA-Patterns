package SlidingWindow;
import java.util.*;

/*
Problem Statement

Given a binary array nums (containing only 0s and 1s) and an integer k, count the number of contiguous subarrays that contain exactly k ones.

Example
Input: nums = [1,0,1,0,1], k = 2
Output: 4
Explanation: Subarrays with exactly 2 ones:
[1,0,1], [1,0,1,0], [0,1,0,1], [1,0,1]

Key Idea

Count subarrays with at most k ones → atMost(k)

Count subarrays with at most k-1 ones → atMost(k-1)

Subarrays with exactly k ones = atMost(k) - atMost(k-1)

Intuition (Sliding Window)

Keep a window [l, r] with at most goal ones.

For each r, number of valid subarrays ending at r = r - l + 1.

Sliding window moves l forward when sum > goal. */

public class BinarySubarraywithsumk {
// --------------------------------------------
// Count subarrays with at most 'goal' ones
// Time: O(n), Space: O(1)
// Remember:
// - Sliding window approach
// - Valid window: total number of 1s ≤ goal
// - For each valid window, (r - l + 1) subarrays end at r
    public static int numberOfSubarrays(int[] nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

    // ------------------------------
    // Count subarrays with at most 'goal' ones
    public static int atMost(int[] nums, int goal) {
        if (goal < 0) return 0;  // No valid subarray

        int l = 0, cnt = 0, sum = 0;

        for (int r = 0; r < nums.length; r++) {
            sum += nums[r];

            while (sum > goal) {
                sum -= nums[l];
                l++;
            }

            cnt += r - l + 1; // All subarrays from l to r are valid
        }

        return cnt;
    }

    // ------------------------------
    // MAIN METHOD
    public static void main(String[] args) {
        int[] nums = {1, 0, 1, 0, 1};
        int k = 2;

        int result = numberOfSubarrays(nums, k);
        System.out.println("Number of subarrays with exactly " + k + " ones: " + result);
    }
}

