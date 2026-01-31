import java.util.*;

public class MaximumSubarray {

    /*
     * Kadane’s Algorithm
     * Returns start and end index of maximum subarray
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
    static int[] maxSubarraySumKadane(int[] arr, int n) {
        long sum = 0;
        long maxSum = Long.MIN_VALUE;

        int start = -1, ansStart = -1, ansEnd = -1;

        for (int i = 0; i < n; i++) {
            if (sum == 0) start = i;

            sum += arr[i];

            if (sum > maxSum) {
                maxSum = sum;
                ansStart = start;
                ansEnd = i;
            }

            if (sum < 0) {
                sum = 0;
            }
        }

        return new int[]{ansStart, ansEnd};
    }

    /*
     * Brute Force Approach
     *
     * Time Complexity: O(N^2)
     * Space Complexity: O(1)
     */
    static long maxSubarraySumBrute(int[] arr, int n) {
        long maxSum = Long.MIN_VALUE;

        for (int i = 0; i < n; i++) {
            long sum = 0;
            for (int j = i; j < n; j++) {
                sum += arr[j];
                maxSum = Math.max(maxSum, sum);
            }
        }

        return maxSum;
    }

    public static void main(String[] args) {
        int[] arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int n = arr.length;

        int[] kadaneRes = maxSubarraySumKadane(arr, n);
        System.out.println("Kadane's Algorithm: Max Subarray is from index "
                + kadaneRes[0] + " to " + kadaneRes[1]);

        long bruteRes = maxSubarraySumBrute(arr, n);
        System.out.println("Brute-force: Maximum Subarray Sum = " + bruteRes);
    }
}
