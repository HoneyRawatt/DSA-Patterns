package BinarySearch.1D;

import java.util.*;
public class MindaysmakeMbouquets {
    // Helper function to check feasibility
    // Can we make at least m bouquets by 'days'?
    //
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    static boolean possible(int[] arr, int days, int m, int k) {
        int cnt = 0;      // count of consecutive bloomed flowers
        int bouquets = 0;

        for (int x : arr) {
            if (x <= days) {
                cnt++;
            } else {
                bouquets += cnt / k; // form bouquets from previous streak
                cnt = 0;
            }
        }
        bouquets += cnt / k; // handle remaining flowers
        return bouquets >= m;
    }

    // Brute Force Approach
    // Time Complexity: O((maxDay - minDay) * n)
    // Space Complexity: O(1)
    static int roseGardenBrute(int[] arr, int m, int k) {
        long required = (long) m * k;
        if (required > arr.length) return -1;

        int minDay = Integer.MAX_VALUE;
        int maxDay = Integer.MIN_VALUE;

        for (int x : arr) {
            minDay = Math.min(minDay, x);
            maxDay = Math.max(maxDay, x);
        }

        // Try every possible day
        for (int day = minDay; day <= maxDay; day++) {
            if (possible(arr, day, m, k)) {
                return day;
            }
        }
        return -1;
    }

    // Optimized Binary Search Approach
    // Time Complexity: O(n log(maxDay - minDay))
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Answer lies between minimum and maximum bloom day
    // - If we can make bouquets on day = mid,
    //   try earlier days (minimize answer)
    static int roseGarden(int[] arr, int m, int k) {
        long required = (long) m * k;
        if (required > arr.length) return -1;

        int minDay = Integer.MAX_VALUE;
        int maxDay = Integer.MIN_VALUE;

        for (int x : arr) {
            minDay = Math.min(minDay, x);
            maxDay = Math.max(maxDay, x);
        }

        int low = minDay, high = maxDay;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (possible(arr, mid, m, k)) {
                high = mid - 1; // try smaller day
            } else {
                low = mid + 1;  // need more days
            }
        }
        return low;
    }

    // Driver code
    public static void main(String[] args) {
        int[] bloomDay = {1, 10, 3, 10, 2};
        int m = 3, k = 1;

        int result = roseGarden(bloomDay, m, k);

        if (result == -1)
            System.out.println("It's not possible to make " + m + " bouquets.");
        else
            System.out.println("Minimum day to make " + m + " bouquets: " + result);
    }
}
