package QueueQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT (Sliding Window Maximum):
-----------------------------------------------------
Given an integer array `arr` and a window size `k`,
find the maximum element in every contiguous subarray
(window) of size `k`.

Example:
arr = [1,3,-1,-3,5,3,6,7], k = 3
Output = [3,3,5,5,6,7]
=====================================================
*/

public class SlidingWindowMaximum {

    /*
    =====================================================
    1️⃣ Optimal O(n) Solution using Deque
    =====================================================
    Intuition:
    - Use a deque to store indices of useful elements
    - Deque maintains elements in decreasing order of values
    - Front of deque always stores index of maximum element

    Time Complexity: O(n)
    Space Complexity: O(k)
    */
    public static List<Integer> slidingWindowMax(int[] arr, int k) {
        Deque<Integer> dq = new ArrayDeque<>(); // stores indices
        List<Integer> result = new ArrayList<>();

        int n = arr.length;

        for (int i = 0; i < n; i++) {

            // Remove indices that are out of the current window
            if (!dq.isEmpty() && dq.peekFirst() <= i - k) {
                dq.pollFirst();
            }

            // Maintain decreasing order in deque
            while (!dq.isEmpty() && arr[dq.peekLast()] <= arr[i]) {
                dq.pollLast();
            }

            // Add current index
            dq.offerLast(i);

            // Add max to result once the first window is complete
            if (i >= k - 1) {
                result.add(arr[dq.peekFirst()]);
            }
        }

        return result;
    }

    /*
    =====================================================
    2️⃣ Brute-force O(n * k) Solution
    =====================================================
    Intuition:
    - For each window, iterate over k elements
    - Track and store the maximum

    Time Complexity: O(n * k)
    Space Complexity: O(1)
    */
    public static List<Integer> slidingWindowMaxBrute(int[] arr, int k) {
        List<Integer> result = new ArrayList<>();
        int n = arr.length;

        for (int i = 0; i <= n - k; i++) {
            int maxVal = arr[i];
            for (int j = i; j < i + k; j++) {
                maxVal = Math.max(maxVal, arr[j]);
            }
            result.add(maxVal);
        }

        return result;
    }

    /*
    =====================================================
    Main Method
    =====================================================
    */
    public static void main(String[] args) {
        int[] arr = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;

        List<Integer> optimal = slidingWindowMax(arr, k);
        List<Integer> brute = slidingWindowMaxBrute(arr, k);

        System.out.print("Optimal: ");
        for (int x : optimal) System.out.print(x + " ");

        System.out.print("\nBrute: ");
        for (int x : brute) System.out.print(x + " ");
    }
}
