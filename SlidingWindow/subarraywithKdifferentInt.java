package SlidingWindow;

import java.util.*;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
Given an integer array nums and an integer k, return
the number of contiguous subarrays that contain exactly
k distinct integers.

Example:
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays with exactly 2 distinct integers:
[1,2], [2,1], [1,2], [2,1,2], [1,2,1], [2,3], [1,2]

========================================================
INTUITION:
--------------------------------------------------------
1. "Exactly k distinct integers" can be computed as:
   exactly_k = atMost(k) - atMost(k - 1)

2. Use sliding window for atMost:
   - Maintain a window [l, r] with at most 'goal' distinct elements.
   - Expand r, shrink l when distinct count > goal.
   - For each r, number of valid subarrays ending at r = r - l + 1.

3. This avoids checking all subarrays explicitly (O(n^2)).

========================================================
TIME AND SPACE COMPLEXITY:
--------------------------------------------------------
Brute Force:
- Time: O(n^2)
- Space: O(k) (hashmap for counting elements)

Optimal (Sliding Window):
- Time: O(n)
- Space: O(k)
========================================================
*/

public class subarraywithKdifferentInt {

    // -----------------------------------------------------
    // Helper function: Count subarrays with at most 'goal' distinct numbers
    // Time: O(n)
    // Space: O(k)
    public static int atMostKDistinct(int[] nums, int goal) {
        Map<Integer, Integer> countMap = new HashMap<>();
        int left = 0, total = 0;

        for (int right = 0; right < nums.length; right++) {
            countMap.put(nums[right], countMap.getOrDefault(nums[right], 0) + 1);

            // Shrink window if distinct count exceeds goal
            while (countMap.size() > goal) {
                countMap.put(nums[left], countMap.get(nums[left]) - 1);
                if (countMap.get(nums[left]) == 0) countMap.remove(nums[left]);
                left++;
            }

            // All subarrays ending at right and starting from left..right are valid
            total += right - left + 1;
        }

        return total;
    }

    // -----------------------------------------------------
    // Optimal function: Subarrays with exactly k distinct integers
    // Time: O(n)
    // Space: O(k)
    public static int subarraysWithKDistinctOptimal(int[] nums, int k) {
        return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
    }

    // -----------------------------------------------------
    // Brute force approach: Try all subarrays
    // Time: O(n^2)
    // Space: O(k)
    public static int subarraysWithKDistinctBrute(int[] nums, int k) {
        int total = 0;

        for (int i = 0; i < nums.length; i++) {
            Map<Integer, Integer> countMap = new HashMap<>();
            for (int j = i; j < nums.length; j++) {
                countMap.put(nums[j], countMap.getOrDefault(nums[j], 0) + 1);

                if (countMap.size() == k) total++;
                else if (countMap.size() > k) break; // no longer valid
            }
        }

        return total;
    }

    // -----------------------------------------------------
    // MAIN METHOD
    public static void main(String[] args) {
        int[] nums = {1, 2, 1, 2, 3};
        int k = 2;

        System.out.println("Brute Force Result: " + subarraysWithKDistinctBrute(nums, k));
        System.out.println("Optimal Result:     " + subarraysWithKDistinctOptimal(nums, k));
    }
}
