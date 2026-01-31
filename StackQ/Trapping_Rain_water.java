package StackQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array arr of non-negative integers representing
elevation heights where the width of each bar is 1, 
compute how much water it can trap after raining.

Example:
Input:  [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
=====================================================
*/

class Trapping_Rain_water{

    /*
    =====================================================
    APPROACH 1: Using Precomputed Right Max (Prefix + Suffix)
    -----------------------------------------------------
    INTUITION:
    - Water trapped at index i = min(maxLeft[i], maxRight[i]) - arr[i]
    - Precompute maxRight array (suffix max)
    - Maintain maxLeft while traversing

    TIME COMPLEXITY: O(n)
    SPACE COMPLEXITY: O(n) for suffix array
    =====================================================
    */
    public static int trappingRainWater2N(int[] arr) {
        int n = arr.length;
        if (n == 0) return 0;

        int[] suffixMax = new int[n];
        suffixMax[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixMax[i] = Math.max(suffixMax[i + 1], arr[i]);
        }

        int total = 0, leftMax = 0;
        for (int i = 0; i < n; i++) {
            leftMax = Math.max(leftMax, arr[i]);
            total += Math.min(leftMax, suffixMax[i]) - arr[i];
        }

        return total;
    }

    /*
    =====================================================
    APPROACH 2: OPTIMAL TWO-POINTER METHOD
    -----------------------------------------------------
    INTUITION:
    - Use two pointers (left and right)
    - Keep track of max heights on both sides
    - Water trapped at a side depends on the smaller boundary
    - Move pointer from the side with smaller height

    TIME COMPLEXITY: O(n)
    SPACE COMPLEXITY: O(1)
    =====================================================
    */
    public static int trappingRainWater(int[] arr) {
        int n = arr.length;
        if (n == 0) return 0;

        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int total = 0;

        while (left <= right) {
            if (arr[left] <= arr[right]) {
                if (arr[left] >= leftMax)
                    leftMax = arr[left];
                else
                    total += leftMax - arr[left];
                left++;
            } else {
                if (arr[right] >= rightMax)
                    rightMax = arr[right];
                else
                    total += rightMax - arr[right];
                right--;
            }
        }

        return total;
    }

    public static void main(String[] args) {
        int[] arr = {0,1,0,2,1,0,1,3,2,1,2,1};

        System.out.println("Prefix + Suffix Array Approach: " + trappingRainWater2N(arr));
        System.out.println("Two-Pointer Optimal Approach: " + trappingRainWater(arr));
    }
}
