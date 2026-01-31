package StackQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an integer array arr, find the sum of the
minimum element of all possible contiguous subarrays.

Example:
Input:  [3, 1, 2, 4]
Output: 17
=====================================================
*/

class Sum_subarrays_min{

    /*
    =====================================================
    BRUTE FORCE APPROACH
    -----------------------------------------------------
    INTUITION:
    - For every subarray, track the minimum element
    - Sum all minimums
    TIME COMPLEXITY: O(n^2)
    SPACE COMPLEXITY: O(1)
    =====================================================
    */
    public int sumOfSubarrayMinimumsBrute(int[] arr) {
        int n = arr.length;
        long total = 0;
        int mod = 1_000_000_007;

        for (int i = 0; i < n; i++) {
            int mini = Integer.MAX_VALUE; // running minimum for subarray starting at i
            for (int j = i; j < n; j++) {
                mini = Math.min(mini, arr[j]);
                total = (total + mini) % mod;
            }
        }
        return (int) total;
    }

    /*
    =====================================================
    HELPER FUNCTION: Next Smaller Element (NSE)
    -----------------------------------------------------
    - For each index i, find the index of the next smaller element to the right
    - If no such element exists, store n (length of array)
    =====================================================
    */
    private int[] findNSE(int[] arr) {
        int n = arr.length;
        int[] nse = new int[n];
        Stack<Integer> st = new Stack<>();

        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && arr[st.peek()] >= arr[i])
                st.pop();
            nse[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        return nse;
    }

    /*
    =====================================================
    HELPER FUNCTION: Previous Smaller Element (PSE)
    -----------------------------------------------------
    - For each index i, find the index of the previous smaller element to the left
    - If no such element exists, store -1
    =====================================================
    */
    private int[] findPSE(int[] arr) {
        int n = arr.length;
        int[] pse = new int[n];
        Stack<Integer> st = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && arr[st.peek()] > arr[i])
                st.pop();
            pse[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        return pse;
    }

    /*
    =====================================================
    OPTIMIZED APPROACH USING NSE + PSE
    -----------------------------------------------------
    INTUITION:
    - Each arr[i] contributes as minimum in multiple subarrays:
      Contribution = arr[i] * left * right
      left  = i - pse[i] (#subarrays ending at i)
      right = nse[i] - i (#subarrays starting at i)
    - Sum contributions for all elements
    TIME COMPLEXITY: O(n)
    SPACE COMPLEXITY: O(n)
    =====================================================
    */
    public int sumOfSubarrayMinimums(int[] arr) {
        int n = arr.length;
        int[] nse = findNSE(arr);
        int[] pse = findPSE(arr);
        long total = 0;
        int mod = 1_000_000_007;

        for (int i = 0; i < n; i++) {
            long left = i - pse[i];
            long right = nse[i] - i;
            total = (total + (left * right % mod) * arr[i] % mod) % mod;
        }
        return (int) total;
    }

    public static void main(String[] args) {
        Sum_subarrays_min sol = new Sum_subarrays_min();
        int[] arr = {3, 1, 2, 4};

        System.out.println("Brute Force Result: " + sol.sumOfSubarrayMinimumsBrute(arr));
        System.out.println("Optimized Result: " + sol.sumOfSubarrayMinimums(arr));
    }
}
