package StackQ;

import java.util.*;

public class SubarrayRanges {

    /*
    =====================================================
    PROBLEM STATEMENT:
    -----------------------------------------------------
    Given an integer array arr, find the sum of the ranges
    (max - min) of all possible subarrays.
    =====================================================
    */

    /*
    ========================
    1️⃣ Brute-force Method
    ========================
    Intuition:
    - For each subarray starting at index i, iterate all ending indices j >= i
    - Keep track of min and max in the subarray [i,j]
    - Add (max-min) to the sum

    Time Complexity: O(n^2)
    Space Complexity: O(1)
    */
    public static int sumOfSubarrayRangesBrute(int[] arr) {
        int n = arr.length;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int largest = arr[i];
            int smallest = arr[i];
            for (int j = i; j < n; j++) {
                largest = Math.max(largest, arr[j]);
                smallest = Math.min(smallest, arr[j]);
                sum += (largest - smallest);
            }
        }
        return sum;
    }

    /*
    ========================
    2️⃣ Optimized Method
    ========================
    Intuition:
    - Each element contributes as minimum or maximum in multiple subarrays
    - Use monotonic stacks to efficiently calculate contribution
    - Contribution formula: arr[i] * (#subarrays where it's max/min)
    
    Time Complexity: O(n)
    Space Complexity: O(n)
    */

    // Minimum Helpers
    public static int[] findNextSmaller(int[] arr) {
        int n = arr.length;
        int[] nse = new int[n];
        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && arr[st.peek()] >= arr[i]) st.pop();
            nse[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        return nse;
    }

    public static int[] findPrevSmaller(int[] arr) {
        int n = arr.length;
        int[] pse = new int[n];
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) st.pop();
            pse[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        return pse;
    }

    public static int sumSubarrayMinimums(int[] arr) {
        int n = arr.length;
        int[] nse = findNextSmaller(arr);
        int[] pse = findPrevSmaller(arr);
        long total = 0;
        int mod = (int)1e9 + 7;
        for (int i = 0; i < n; i++) {
            long left = i - pse[i];
            long right = nse[i] - i;
            total = (total + left * right % mod * arr[i] % mod) % mod;
        }
        return (int) total;
    }

    // Maximum Helpers
    public static int[] findNextGreater(int[] arr) {
        int n = arr.length;
        int[] nge = new int[n];
        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && arr[st.peek()] <= arr[i]) st.pop();
            nge[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        return nge;
    }

    public static int[] findPrevGreater(int[] arr) {
        int n = arr.length;
        int[] pge = new int[n];
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && arr[st.peek()] < arr[i]) st.pop();
            pge[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        return pge;
    }

    public static int sumSubarrayMaximums(int[] arr) {
        int n = arr.length;
        int[] nge = findNextGreater(arr);
        int[] pge = findPrevGreater(arr);
        long total = 0;
        int mod = (int)1e9 + 7;
        for (int i = 0; i < n; i++) {
            long left = i - pge[i];
            long right = nge[i] - i;
            total = (total + left * right % mod * arr[i] % mod) % mod;
        }
        return (int) total;
    }

    // Sum of Subarray Ranges
    public static int sumOfSubarrayRanges(int[] arr) {
        int maxSum = sumSubarrayMaximums(arr);
        int minSum = sumSubarrayMinimums(arr);
        int mod = (int)1e9 + 7;
        long ans = ((long) maxSum - minSum + mod) % mod; // ensure non-negative
        return (int) ans;
    }

    public static void main(String[] args) {
        int[] arr = {3, 1, 2, 4};

        System.out.println("Brute-force sum of subarray ranges: " 
                            + sumOfSubarrayRangesBrute(arr)); // O(n^2)

        System.out.println("Optimized sum of subarray ranges: " 
                            + sumOfSubarrayRanges(arr)); // O(n)
    }
}
