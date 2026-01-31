package BinarySearch.1D;
import java.util.*;
public class SmallestDivisorGivenThreshold {

    /*
     * INTUITION:
     * ----------
     * We are looking for the smallest divisor such that:
     * sum( ceil(nums[i] / divisor) ) <= limit
     *
     * If divisor is SMALL  → division result is LARGE → sum is LARGE
     * If divisor is LARGE  → division result is SMALL → sum is SMALL
     *
     * Hence, the sum function is MONOTONICALLY DECREASING.
     * This allows us to apply BINARY SEARCH on the answer (divisor).
     *
     * TIME COMPLEXITY:
     * ----------------
     * For one divisor check: O(n)
     * Binary search range: log(max(nums))
     * Overall: O(n * log(max(nums)))
     *
     * SPACE COMPLEXITY:
     * -----------------
     * O(1) – No extra space used
     */

    // Helper function to calculate:
    // sum = Σ ceil(nums[i] / div)
    private static int sumByDiv(int[] nums, int div, int limit) {
        int sum = 0;

        for (int x : nums) {
            // ceil(x / div) using integer arithmetic
            sum += (x + div - 1) / div;

            // Optimization: stop early if sum exceeds limit
            if (sum > limit) break;
        }
        return sum;
    }

    /*
     * BRUTE FORCE APPROACH
     *
     * Try every possible divisor from 1 to max(nums)
     * Return the first divisor for which sumByDiv <= limit
     *
     * TIME COMPLEXITY: O(n * max(nums))
     * SPACE COMPLEXITY: O(1)
     *
     * This approach is slow and not suitable for large inputs.
     */
    public static int smallestDivisorBrute(int[] nums, int limit) {
        int maxVal = 0;
        for (int x : nums) maxVal = Math.max(maxVal, x);

        for (int div = 1; div <= maxVal; div++) {
            if (sumByDiv(nums, div, limit) <= limit) {
                return div;
            }
        }
        return maxVal;
    }

    /*
     * OPTIMAL APPROACH – BINARY SEARCH ON ANSWER
     *
     * Search space:
     * low  = 1
     * high = max(nums)
     *
     * For each mid divisor:
     *  - If sumByDiv(mid) <= limit → valid divisor, try smaller
     *  - Else → divisor too small, try bigger
     *
     * TIME COMPLEXITY:
     * O(n * log(max(nums)))
     *
     * SPACE COMPLEXITY:
     * O(1)
     */
    public static int smallestDivisor(int[] nums, int limit) {
        int low = 1;
        int high = 0;

        // Find maximum value in array
        for (int x : nums) high = Math.max(high, x);

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (sumByDiv(nums, mid, limit) <= limit) {
                // mid is a valid divisor → try smaller
                high = mid - 1;
            } else {
                // mid too small → increase divisor
                low = mid + 1;
            }
        }

        // 'low' points to the smallest valid divisor
        return low;
    }

    // Driver code for testing
    public static void main(String[] args) {
        int[] nums = {1, 2, 5, 9};
        int limit = 6;

        System.out.println(
            "Smallest divisor (Binary Search): " + smallestDivisor(nums, limit)
        );

        System.out.println(
            "Smallest divisor (Brute Force): " + smallestDivisorBrute(nums, limit)
        );
    }
}

